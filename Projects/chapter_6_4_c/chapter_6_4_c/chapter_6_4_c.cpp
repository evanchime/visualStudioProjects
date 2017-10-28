// chapter_6_4_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 

#define MAXWORD 100

struct tnode * addtree(struct tnode * p, char * w);
struct tnode *addtree_2_b(struct tnode * p, struct tnode **pp);
void addtree_2_a(struct tnode * p, struct tnode **pp);
void treeprint(struct tnode *);
int getword(char *, int);
void strcpy_x(char *, char *);
int strcmp_x(char *, char *);



struct  tnode  /* the tree node */
{
	char *word; /* points to the text */
	int count; /* number of occurences */
	struct tnode *left; /*left child */
	struct tnode *right; /* right child */
};



int main()
{
	struct tnode *root, *root2;
	char word[MAXWORD];
	root = root2 = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	addtree_2_a(root, &root2);
	treeprint(root2);
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

int getch(void);
void ungetch(int);
/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, d, comment(void);
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


struct tnode *talloc(void);
char *strdup(char *);

struct tnode * addtree(struct tnode * p, char * w)
{
	int cond;
	if (p == NULL)
	{
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

struct tnode *addtree_2_b(struct tnode * p, struct tnode **pp)
{
	if (*pp == NULL)
	{
		*pp = talloc(); // make a new node 
		(*pp)->word = strdup(p->word);
		(*pp)->count = p->count;
		(*pp)->left = (*pp)->right = NULL;
	}
	else if (p->count == (*pp)->count || p->count < (*pp)->count)
		(*pp)->right = addtree_2_b(p, &(*pp)->right); // greater than or equal to into right subtree 
	else
		(*pp)->left = addtree_2_b(p, &(*pp)->left); // less than count word 
	return *pp;
}

/* build tree from existing tree, based on order of frequency of occurence */
void addtree_2_a(struct tnode * p, struct tnode **pp)
{
	if (p != NULL)
	{
		addtree_2_a(p->left, pp);
		*pp = addtree_2_b(p, pp);
		addtree_2_a(p->right, pp);
	}
}


void treeprint(struct tnode * p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

#include <stdlib.h> 
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


