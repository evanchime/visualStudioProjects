// itoa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<new>
#include<memory>
#include<bitset>
#include<fstream>
#include<sstream>
#include<stdio.h>



using namespace std;

/*reverse:  reverse string s in place */

void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = (strlen(s) - 1); i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/*itoa_2:  convert n to characters in s, third argument = min field width */
void itoa_2(int n, char s[], int min_field_width)
{
	int i, sign, r, width_count;
	//n_copy = n ; /* make copy n */ 
	//if (((sign = n) < 0)  && (n_copy <<= 1)) /*record sign and check if n is largest possible negative value */
	//n = -n; /*make n positive */ 
	sign = n;
	i = width_count = 0;
	do {
		/*generate digits in reverse order */
		r = n % 10;
		if (sign < 0)
			r = -r;
		s[i++] = r + '0';
		++width_count;
		//s[i++] = (n_copy) ? ((n % 10) + '0') : (-(n % 10) + '0'); /*get next digit */
	} while (n /= 10);
	/*delete it */
	if (sign < 0)
		s[i++] = '-';
	if (width_count < min_field_width)
	{
		for ( ; i < min_field_width ; )
		{
			s[i++] = ' ';
		}
	}
	s[i] = '\0';
	reverse(s);
}


/*itoa:  convert n to characters in s */ 
void itoa(int n, char s[])
{
	int i, sign, r; 
	//n_copy = n ; /* make copy n */ 
	//if (((sign = n) < 0)  && (n_copy <<= 1)) /*record sign and check if n is largest possible negative value */
		//n = -n; /*make n positive */ 
	sign = n;
	i = 0; 
	do {
		/*generate digits in reverse order */ 
		r = n % 10;
		if (sign < 0)
			r = -r;
		s[i++] = r + '0';
		//s[i++] = (n_copy) ? ((n % 10) + '0') : (-(n % 10) + '0'); /*get next digit */
	} while (n /= 10); 
	/*delete it */ 
	if (sign < 0)
		s[i++] = '-'; 
	s[i] = '\0'; 
	reverse(s);
}
// another version of itob, more concise
/*
void itob(int n, char s[], int b)
{
int i, sign, r;

sign = n;
i = 0;
do {
r = n % b;
if (sign < 0)
r = -r;
s[i++] = (r > 9 ? (r-10 + 'A') : (r + '0'));
} while (n /= b);

if (sign < 0)
s[i++] = '-';
s[i] = '\0';

reverse(s);
}*/

void itob(int n, char s[], int base)
{
	int i, sign, jjj;
	jjj = i = 1;
	while ((i <<= 1) != 0)
	{
		++jjj;
	}
	unsigned int N;
	if ((sign = n) < 0) /*record sign */
	{
		if (base = 2)
			N = ~(-n) + 1;
		else
			N = -n; /*make n positive */
	}
	else
		N = n;
	i = 0;
	do {
		/*generate digits in reverse order */
		if ((N % base) >= 10)
			s[i++] = (N % base) - 10 + 'a'; /*get next digit. case base 16, abcdef */
		else
			s[i++] = (N % base) + '0'; /*get next digit */
	} while (N /= base);
	/* case base 8 or base 16 */
	if (base == 8 || base == 16)
	{
		if(base == 16)
			s[i++] = 'x';
		s[i++] = '0';
	}
	/*delete it */
	if (sign < 0 && base != 2)
		s[i++] = '-';
	else if (sign >= 0 && base == 2)
	{
		for (; i < jjj; )
			s[i++] = '0';
	}
	s[i] = '\0';
	reverse(s);
}



int main()
{
	
	char s[128];

	int n = -987453;

	itoa_2(n, s, 5);
	printf("%s", s);
	
    return 0;
}

