// Base.cpp : Defines the entry point for the console application.
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



/*class Base {
public:
	void pub_mem(); // public member 
	//void memfcn(Base &b) { b = *this; }
protected:
	int prot_mem; // protected member 
private: 
	char priv_mem; // private member 
};

class Sneaky : public Base{
	friend void clobber(Sneaky&); // can access Sneaky::prot_mem 
	friend void clobber(Base&); // can't access Base::prot_mem
	//void memfcn(Base &b) { b = *this; }
	int j; // j is private by default 
};

struct Pub_Derv : public Base { // ok: derived classes can access protected members 
	int f() { return prot_mem; }
	//void memfcn(Base &b) { b = *this; }
	// error: private members are inaccessible to derived classes char g() { return priv_mem; } 
};
struct Priv_Derv : private Base
{ // private derivation doesn't affect access in the derived class 
	//void memfcn(Base &b) { b = *this; }
	int f1() const { return prot_mem; }
};
struct Prot_Derv : protected Base
{ // private derivation doesn't affect access in the derived class 
	//void memfcn(Base &b) { b = *this; }
	int f2() const { return prot_mem; }
};
struct Derived_from_Public : public Pub_Derv
{ // ok: Base::prot_mem remains protected in Pub_Derv 
	//void memfcn(Base &b) { b = *this; }
	int use_base() { return prot_mem; }
};
struct Derived_from_Private : public Priv_Derv
{ // error: Base::prot_mem is private in Priv_Derv int use_base() { return prot_mem; } 
	//void memfcn(Base &b) { b = *this; }
};
struct Derived_from_Protected : public Prot_Derv
{ // error: Base::prot_mem is private in Priv_Derv int use_base() { return prot_mem; } 
	void memfcn(Base &b) { b = *this; }
};*/


class Base { 
public: 
	virtual int fcn()
	{
		cout << "base version";
		return 0;
	}
};

class D1 : public Base {
public: // hides fcn in the base; this fcn is not virtual // D1 inherits the definition of Base::fcn()
	
	int fcn(int); // parameter list differs from fcn in Base 
	//virtual void f2(); // new virtual function that does not exist in Base 
protected:
	using Base::fcn;
	virtual int fcn() override
	{
		cout << "D1 version";
		return 0;
	}
};

class D2 : public D1{ 
public: 
	int fcn(int); // nonvirtual function hides D1::fcn(int) 
	int fcn() override // overrides virtual fcn from Base 
	{
		cout << "D2 version";
		return 0;
	}
	//void f2(); // overrides virtual f2 from D1
};
	


int main()
{
	/*Pub_Derv D1{};
	Priv_Derv D2{};
	Prot_Derv D3{};
	Derived_from_Public DD1{};
	Derived_from_Private DD2{};
	Derived_from_Protected DD3{};
	Base *p = &D1;
	p = &DD1;*/

	Base bobj; D1 d1obj; D2 d2obj; Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj; 
	bp1->fcn(); // virtual call, will call Base::fcn at run time 
	bp2->fcn(); // virtual call, will call Base::fcn at run time 
	bp3->fcn(); // virtual call, will call D2::fcn at run time 
	
	/*D1 *d1p = &d1obj; D2 *d2p = &d2obj; 
	//bp2->f2(); // error: Base has no member named f2 
	d1p->f2(); // virtual call, will call D1::f2( ) at run time 
	d2p->f2(); // virtual call, will call D2::f2( ) at run time

Base *p1 = &d2obj; D1 *p2 = &d2obj; D2 *p3 = &d2obj; 
//p1->fcn(42); // error: Base has no version of fcn that takes an int 
p2->fcn(42); // statically bound, calls D1::fcn(int) 
p3->fcn(42); // statically bound, calls D2::fcn(int)*/
    return 0;
}

