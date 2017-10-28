//commandline.cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctype.h>
#include <stdio.h>
#include<iostream>
#include<string>
#include <string.h> 

using namespace std;

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
	double op2;
	if (argc < 4)
	{
		printf("not enought arguments: expr numbers operators\n");
	}
	else
	{
		while (--argc > 0)
		{
			char s[100], *ps = s, c;
			if (isdigit(**++argv))
			{
				while (isdigit(*ps++ = (*(*argv)++)));
				if ((*--ps = (*--(*argv))) == '.')
					while (isdigit(*++ps = (*++(*argv))));
				push(atof(s));
			}
			else
			{
				while (*ps++ = (*(*argv)++));
				if ((ps - s) == 4)
					c = LIBFUNC;
				else if ((ps - s) == 2)
					c = *s;
				else
					c = '\0';
				switch (c)
				{
				case LIBFUNC:
					LibFunc(s);
					break;
				case '+':
					push(pop() + pop());
					break;
				case '*':
					push(pop() * pop());
					break;
				case '-':
					op2 = pop();
					push(pop() - op2);
					break;
				case '/':
					op2 = pop();
					if (op2 != 0.0)
						push(pop() / op2);
					else
						printf("error: zero divisor\n");
					break;
				case '%':
					op2 = pop();
					if (op2 != 0.0)
						push((int)pop() % (int)op2);
					else
						printf("error: zero divisor\n");
					break;
				default:
					printf("error: unknown command %s\n", s);
					break;
				}
			}
		}
		printf("the result is %.2f\n", result());
	}
	
	return 0;
}
