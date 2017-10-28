// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include"StrBlob.h"
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
//#include<stdio.h>

using namespace std;

void Textquery(const char *cString, vector<string> &svec, map<string,set<size_t>> &mstr_set) 
{
	ifstream Input(cString);
	string s{}, is{};
	size_t iii{};
	while (getline(Input, s))
	{
		++iii;
		istringstream my_stringstream(s);
		while (my_stringstream >> is)
		{
			mstr_set[is].insert(iii);
		}
		svec.push_back(s);
	}
}

void Queryresult(const string &s, const vector<string> &svec, const map<string,set<size_t>> &mstr_set)
{
	for each (auto var in mstr_set)
	{
		if (var.first == s)
		{
			cout << s << "occured" << var.second.size() << ((var.second.size() > 1) ? "times" : "time") << endl;
			for (auto i = ((var.second).cbegin()); i != ((var.second).cend()); i++)
			{
				cout << "(" << "line" << *i << ")" << svec[(*i) - 1] << ";" << endl;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	vector<string>svec{};
	map<string, set<size_t>>mstr_set{};
	Textquery(argv[1], svec, mstr_set);
	do
	{
		cout << "enter the word to look for : ";
		string s{};
		if (!(cin >> s) || s == "q")
		{
			break;
		}
		Queryresult(s, svec, mstr_set);
	} while (true);
    return 0;
}

