// Foo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<new>
#include<memory>
#include<vector>
#include<algorithm>


using namespace std;
class Foo
{
public:
	Foo() : i(3){}
	Foo(const Foo &f) : i(f.i) {}
	Foo(Foo &&f) : i(std::move(f.i)) {}
	Foo &operator=(const Foo &f) { i = f.i; return *this; }
	Foo &operator=(Foo &&f) { i = std::move(f.i); return *this; }
	Foo sorted() const & {
		//Foo ret(*this);
		cout << " foo ";
		//return ret.sorted();
		return Foo(*this).sorted();
	}
	~Foo(){}

private:
	int i{};
};

int main()
{
	Foo x{};
	x.sorted();
    return 0;
}

