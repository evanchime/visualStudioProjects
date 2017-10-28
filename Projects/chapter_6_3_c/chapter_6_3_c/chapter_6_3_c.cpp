// chapter_6_3_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXWORD 100 
void getword_from_line(char *line, char *word, struct tnode * root, int iii);
//struct tnode *addtree(struct tnode *, char *, int i);
void treeprint(struct tnode *);
//int Compare_Type(char *);
int getline_x(char*, int);
void strcpy_x(char *, char *);
int strcmp_x(char *, char *);
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);

struct tnode * addtree(struct tnode * p, char * w, int i);
int Compare_Type(char *word);

struct  tnode  /* the tree node */
{
	char *word; /* points to the text */
	int Line_count; /* number of occurences */
	int lines[MAXLINES]; /* array of line numbers word appears in */
	struct tnode *left; /*left child */
	struct tnode *right; /* right child */
};



int main()
{
	int nlines; // number of input lines read 
	struct tnode * root;
	char word[MAXWORD];
	root = NULL;
	if ((nlines = readlines(lineptr, MAXLINES)) > 0)
	{
		for (int iii = 0; iii < nlines; iii++)
		{
			char *p = lineptr[iii];
			while (*p)
			{
				char *w = word;
				while (*p == ' ')
					p++;
				while (isalpha(*w = *p))
					w++, p++;
				if (*w == ' ' || *w == '\0')
				{
					*w = '\0';
					if (!Compare_Type(word))
						root = addtree(root, word, (iii + 1));
				}
				else
				{
					while (*p != ' ' && *p != '\0')
						p++;
					if (*p == '\0')
						break;
				}
			}
		}
		treeprint(root);
		return 0;
	}
	else
	{
		printf("error: input too big\n");
		return 1;
	}
	
}

#define MAXLEN 1000 /* max length of any input line */ 
char *alloc(int); /* readlines:  read input lines */
int readlines(char * lineptr[], int maxlines)
{
	int len, nlines;
	char * p, line[MAXLEN]; 
	nlines = 0;
	while ((len = getline_x(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; // delete newline 
			strcpy_x(p, line); 
			lineptr[nlines++] = p;
		} 
	return nlines;
}

/* getline_x: my getline; get line into s, return length */
int getline_x(char *s, int lim)
{
	int c; char *temp;
	for (temp = s; --lim > 0 && (c = getchar()) != EOF && c != '\n'; )
		*temp++ = c;
	if (c == '\n')
		*temp++ = c;
	*temp = '\0';
	return temp - s;
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

#define ALLOCSIZE 10000 /* size of available space */ 
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char * allocp = allocbuf; /* next free position */
char * alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		/* it fits */ allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}
void afree(char * p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

int Compare_Type(char *word)
{
	int iii, jjj;
	static char *types[] = {
		"the",
		"this",
		"that",
		"those",
		"them"
	};
	char *pt = word;
	for (iii = 0, jjj = sizeof types / sizeof types[0]; iii < jjj; )
		if (strcmp_x(pt, types[iii++]) == 0)
			return 1;
	return 0;
}
struct tnode *talloc(void);
char *strdup(char *);

struct tnode * addtree(struct tnode * p, char * w, int i)
{
	int cond;
	if (p == NULL)
	{
		p = talloc(); /* make a new node */
		p->word = strdup(w);
		p->Line_count = 0;
		p->lines[p->Line_count++] = i;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp_x(w, p->word)) == 0)
		p->lines[p->Line_count++] = i; /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w, i);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w, i);
	return p;
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

void treeprint(struct tnode * p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%s%s%s", p->word, " appears in line", (p->Line_count == 1) ? " " : "s ");
		for (int iii = 0; iii < p->Line_count; iii++)
		{
			printf("%s%d", ((iii == 0) ? "" : ", "), p->lines[iii]);
		}
		printf("\n");
		treeprint(p->right);
	}
}