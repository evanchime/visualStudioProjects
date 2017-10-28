// bits_manipulation_c.cpp : Defines the entry point for the console application.
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
#include<math.h>
#include<utility>

#define MAXLINE 1000


using namespace std;

// getbits returns the (right adjusted) n-bit field of x that begins at position p
// assume n and p are sensible positive values
unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

// setbits return x with the n bits at position p set to the rightmost n bits of y, 
//leaving the others unchanged
unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned a;
	a = (1 << n) - 1; // mask
	y = (y & a); // masking
	y = y << ((p - n) + 1); // shift masked value to position p
	a = ~(a << ((p - n) + 1)); // shift mask to position p
	return (x & a) | y;
}

// invert returns x with the n bits that begin at position p inverted
// (ie 1 changed into 0 and vice versa), leaving the others unchanged
unsigned invert(unsigned x, int p, int n) {
	unsigned a, y;
	a = (1 << n) - 1; // mask
	y = (x >> ((p - n) + 1)) & a; // shift x to rightmost bits, then mask
	y = (y ^ a); // xor masked value
	a = ~(a << ((p - n) + 1)); // shift xored masked value to position p
	return (x & a) | (y << ((p - n) + 1));
}

// rightrot  returns the value of the integer x rotated right by n bit positions
unsigned rightrot(unsigned x, int n) {
	unsigned a, y, z;
	a = x & ((1 << n) - 1); // extract rightmost n bits of x;
	x = x >> n; // shift x n bits right 
	y = z = 1;
	while ((y = y << 1) != 0) // find out how many bits in x
	{
		++z;
	}
	return x | (a << (z - n)); // right rotated x
}


/*int binsearch(int x, int v[], int n) {
	int low, high, mid; low = 0; high = n - 1;
	while (low <= high) 
	{
		mid = (low + high) / 2; 
		if (x < v[mid]) 
			high = mid - 1; 
		else if (x > v[mid])
			low = mid + 1; 
		else                  
		  return mid; //found match 
	} 
	return -1;  //no match
}*/

int binsearch(int x, int v[], int n) // binary search . decides if the value x, occurs in the sorted array v
{
	int low, high, mid;
	low = mid = 0; high = n - 1; 
	while ((low <= high) && x != v[mid])
	{
		mid = (low + high) >> 1;
		 (x < v[mid]) ? (high = mid - 1) : (low = mid + 1);
	}
	if (x == v[mid])
		return mid;
	return -1;
}

void escape(char s[], char t[])
{
	// function escape converts characters like newline and tab 
	// into visible escape sequences like \t and \n as it copies the string t to s
	int iii, jjj;
	for ( jjj = iii = 0; t[iii] != '\0'; iii++)
	{
		if (t[iii] == '\\')
		{
			switch (t[++iii])
			{
			case 't':
				s[jjj++] = '\t';
				break;
			case 'n':
				s[jjj++] = '\n';
				break;
			default:
				s[jjj++] = t[--iii];
				break;
			}
		}
		else
		{
			s[jjj++] = t[iii];
		}
	}
	s[jjj] = '\0';
}

void reverse_escape(char s[], char t[])
{
	// function reverse_escape converts escape sequences into the real characters 
	int iii, jjj;
	for (jjj = iii = 0; t[iii] != '\0'; iii++)
	{
		switch (t[iii])
		{
		case '\t':
			s[jjj++] = '\\';
				s[jjj++] = 't';
			break;
		case '\n':
			s[jjj++] = '\\';
				s[jjj++] = 'n';
			break;
		default:
			s[jjj++] = t[iii];
			break;
		}
	}
	s[jjj] = '\0';
}

void expand(char s1[], char s2[])
{
	char s3[1000];
	int i, j, l, x;
	l = i = j = x = 0;
	for (i = 0; s1[i] != '\0'; ++i)
	{
		if (s1[i] != '-')
		{
			s3[l++] = s1[i];
		}
		else if(i == 0)
			s3[l++] = s1[i];
		else
		{
			x = s1[++i];
			i -= 2;
			if (x == '\0')
			{
				s3[l++] = s1[++i];
				s3[l++] = '\0';
				break;
			}
			else
			{
					for (j = 0; s2[j] != '\0'; j++)
					{
						if (tolower(s2[j]) == tolower(s1[i]))
						{
							for (j +=1; s2[j] != x;)
							{
								s3[l++] = s2[j++];
							}
							s3[l++] = x;
							break;
						}
					}
				}
				i += 2;
			}
		}
	s3[l] = '\0';	
	for ( i = 0; s3[i] != '\0'; i++)
	{
		s1[i] = s3[i];
	}
	s1[i] = '\0';
}

// reverse function reverses string in place 
/*void reverse(char s[])
{
	int c, i, j;
	for( i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{ 
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}*/

// recursive version of function reverse(s) which reverses strings in place
void do_reverse(char s[], int i, int j)
{
	int c;
	if (j != 0)
	{
		do_reverse(s,++i, --j);
		if (j < i)
		{
			c = s[j];
			s[j] = s[i];
			s[i] = c;
		}
	}
}

void reverse(char s[])
{
	do_reverse(s, 0, strlen(s) - 1);
}

// itoa, recursion version
void itoa_r(int n)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}
	if (n / 10)
	{
		itoa_r(n / 10);
	}
	putchar((n % 10) + '0');
}

#define swap(t,x,y) \
{t c = x; x = y; y = c;}


int main()
{
	/*char s1[18] = "a-b-c-d";
	char s2[] = "abcd0123456789";

	expand(s1, s2);
	for (size_t i = 0; i < strlen(s1); i++)
	{
		cout << s1[i];
	}*/
	//int iArray[] = { 1,2,3,4 };
	//cout << binsearch(5, iArray, 4);
	/*int iii;
	char s[MAXLINE], u[MAXLINE];
	char t[] = "j\tkmn\nh";
	escape(s, t);
	reverse_escape(u, s);
	for (int iii = 0; u[iii] != '\0'; iii++)
	{
		putchar(u[iii]);
	}*/
	//printf("%s", s);
	//cout << c;

	//string s{ "<=" };
	//cout << s

	//cout << -0x0A;
	/*double x{ 4.0 }, y{ 10.0 };
	cout << (int)x % (int)y;*/

	//const char x[4] = "bye";

	//const char(&y)[4] = x;

	//const char[4] &z = x;

	//int a = 1, b = 2;
	//auto x = make_pair( "mn", make_pair(int(1),int(2)) );

	//itoa_r(-123);

	//char s[7] = "12345-";
	//reverse(s);

	int p[2] = { 1,2 };

	cout << *p;
	


	return 0;
}


