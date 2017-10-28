// chapter_5_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctype.h>
#include <stdio.h>
#include<iostream>
#include<string>
#include <string.h> 

using namespace std;

int getch(void);
void ungetch(int);

#define SIZE 4


/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))   /* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);  /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{
		if (!isdigit(c = getch()))
		{
			ungetch(c);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

/* getfloat:  get next floating point number from input into *pn */
int getfloat(double *pn)
{
	int c, sign;
	double power;

	while (isspace(c = getch()))   /* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);  /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{
		if (!isdigit(c = getch()))
		{
			ungetch(c);
			return 0;
		}
	}
	for (*pn = 0.0; isdigit(c); c = getch())
	{
		*pn = 10.0 * *pn + (c - '0');
	}
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch())
	{
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}
	*pn = (sign * *pn) / power;
	if (c != EOF)
		ungetch(c);
	return c;
}

// our version of strcat
void strcat_x(char *s, char *t)
{
	while (*s++); /* find end of string */
	--s;
	while (*s++ = *t++); /* copy t */
}


char *strncat_x(char s[], char t[], size_t n)
{
	size_t iii, jjj;
	for (iii = strlen(s), jjj = 0; jjj < n; )
		s[iii++] = t[jjj++];
	s[iii] = '\0';
	return s;
}

/* strncat:  concatenate at most n characters of t to the end of s; s

must be big enough. pointer version */

/* char *strncat_x(char *s, const char *t, int n)

{
	char *temp = s;
	while (*s)              // find end of s 
		s++;
	while (*t && n-- > 0)   // copy at most n characters of t 
		*s++ = *t++;
	*s = '\0';
	return temp;

}*/


/* strncmp:  compare at most n characters of s and t, return <0 if s<t,

0 if s==t, >0 if s>t */

int strncmp_x(char *s, const char *t, int n)

{

	for (; *s == *t && n-- > 0; s++, t++)

		if (*s == '\0' || n == 0)

			return 0;

	return *s - *t;

}

// function strend which returns 1 if the string t 
// occurs at the end of the string s and zero otherwise
int strend(char s[], char t[])
{
	int iii, jjj;
	for (iii = strlen(s) - strlen(t), jjj = 0; iii > 0 && s[iii] != '\0'; )
		if (s[iii++] != t[jjj++])
			return 0;
	if (s[iii] == '\0' && t[jjj] == '\0')
		return 1;
	else
		return 0;
}

char *strncpy_x(char s[], char t[], size_t n)
{
	size_t jjj;
	for (jjj = 0; jjj < n; jjj++)
		s[jjj] = t[jjj];
	return s;
}


/* strncpy:  copy at most n characters of t to s. pointer version */
/*char *strncpy_x(char *s, const char *t, int n)
{
	char *temp = s;
	while (*t && n-- > 0)
		*s++ = *t++;
	*s = '\0';
	return temp;

}*/

