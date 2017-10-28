// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<new>
#include<memory>
#include<vector>
#include<algorithm>


using namespace std;

/*struct X {
	X() { std::cout << "X()" << std::endl; }
	X(const X&) { std::cout << "X(const X&)" << std::endl; }
	X &operator = (const X &x) { std::cout << "X &operator = (const X &x)" << std::endl; return *this; }
	~X() { std::cout << "~X()" << std::endl; }
};

void myfunc(int x, const X y)
{
	cout << x << endl;
}*/



/*class numbered
{
public:
	numbered() { mysn += 1; }
	numbered(const numbered &x) : mysn(x.mysn + 1) {}
	~numbered() {}
	int mysn{};
private:

};

void f(const numbered &s)
{
	cout << s.mysn << endl;

}*/

class Employee
{
public:
	Employee() : ID(++Static_member) {}
	Employee(const string &s) : Name(s), ID(++Static_member) {}
	Employee(const Employee &e) : ID(++Static_member), Name(e.Name) {}
	Employee &operator = (const Employee &) { return *this; }
	size_t my_ID() { return ID; }
	~Employee() {}

private:
	static size_t Static_member;
	size_t ID{};
	string Name{};

};

size_t Employee::Static_member{};

class HasPtr {
	friend void swap(HasPtr &x, HasPtr &y);
public:
	HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
	HasPtr(const HasPtr &y) : i(y.i), ps(new string(*(y.ps))) { cout << "copy constructed"; }
	HasPtr(HasPtr &&rhs) : i(std::move(rhs.i)), ps(std::move(new std::string(*rhs.ps)))
	{
		rhs.ps = 0;
		cout << "move constructed";
	}
	/*HasPtr &operator = (const HasPtr &y)
	{
		auto x = new string(*(y.ps));
		delete ps;
		ps = x;
		i = y.i;
		return *this;
	}*/
	/*HasPtr& operator=(HasPtr rhs) 
	{ 
		swap(*this, rhs);
		cout << "copy swapped";
		return *this; 
	} // copy and swap assignment*/
	HasPtr& operator=(const HasPtr &rhs)
	{
		auto new_pt = new std::string(*rhs.ps);
		delete ps;
		ps = std::move(new_pt);
		i = std::move(rhs.i);
		cout << "copy assigned";
		return *this;
	}
	HasPtr& operator=(HasPtr &&rhs)
	{
		if (this != &rhs)
		{
			delete ps;
			ps = std::move(new std::string(*rhs.ps));
			i = std::move(rhs.i);
			rhs.ps = 0;
		}
		cout << "move assigned";
		return *this;
	}
	~HasPtr() { delete ps; }
	bool operator < (const HasPtr &rhs)
	{
		return *ps < *(rhs.ps); 
	}

	/*void swap(HasPtr &y)
	{
		auto s = *(y.ps);
		using std::swap;
		swap(*(ps), *(y.ps));
		swap(i, y.i);
		if (*(ps) == s)
		{
			cout << "successful swap";
		}
	}*/
	std::string *ps;
private:
	 int i;
	 //std::string *ps;
};

void swap(HasPtr &x, HasPtr &y)
{
	auto s = *(y.ps);
	using std::swap;
	swap(*(x.ps), *(y.ps));
	swap(x.i, y.i);
	if (*(x.ps) == s)
	{
		cout << "successful swap";
	}
}








int main()
{
	


	/*X x{};
	myfunc(1, x);
	vector<X>z(3);
	numbered a, b = a, c = b;

	f(a); f(b); f(c);

	

	Employee y;
	Employee z = y;
	Employee x("adam");
	y = x;
	cout << y.my_ID() << x.my_ID() << z.my_ID();*/

	HasPtr x(string("jhg"));
	HasPtr y(string("kj"));
	//swap(x, y);
	//x.swap(y);
	y = HasPtr(string("kkkkkk")); // x;

	cout << *(y.ps);
	
	//cout << (x < y);

	//HasPtr a("kjiu"), b("kjill"), c("gdvcf"), d("aaaaaa");
	

	//vector<HasPtr>vec_Hasptr{ a, b, c, d};
	//sort(vec_Hasptr.begin(), vec_Hasptr.end());
	/*for each (const HasPtr &var in vec_Hasptr)
	{
		cout << *(var.ps) << endl;
	}*/

	


    return 0;
}

