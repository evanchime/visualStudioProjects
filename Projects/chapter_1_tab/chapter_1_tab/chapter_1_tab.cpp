// chapter_1_tab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*

* Exercise 1-20

* Write a program detab that replaces tabs in the input

* with the proper number of blanks to space to the next tab stop.

* Assume a fixed set of tab stops, say every n columns.

* Should n be a variable or a symbolic parameter?

*/



#include <stdio.h>
#include <stdlib.h>
//#include<string.h>
#include<iostream>
#include<vector>
#include<string>
#include<new>
#include<memory>
#include<bitset>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
//#include"Text_Query.h"
#include<algorithm>
#include<iterator>
#include<exception>
//#include"Sales_data.h"
#include<functional>

using std::cout;
using std::endl;

using namespace std;



#define MAXL 1000



#define TRUE  1

#define FALSE 0



int line(char s[], int lim);

void detab(char src[], char tar[], int Tabwidth, int Tabstart);

	
/*qsort: sort v[left]...v[right] into increasing order */
void qsort(void * v[], int left, int right, int(*comp)(void *, void *))
{
	int i, last;
	void swap(void * v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last, comp);
	qsort(v, last + 1, right, comp);
}
void swap(void * v[], int i, int j)
{
	void * temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}



	int main(int argc, char *argv[])

	{

		/* // ordinary entab version
		int i;

		int c, col, blanks, numtabs;



		col = blanks = 0;

		while ((c = getchar()) != EOF) {

			if (c == ' ') {

				blanks = blanks + 1;

				col = col + 1;

			}
			else {

				if (blanks == 1)

					putchar(' ');

				else if (blanks > 1) {

					numtabs = col / TABWIDTH - (col - blanks) / TABWIDTH;

					for (i = 0; i < numtabs; ++i)

						putchar('\t');

					if (numtabs >= 1)

						blanks = col - (col / TABWIDTH)*TABWIDTH;

					for (i = 0; i < blanks; ++i)

						putchar(' ');

				}

				blanks = 0;

				putchar(c);

				col = col + 1;

				if (c == '\n')

					col = 0;

			}

		}*/

	/* // entab version that takes argument from command line
	
	#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	# define MAX_TABS 7
	int i, j, TABWIDTH;

	int c, col, blanks, numtabs, m, n, arg_count, k, Tab_array[MAX_TABS];
	col = blanks = m = n = k = 0;
	arg_count = argc;

	while( *++argv && --arg_count > 0)
	{
		switch(**argv)
		{
			case '-':
				m = atoi(*argv + 1);
				break;
			case '+':
				n = atoi(*argv + 1);
				break;
			default:
				Tab_array[k++] = atoi(*argv);
				break;
		}
	}
	Tab_array[k] = '\0';
	k = 0;
	argv -= argc; //temp;
	TABWIDTH = ((argc > 1) ? (n ? n : Tab_array[k++]) : 8);

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
				numtabs = col / TABWIDTH - (col - (blanks + m)) / TABWIDTH;

				for(j = 0; j < Adjustments - (col - (blanks + m)); ++j)
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
				if ((argc > 1) && !n)
				{
					if (!(TABWIDTH = Tab_array[k++]))
					{
						printf(" no more tab stops in argument ");
						break;
					}
				}
			}

		}

	}
	return EXIT_SUCCESS;	
}


	*/
	/*# define MAX_TABS 7
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


	

	while (line(s, MAXL) > 0 )
	{
		if ((TABWIDTH * strlen(s)) < strlen(tar))
		{
			detab(s, tar, TABWIDTH, m);
			/*if (argc > 1)
			{
				if (!*++argv)
				{
					printf(" no more tab stops in argument ");
					break;
				}
			}*/
			/*printf("%s", tar);
			if((argc > 1) && !n && !m)
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
		
	}*/

		char *s[4] = { "aaa", "bbb", "ccc", "ddd"};

		qsort((void **)s, 0, 3, (int (*)(void *, void*))strcmp);

		for (auto x = begin(s); x != end(s); )
			cout << *(x++) << endl;

		return EXIT_SUCCESS;

}





int line(char s[], int lim) {

	char c;

	int i = 0;

	while ((c = getchar()) != EOF && c != '\n' && i < lim - 1) {

		s[i++] = c;
	}

	if (c == '\n') {

		s[i++] = '\n';
	}

	s[i] = '\0';

	return i;

}

void detab(char src[], char tar[], int Tabwidth, int Tabstart) 
{

	int i, j, spacew;

	//int j = 0;

	//int spacew;

	char c;

	for (i = 0, j = 0; (c = src[i]) != '\0'; i++) {

		if (c != '\t') {

			tar[j++] = c;

		}
		else {

			spacew = Tabwidth - (j - Tabstart) % Tabwidth;

			while (spacew-- > 0) {

				tar[j++] = '-';

			}

		}

	}

	tar[j] = '\0';

}


