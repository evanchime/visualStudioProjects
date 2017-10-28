// chapter_5_2_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctype.h>
#include <stdio.h>
#include<iostream>
#include<string>
#include <string.h> 


using namespace std;

enum { NAME, PARENS, BRACKETS, PARENS_ARG };
int tokentype; /* type of last token */
int left_parenthesis = 0; /* check for excessive parenthesis*/

#define MAXTOKEN 100
char out[1000]; /* output string */
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */

/* strcpy_x: my strcpy, copy t to s; pointer version */
void strcpy_x(char *s, char *t)
{
	while (*s++ = *t++)
		;
}

/* my strcmp; return < 0 if s < t, 0 if s == t, > 0 if s>t */
int strcmp_x(char *s, char *t)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return (*s - *t);
}

// our version of strcat
void strcat_x(char *s, char *t)
{
	while (*s++); /* find end of string */
	--s;
	while (*s++ = *t++); /* copy t */
}

int getch(void);
void ungetch(int c);
int gettoken(void);

void dcl(void);
void dirdcl(void);

/* dcl:  parse a declarator */ 
void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; ) /* count *' s */
		ns++;
	dirdcl();
	while (ns--> 0)
		strcat_x(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
	int type;
	if (tokentype == '(')
	{  /* ( dcl ) */
		left_parenthesis++;
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	else if (tokentype == NAME) /* variable name */
		strcpy_x(name, token);
	else
		printf("error: expected name or (dcl)\n");

	while ((type = gettoken()) == PARENS || type == BRACKETS || type == PARENS_ARG)
		if (type == PARENS)
			strcat_x(out, " function returning");
		else if (type == PARENS_ARG)
		{
			strcat_x(out, " function taking ");
			strcat_x(out, token);
			strcat_x(out, " and returning");
		}
		else {
			strcat_x(out, " array");
			strcat_x(out, token);
			strcat_x(out, " of");
		}
} 


char datatype[MAXTOKEN]; /* data type = char, int, etc. */


int main() /* convert declaration to words */
{
	int c, getch(void);
	void ungetch(int);
	while (gettoken() != EOF) { /* 1st token on line */
		//strcpy_x(datatype, token); /* is the datatype */
		int CONST = 0;
		if (strcmp_x(token, "const") == 0)
		{
			CONST = 1;
			strcpy_x(datatype, token);
		}
		else if ((strcmp_x(token, "char") == 0) || (strcmp_x(token, "int") == 0))
			strcpy_x(datatype, token);
		else
			printf("error: invalid input \n");
		while ((c = getch()) == ' ' || c == '\t');
		ungetch(c);
		if(isalpha(c))
		{
			if (NAME == gettoken())
		    {
				strcat_x(datatype, " ");
				if (CONST && (strcmp_x(token, "char") == 0 || strcmp_x(token, "int") == 0))
					strcat_x(datatype, token);
				else if (!CONST && strcmp_x(token, "const") == 0)
					strcat_x(datatype, token);
				else
					printf("error: invalid input \n");
			}
		 }


		out[0] = '\0';
		dcl(); /* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char * p = token;

	while ((c = getch()) == ' ' || c == '\t');
	if (c == '(')
	{
		if ((c = getch()) == ')')
		{ 
			strcpy_x(token, "()");
			return tokentype = PARENS;
		}
		else if (isalpha(c))
		{
			for (*p++ = c; isalnum(c = getch()); ) 
				*p++ = c; 
			*p = '\0';
			if (c == ')')
			{
				return tokentype = PARENS_ARG;
			}
			else
			{
				printf("error: invalid input\n");
				return tokentype = c;
			}
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[')
	{
		/*for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;*/
		for (*p++ = c; (*p++ = c = getch()) != ']' && isdigit(c); )
			;
		*p = '\0';
		if (c == ']')
		{
			return tokentype = BRACKETS;
		}
		else
		{
			printf("error: invalid index \n");
			return tokentype = c;
		}
	}
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch()); ) *p++ = c; *p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
	{
		if (c == ']' || (c == ')' && left_parenthesis-- <= 0))
			printf("error: excessive bracket or parenthesis \n");
		return tokentype = c;
	}
		
}

/* undcl: convert word description to declaration */
/*int main()
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF)
	{
		strcpy_x(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat_x(out, token);
			else if (type == '*')
			{
				sprintf_s(temp, "(* %s)", out);
				strcpy_x(out, temp);
			}
			else if (type == NAME)
			{
				sprintf_s(temp, "%s %s", token, out);
				strcpy_x(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}
	return 0;
}*/


#define BUFSIZE 100 
char buf[BUFSIZE]; /* buffer for ungetch */ 

int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}


