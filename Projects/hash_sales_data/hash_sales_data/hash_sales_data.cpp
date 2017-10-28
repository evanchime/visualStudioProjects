// hash_sales_data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<new>
#include<memory>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include"Sales_data.h"


using namespace std;


int main()
{
	unordered_multiset<Sales_data>SDset{ { "aaaa", 3, 23.10 }, { "aaaa", 3, 23.10 }, { "bbbb", 3, 22.10 }, {"ssss", 4, 23.17},{ "bbbb", 3, 22.10 }, { "ssss", 4, 23.17 },{ "ssss", 4, 23.17 },
	{ "aaaa", 3, 23.10 }, { "bbbb", 3, 22.10 }, { "aaaa", 3, 23.10 }, { "bbbb", 3, 22.10 }, {"ssss", 4, 23.17} };
    
	for each (auto var in SDset)
	{
		cout << var << endl;
	}
	
	return 0;
}