/* getline: get line into s, return length */
int getline(char *s, int lim)
{
	int c; char *temp;
	for (temp = s; --lim > 0 && (c = getchar()) != EOF && c != '\n'; )
		*temp++ = c;
	if (c == '\n')
		*temp++ = c;
	*temp = '\0';
	return temp - s;
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

/* strindex:  return index of t in s, −1 if none  */
int strindex_x(char *s, char *t)
{
	char *s_temp, *t_temp;
	int i;
	for (s_temp = s, i = 0; *s_temp != '\0'; s_temp = s + (++i))
	{
		for (t_temp = t; *t_temp != '\0' && *s_temp == *t_temp; s_temp++, t_temp++);
		if ((t_temp - t) > 0 && *t_temp == '\0')
			return i;
	}
	return -1;
}

void reverse(char *s)
{
	int c;
	char *temp = s;
	while (*s++);
	for (s -= 2; s > temp; s--, temp++)
	{
		c = *s;
		*s = *temp;
		*temp = c;
	}
}
void itoa(int n, char *s)
{
	char *temp = s;
	int sign;
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	do { /* generate digits in reverse order */
		*s++ = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(temp);
}

int atoi_x(char *s)
{
	int sign, n = 0;
	while (isspace(*s++));
	sign = (*(--s) == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	while (isdigit(*s))
		n = (10 * n) + (*s++ - '0');
	return sign * n;
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
#define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char * lineptr[], int left, int right); /* sort input lines */
/*int main()
{
	int nlines; // number of input lines read 
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
		return 1;
	}
}*/

#define MAXLEN 1000 /* max length of any input line */ 
int getline(char*, int);
char *alloc(int); /* readlines:  read input lines */
int readlines(char * lineptr[], int maxlines)
{
	int len, nlines;
	char * p, line[MAXLEN]; nlines = 0;
	while ((len = getline_x(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; // delete newline 
			strcpy_x(p, line); lineptr[nlines++] = p;
		} return nlines;
	/*char allocbuf[ALLOCSIZE];
	int len, nlines;
	char * p = allocbuf, line[MAXLEN]; nlines = 0;
	while ((len = getline_x(line, MAXLEN)) > 0)
		if (nlines >= maxlines || ((allocbuf + ALLOCSIZE - p) < len))
			return -1;
		else {
			line[len - 1] = '\0'; // delete newline 
			strcpy_x(p, line); lineptr[nlines++] = p;
			p += len;
		} return nlines;*/
} /* writelines:  write output lines */
void writelines(char * lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}
/* qsort : sort v[left]...v[right] into increasing order */
void qsort(char * v[], int left, int right)
{
	int i, last;
	void swap(char * v[], int i, int j);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp_x(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}
/* swap:  interchange v[i] and v[j] */
void swap(char * v[], int i, int j)
{
	char * temp; temp = v[i];
	v[i] = v[j]; v[j] = temp;
}


static char daytab[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };

/* day_of_year:  set day of year from month & day */ 
int day_of_year(int year, int month, int day)
{
	if (year < 1)
	{
		printf(" invalid year ");
		return -1;
	}
		
	if (month < 1 || month > 12)
	{
		printf(" invalid month ");
		return -1;
	}
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	char(*p)[13] = daytab;
	if (day < 1 || day > /*daytab[leap][month]*/ *(*(p + leap) + month))
	{
		printf(" invalid day ");
		return -1;
	}
	for (i = 1; i < month; i++)
		day += /*daytab[leap][i]*/ *(*(daytab + leap) + i); 
	return day;
} 
/* month_day : set month, day from day of year */
void month_day(int year, int yearday, int * pmonth, int * pday) 
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (year >= 1 /* || yearday >= 1*/)
	{
		if (yearday >= 1 && ((leap && yearday <= 366) || (!leap && yearday <= 365)))
		{
			for (i = 1; yearday > /*daytab[leap][i] */ *(*(daytab + leap) + i); i++)
				yearday -= /* daytab[leap][i] */ *(*(daytab + leap) + i);
			*pmonth = i;
			*pday = yearday;
		}
		else
			printf("error; invalid yearday \n");
	}
	else
		printf("error; invalid year \n");
}

#define LIBFUNC 1
#define MAXVAL 100
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push:  push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop : pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

double result(void)
{
	return pop();
}

void LibFunc(char ss[])
{
	if (ss[0] == 's' && ss[1] == 'i' && ss[2] == 'n')
	{
		push(sin(pop()));
	}
	else if (ss[0] == 'e' && ss[1] == 'x' && ss[2] == 'p')
	{
		push(exp(pop()));
	}
	else if (ss[0] == 'p' && ss[1] == 'o' && ss[2] == 'w')
	{
		double op3;
		op3 = pop();
		push(pow(pop(), op3));
	}
	else {
		printf("error: not a valid function\n");
	}
}


int main(int argc, char *argv[])
{
	/*int n, getfloat(double *);
	double array[SIZE];
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;
	for (size_t i = 0; i < SIZE; i++)
	{
		cout << array[i] << " ";
	}
	*/

	//char s[10] = "byebye";
	//char t[4] = "aye";

	//int n[9] = { 6,7 };

	

	//cout << strncmp_x(s, t, 3);;

	//char s[5];
	//cout << getline(s, 5);
	//char s[3];
	//reverse(s);
	 
	//itoa(20, s);

	//int y = atoi_x("  66");
	//cout << y;

	/*int month = 0;
	int day = 2;

	month_day(0, 365, &month, &day);

	cout << month << day;
	//cout << day_of_year(0, 3, 33);*/
    return 0;
}

/* Chose a flag to toggle when an EOF is encountered */
#define HITEOF  0
#define NOEOF   1
#define BUFSIZE 100 
int bufp = 0; /* next free position in buf */
char buf[BUFSIZE]; /* buffer for ungetch */
int eofStatus = NOEOF;

/* getch: get a (possibly pushed back) character */
int getch(void) {
	if (eofStatus == NOEOF) /* if an EOF hasn't been hit operate as normal */
		return (bufp > 0) ? buf[--bufp] : getchar();
	else /* if an EOF has been hit, then always return EOF */
		return EOF;
}

/* push character back on input */
void ungetch(int c) {
	if (c == EOF)
		eofStatus = HITEOF; /* toggle the eof flag */

	if (eofStatus != HITEOF) /* only keep reading in chars if an eof hasn't been hit */
		if (bufp >= BUFSIZE)
			printf("ungetch: too many characters\n");
		else
			buf[bufp++] = c;
}

