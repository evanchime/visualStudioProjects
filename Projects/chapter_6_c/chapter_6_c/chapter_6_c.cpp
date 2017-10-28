// chapter_6_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <ctype.h> 
#include <string.h>
#include <stdlib.h> 
 
struct  tnode  /* the tree node */
{
	char *word; /* points to the text */
	int count; /* number of occurences */
	struct tnode *left; /*left child */
	struct tnode *right; /* right child */
};

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int Compare_Type(char *);
void strcpy_x(char *, char *);
int strcmp_x(char *, char *);

/* word frequency count */
int main(int argc, char *argv[])
{
	//#define VAR atoi(argv[1])
	struct tnode * root;
	char word[MAXWORD];
	root = NULL;
	/*while (getword(word, MAXWORD) != EOF)
	if (isalpha(word[0]))
	root = addtree(root, word);*/
	while (getword(word, MAXWORD) != EOF)
		if (Compare_Type(word))
		{
			int c;
			if ((c = getword(word, MAXWORD)) == EOF)
				break;
			/*else if(c == '\n')
			continue;*/
			else if ((isalpha(word[0]) || word[0] == '_') && strlen(word) > 6)
				root = addtree(root, word);
		}
	treeprint(root);
	return 0;
}

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


/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, d, comment(void), getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#')
	{
		for (; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_')
			{
				ungetch(*w);
				break;
			}
	}
	else if (c == '\'' || c == '"')
	{
		for (; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c)
			{
				w++;
				break;
			}
			else if (*w == EOF)
				break;
	}
	else if (c == '/')
		if ((d = getch()) == '*')
			c = comment();
		else
			ungetch(d);
	*w = '\0';
	return c;
}

int getch(void);
void ungetch(int);
/* comment: skip over comment and return a character */
int comment()
{
	int c;
	while ((c = getchar()) != EOF)
		if (c == '*')
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
	return c;
}


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

int Compare_Type(char *word)
{
	int iii, jjj;
	static char *types[] = {
		"char",
		"int",
		"void"
	};
	char *pt = word;
	for (iii = 0, jjj = sizeof types / sizeof types[0]; iii < jjj; )
		if (strcmp_x(pt, types[iii++]) == 0)
			return 1;
	return 0;
}

struct tnode * talloc(void);
char * strdup(char *);

/* addtree:  add a node with w, at or below p */
struct tnode * addtree(struct tnode * p, char * w)
{
	int cond;
	if (p == NULL)
	{
		/* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp_x(w, p->word)) == 0)
		p->count++; /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode * p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}


/* talloc:  make a tnode */
struct tnode * talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char * strdup(char * s) /* make a duplicate of s */
{
	char * p;
	p = (char *)malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy_x(p, s);
	return p;
}


