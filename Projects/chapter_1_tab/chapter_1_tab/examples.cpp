// chapter1_testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAXL 1000

int line(char s[], int lim);

void detab(char src[], char tar[], int Tabwidth, int Tabstart);

int main(int argc, char *argv[])
{
	#define MAX_TABS 7

	/*int c, col, blanks, numtabs, m, n, arg_count, k, i, TABWIDTH, Tab_array[MAX_TABS];
	col = blanks = m = n = k = 0;
	arg_count = argc;

	while( *++argv && --arg_count > 0)
	{
	switch(**argv)
	{
	case '-':
	m = atoi(*argv + 1);
	if(!m)
	{	printf("invalid column start");
	return 0;
	}
	break;
	case '+':
	n = atoi(*argv + 1);
	if(!n)
	{	printf("invalid column stop");
	return 0;
	}
	break;
	default:
	Tab_array[k++] = atoi(*argv);
	break;
	}
	}
	Tab_array[k] = '\0';
	k = 0;
	argv -= argc;
	TABWIDTH = n ? n : (Tab_array[k] ? Tab_array[k++] : 8);
	col -= m;
	while ((c = getchar()) != EOF) {

	if (c == ' ') {

	blanks = blanks + 1;

	col = col + 1;

	}
	else
	{

	if (blanks == 1)

	putchar(' ');

	else if (blanks > 1)
	{
	int Adjustments = (col / TABWIDTH)*TABWIDTH;
	numtabs = col / TABWIDTH - (col - blanks) / TABWIDTH;

	for(i = 0; i < Adjustments - (col - blanks); ++i)
	putchar(' ');
	if (numtabs >= 1)

	blanks = col -  Adjustments;

	for (i = 0; i < blanks; ++i)

	putchar(' ');

	}

	blanks = 0;
	putchar(c);
	col = col + 1;
	if (c == '\n')
	{
	col = 0;
	col -= m;
	if ((argc > 1) && !n && !m)
	{
	if (!(TABWIDTH = Tab_array[k++]))
	{
	printf(" no more tab stops in argument ");
	break;
	}
	}
	}

	}

	}*/
	char s[MAXL];
	char tar[MAXL * MAXL];


	int m, n, arg_count, k, i, TABWIDTH, Tab_array[MAX_TABS];
	m = n = k = 0;
	arg_count = argc;

	while (*++argv && --arg_count > 0)
	{
		switch (**argv)
		{
		case '-':
			m = atoi(*argv + 1);
			if (!m)
			{
				printf("invalid column start");
				return 0;
			}
			break;
		case '+':
			n = atoi(*argv + 1);
			if (!n)
			{
				printf("invalid column stop");
				return 0;
			}
			break;
		default:
			Tab_array[k++] = atoi(*argv);
			break;
		}
	}
	Tab_array[k] = '\0';
	k = 0;
	argv -= argc;
	TABWIDTH = n ? n : (Tab_array[k] ? Tab_array[k++] : 8);




	while (line(s, MAXL) > 0)
	{
		if ((TABWIDTH * strlen(s)) < (MAXL * MAXL))
		{
			detab(s, tar, TABWIDTH, m);
			printf("%s", tar);
			if ((argc > 1) && !n && !m)
			{
				if (!(TABWIDTH = Tab_array[k++]))
				{
					printf(" no more tab stops in argument ");
					break;
				}
			}
		}
		else
		{
			printf(" string too large for tab stop ");
		}

	}
	return EXIT_SUCCESS;
}

int line(char s[], int lim)
{

	char c;

	int i = 0;

	while ((c = getchar()) != EOF && c != '\n' && i < lim - 1)
	{

		s[i++] = c;
	}

	if (c == '\n')
	{

		s[i++] = '\n';
	}

	s[i] = '\0';

	return i;

}

void detab(char src[], char tar[], int Tabwidth, int Tabstart)
{

	int i, j, spacew;

	char c;

	for (i = 0, j = 0; (c = src[i]) != '\0'; i++)
	{

		if (c != '\t')
		{

			tar[j++] = c;

		}
		else
		{

			spacew = Tabwidth - (j - Tabstart) % Tabwidth;
			Tabstart = 0;
			while (spacew-- > 0)
			{

				tar[j++] = ' ';

			}

		}

	}

	tar[j] = '\0';

}


