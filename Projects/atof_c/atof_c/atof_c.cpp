// atof_c.cpp : Defines the entry point for the console application.
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
#include <ctype.h> 

using namespace std;
/* atof:  convert string s to double */ 
double atof(char s[]) 
{ 
	double val, power, epower;
	int i, j, sign, esign, eval;
	epower = 1;
	for (i = 0; isspace(s[i]); i++) 
		/*skip white space */ ; 
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') 
		i++; 
	for (val = 0.0; isdigit(s[i]); i++) 
		val = 10.0 * val + (s[i] - '0'); 
	if (s[i] == '.')
		i++; 
	for (power = 1.0; isdigit(s[i]); i++) 
	{ 
		val = 10.0 * val + (s[i] - '0'); 
		power *= 10.0; 
	}
	if (s[i] == 'e' || s[i] == 'E')
	{
		i++;
		esign = (s[i++] == '-') ? -1 : 1;
		for (eval = 0; isdigit(s[i]); i++)
		{
			eval = 10 * eval + (s[i] - '0');
		}
		for (j = 0; j < eval; j++)
		{
			epower *= 10;
		}
		if (esign == -1)
			epower = 1 / epower;
	}

	return sign * epower * val / power; 
} 

int main()
{
	double atof(char s[]);
	char s[] = "123.45e-6";
	printf("%g", atof(s));

	

    return 0;
}

