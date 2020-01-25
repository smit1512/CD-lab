#include <stdio.h>
#include<stdlib.h>
#include<string.h>
char c;
FILE * fp;
int r=1,co=0,temp;
char ariop[4][2]={"-","*","+","/"};
char relop[6][4]={"<",">","<=",">=","==","!="};
char logop[4][2]={"&","|","&&","||"};
struct token
{
	char lexemename[50];
	int row,col;
	char type[50];
};
struct token getNextToken()
{
	struct token t;
	c=fgetc(fp);
	co++;
	while(c!=EOF)
	{
		if(c=='\n')
		{
			r++;
			co=0;
		}
		for(int i=0;i<4;i++)
		{
			if(c==ariop[i][0])
			{
				strcpy(t.lexemename,ariop[i]);
				strcpy(t.type,"Arithmetic operator");
				t.row=r;
				t.col=co;
				return t;
			}
		}
		if(c=='<')
		{
			temp=co;
			c=fgetc(fp);
			co++;
			if(c=='=')
			{
				strcpy(t.lexemename,"<=");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
			else
			{
				strcpy(t.lexemename,"<");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
		}
		if(c=='>')
		{
			temp=co;
			c=fgetc(fp);
			co++;
			if(c=='=')
			{
				strcpy(t.lexemename,">=");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
			else
			{
				strcpy(t.lexemename,">");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
		}
		if(c=='=')
		{
			temp=co;
			c=fgetc(fp);
			co++;
			if(c=='=')
			{
				strcpy(t.lexemename,"==");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
		}
		if(c=='!')
		{
			temp=co;
			c=fgetc(fp);
			co++;
			if(c=='=')
			{
				strcpy(t.lexemename,"==");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
			else
			{
				strcpy(t.lexemename,"!");
				strcpy(t.type,"Relational operator");
				t.row=r;
				t.col=temp;
				return t;
			}
		}


		if(c=='&')
		{
			temp=co;
			c=fgetc(fp);
			co++;
			if(c=='&')
			{
				strcpy(t.lexemename,"&&");
				strcpy(t.type,"Logical operator");
				t.row=r;
				t.col=temp;
				return t;
			}
			else
			{
				strcpy(t.lexemename,"&");
				strcpy(t.type,"Logical operator");
				t.row=r;
				t.col=temp;
				return t;
			}
		}
		if(c=='|')
		{
			temp=co;
			c=fgetc(fp);
			co++;
			if(c=='|')
			{
				strcpy(t.lexemename,"||");
				strcpy(t.type,"Logical operator");
				t.row=r;
				t.col=temp;
				return t;
			}
			else
			{
				strcpy(t.lexemename,"|");
				strcpy(t.type,"Logical operator");
				t.row=r;
				t.col=temp;
				return t;
			}
		}
		if(c=='(')
		{
			strcpy(t.lexemename,"(");
			strcpy(t.type,"Special symbol");
			t.row=r;
			t.col=temp;
			return t;
		}
		if(c==')')
		{
			strcpy(t.lexemename,"(");
			strcpy(t.type,"Special symbol");
			t.row=r;
			t.col=temp;
			return t;
		}
		if(c=='}')
		{
			strcpy(t.lexemename,"}");
			strcpy(t.type,"Special symbol");
			t.row=r;
			t.col=temp;
			return t;
		}
		if(c=='{')
		{
			strcpy(t.lexemename,"{");
			strcpy(t.type,"Special symbol");
			t.row=r;
			t.col=temp;
			return t;
		}
		if(c==';')
		{
			strcpy(t.lexemename,"*");
			strcpy(t.type,"Special symbol");
			t.row=r;
			t.col=temp;
			return t;
		}
		if(c=='"')
		{
			int q=-1;
			char buf[50];
			buf[++q]=c;
			c=fgetc(fp);
			temp=co;
			co++;
			while(c!='"')
			{
				buf[++q]=c;
				c=fgetc(fp);
				co++;
			}
			buf[++q]='"';
			buf[++q]='\0';
			strcpy(t.lexemename,buf);
			strcpy(t.type,"Literal");
			t.row=r;
			t.col=temp;
			return t;
		}
		c=fgetc(fp);
		co++;
	}
	t.row=0;
	return t;
}
int main()
{
	char c;
	struct token t;
	fp=fopen("a.txt","r");
	if(fp==NULL)
	{
		printf("Cannot open file");
		exit(0);
	}
	while(1)
	{
		t=getNextToken();
		if(t.row!=0)
		{
			printf("<%s,%d,%d,%s>\n",t.lexemename,t.row,t.col,t.type);
		}
		else
		{
			break;
		}
	}
	
}