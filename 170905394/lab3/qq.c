#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TableLength 1000

struct token
{
	char lexeme[100];
	char type[50];
	int size;
	int no_of_arg;
	char return_type[50];
	char scope;
	int arg[1];
};
typedef struct token token;
struct node
{
	token tok;
	struct node *next;
};
typedef struct node node;
node *table[TableLength] = {NULL};
int isdelimiter(char ch)
{
	return(ch==','||ch=='"'||ch==' '||ch=='\n'||ch=='\t'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='='||ch==';'||ch=='('||ch==')'||ch=='}'||ch=='{'||ch=='<'||ch=='>'||ch=='|'||ch=='&');

}

int iskeyword(char *str)
{
	return (!strcmp(str,"int")||!(strcmp(str,"float"))||!(strcmp(str,"if")));
}

int isIdentifier(char *str)
{
	if(strcmp(str,"printf")==0 || (strcmp(str,"scanf")==0))
		return 0;
	if((str[0]>='0' && str[0]<='9') || isdelimiter(str[0]))
		return 0;
	else
	{
		for(int i=1;i<strlen(str);i++)
		{
			if(isdelimiter(str[i]))
				return 0;
		}
	}
	return 1;
}
int hashf(char str[])
{
	int val=0;
	int c=2;
	for(int i=0;i<strlen(str);i++)
	{
		val+=c*str[i];
		c++;
	}
	return val;
}
int search(char str[])
{
	int pos=hashf(str)%TableLength;
	node *temp=table[pos];
	while(temp)
	{
		token t=temp->tok;
		if(strcmp(t.lexeme,str)==0)
		{
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}
void insert(token t)
{
	if(search(t.lexeme)==1)
	{
		//printf("present\n");
		return;
	}
	else
	{
		//printf("not\n");
	}
	node *nd = (node*)malloc(sizeof(node));
	nd->tok=t;
	nd->next=NULL;
	int pos=hashf(t.lexeme)%TableLength;
	//printf("%d\n",pos);
	if(table[pos]==NULL)
	{
		table[pos]=nd;
		return;
	}
	else
	{
		node *temp=table[pos];
		while(temp->next)
		{
			temp=temp->next;
		}
		temp->next=nd;
	}
}
void print(token tok)
{
	printf("%s\t%s\t%d\t%c\t%d\t\t%d\t\t%s\n",tok.lexeme,tok.type,tok.size,tok.scope,tok.no_of_arg,tok.arg[0],tok.return_type);
}
void display()
{
	//printf("hello\n");
	printf("Name\tType\tSize\tScope\tNo_of_arg\tArguments\tReturn Type\n");
	for(int i=0;i<TableLength;i++)
	{
		
		node *temp=table[i];
		if(temp!=NULL)
		{
			while(temp->next!=NULL)
			{
				print(temp->tok);
				temp=temp->next;
			}
			print(temp->tok);
		}
		//
	}
}
void getNextToken()
{
	FILE *file = fopen("t1.c","r");
	char ch;
	token tok;
	int index=0;
	token prev;
	int flag=0;
	int vflag=0;
	token func;
	func.no_of_arg=0;
	while((ch=fgetc(file))!=EOF)
	{
		//printf("%c\n",ch);
		if(!isdelimiter(ch))
		{
			int i=0;
			char str[50];
			//printf("hi\n");
			while(ch!=' ' && ch!='(')
			{
				str[i++]=ch;
				ch=fgetc(file);
			}
			str[i]='\0';
			if(iskeyword(str))
			{
				strcpy(tok.lexeme,str);
				prev=tok;
				continue;
			}
			else if(isIdentifier(str))
			{
				if(ch=='(')
				{
					strcpy(tok.lexeme,str);
					char t[]="FUNC";
					strcpy(tok.type,t);
					tok.size=0;
					strcpy(tok.return_type,prev.lexeme);
					tok.scope='G';
					if(fgetc(file)==')')
						tok.no_of_arg=0;
					else
					{
						tok.no_of_arg=1;
						fseek(file,-1,SEEK_CUR);
						vflag=1;
					}
					fseek(file,-1,SEEK_CUR);
					func=tok;
				}
				else
				{	
					char ret[]="none";
					strcpy(tok.lexeme,str);
					strcpy(tok.type,prev.lexeme);
					tok.no_of_arg=0;
					strcpy(tok.return_type,ret);
					tok.arg[0]=0;
					if(strcmp(prev.lexeme,"int")==0)
						tok.size=4;
					if(flag==1)
						tok.scope='L';
					else if((strcmp(prev.type,"FUNC")==0))
					{
						tok.scope=' ';
					}
					else
						tok.scope='G';
					if(func.no_of_arg==1 && vflag==1)
					{
						func.arg[0]=hashf(tok.lexeme);
						printf("%s %s\n",tok.lexeme,func.lexeme);
						vflag=0;
					}
				}
			}
			//print(tok);
			insert(tok);
			prev=tok;
		}
		else
		{
			if(ch=='{')
			{
				flag=1;
				//printf("here\n");
			}
			else if(ch=='}')
				flag=0;
		}
	}
	fclose(file);
	display();
}
int main()
{
	//Initialize();
	getNextToken();
}
