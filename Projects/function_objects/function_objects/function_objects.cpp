// function_objects.cpp : Defines the entry point for the console application.
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
using namespace std::placeholders;

class My_Fun_Objects
{
public:
	My_Fun_Objects(){}
	~My_Fun_Objects(){}

	int operator()(int x, int y, int z)
	{
		if (x > 0)
			return y;
		else
			return z;
	}

private:

};

/*class PrintString {
public: 
	PrintString(ostream &o = cout, char c = ' ') : os(o), sep(c) { } 
	void operator()(const string &s) const 
	{ os << s << sep; } 
private: 
	ostream &os; // stream on which to write 
	char sep; // character to print after each output 
};*/

class PrintString {
public:
	PrintString() { }
	string operator()() const
	{
		string s{};
		if (getline(cin, s))
			return s;
		else
			return s;
	}

	void operator()(vector<string> &svec) const
	{
		//int iii{};
		string s{};
		while(getline(cin, s))
			svec.push_back(s);
	}
private:
	//ostream &os; // stream on which to write 
	//char sep; // character to print after each output 
};

class Compare
{
public:
	Compare(int ii) : iii(ii) {}
	~Compare(){}

	bool operator()(int &i) { return (iii == i); }

private:
	int iii{};
};

class SizeComp {
public:
	SizeComp(size_t low, size_t high) : sz_low(low), sz_high(high) { } // parameter for each captured variable 
	SizeComp(size_t high) : sz_high(high) { } // parameter for each captured variable
	// call operator with the same return type, parameters, and body as the lambda 
	bool operator()(const string &s) const 
	{
		return (s.size() >= sz_low) && (s.size() <= sz_high);
	} 

	bool operator()(const string &s, int) const
	{
		return s.size() >= sz_high;
	}
private: 
	size_t sz_low; // a data member for each variable captured by value
	size_t sz_high; // a data member for each variable captured by value
};

class G_1024
{
public:
	G_1024(){}
	~G_1024(){}
	bool operator()(int x, int y)
	{
		return x > y;
	}
private:

};

class Not
{
public:
	Not(){}
	~Not(){}
	 
	bool operator()(const string &s1, const string &s2)
	{
		return s1 != s2;
	}

private:

};

class Multiply_by2
{
public:
	Multiply_by2(){}
	~Multiply_by2(){}

	void operator()(const int &x)
	{
		x * 2;
	}

private:

};


int main(int argc, char *argv[])
{
	vector<int>ivec{ 1,2,1027,1025,4,6 };
	transform(ivec.begin(), ivec.end(), ivec.begin(), bind(multiplies<int>(), _1, 2));
	for each (auto var in ivec)
	{
		cout << var << " ";
	}
	//auto x = count_if(ivec.begin(), ivec.end(), bind(G_1024{}, _1, 1024));
	//auto x = count_if(ivec.begin(), ivec.end(), bind(greater<int>(), 1, 1024));
	//cout << x;
	//vector<string>svec{ "pooh", "kkj", "mncbv", "vcxfxzcs"};
	//auto x = find_if(svec.begin(), svec.end(), bind(not_equal_to<string>(),"pooh", _1));
	//cout << *x;
	//cout << a;
	/*int iii{}, jjj{}, x{ 1 }, y{ 9 }, z{ 10 };
	SizeComp Bound(x, y);
	SizeComp one(z);
	string s{};
	ifstream Input(argv[1]);
	if (Input)
	{
		while (Input >> s)
		{
			if (Bound(s))
				++iii;
			else if (one(s,0))
				++jjj;
		}
		cout << iii << " words in the input file are of sizes " << x << " through " << y << endl;
		cout << jjj << " words in the input file are of sizes " << z << " or more";
	}
	
	//My_Fun_Objects a{};
	//PrintString a{};
	//Compare a( 4 );
	/*vector<int>ivec{1,2,4,6,5,4,3};
	replace_if(ivec.begin(), ivec.end(), Compare(4), 2);
	for each (auto var in ivec)
	{
		cout << var;
	}*/
	//a(int(2));
	//a(svec);
	//string s{};
	//cout << svec.size();

	

	
    return 0;
}

