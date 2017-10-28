// itob.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include<algorithm>
#include<fstream>
#include<functional>

using namespace std;



int htoi(char s[])
{
	int iii, n;
	n = 0;
	for (iii = 0; (s[iii] >= '0' && s[iii] <= '9') || (s[iii] >= 'a' && s[iii] <= 'z') || (s[iii] >= 'A' && s[iii] <= 'Z'); ++iii)
	{
		if (s[iii] >= 'a' && s[iii] <= 'f')
		{
			n = (16 * n) + 10 + (s[iii] - 'a');
		}
		else if(s[iii] >= 'A' && s[iii] <= 'F')
		{
			s[iii] += 'a' - 'A';
			n = (16 * n) + 10 + (s[iii] - 'a');
		}
		else if (s[iii] >= '0' && s[iii] <= '9')
		{
			n = (16 * n) + (s[iii] - '0');
		}

	}
	return n;
}


int main()
{
   
	return 0;



}

