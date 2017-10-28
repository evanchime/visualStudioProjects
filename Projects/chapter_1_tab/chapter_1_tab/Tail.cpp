#include"stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAXLINES 5000 /* max #lines to be stored */
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int Last_n_lines);

int main(int argc, char *argv[])
{
	int n /* number of input lines to print from argument */, Last_n_lines /* number of input lines to print */, nlines /* number of input lines read */;
	n = 0;
	while (*++argv)
	{
		switch (**argv)
		{
		case '-':
			n = atoi(*argv + 1);
			if (!n)
			{
				printf("invalid column start");
				return 0;
			}
			break;
		default:
			break;
		}
	}

	Last_n_lines = n ? n : 10;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0 && nlines >= Last_n_lines)
	{
		writelines(lineptr, nlines, Last_n_lines);
		return 0;
	}
	else
	{
		printf("error: input too big to store or not enough lines read\n");
		return 1;
	}
}

#define MAXLEN 1000 /* max length of any input line */ 
int getline(char *, int);
char *alloc(int);
void strcpy_x(char *s, char *t);

/* readlines:  read input lines */
int readlines(char * lineptr[], int maxlines)
{
	int len, nlines;
	char * p, line[MAXLEN];
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len - 1] = '\0'; /* delete newline */
			strcpy_x(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}


/* writelines:  write output lines */
void writelines(char * lineptr[], int nlines, int last_n_lines)
{
	int i;
	for (i = nlines - last_n_lines; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}


/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i<lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
	{
		s[i] = c;
		++i;
	} s[i] = '\0';
	return i;
}

/* strcpy_x: my strcpy, copy t to s; pointer version */
void strcpy_x(char *s, char *t)
{
	while (*s++ = *t++)
		;
}

#define ALLOCSIZE 10000 /* size of available space */ 
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char * alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n)
	{
		/* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
