// greetingsconsoleapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
	const char *p = "fff";
	char a[4] = { 'f','f', 'f','\0' };

	if (strcmp(p, a) == 0)
		cout << 1 << " " <<  p << " " << a;
	else
		cout << 0;
	//cout << "hello\n";
    return 0;
}

