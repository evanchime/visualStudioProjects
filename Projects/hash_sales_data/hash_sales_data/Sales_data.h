#pragma once
/*
* This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
* Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
* copyright and warranty notices given in that book:
*
* "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
*
*
* "The authors and publisher have taken care in the preparation of this book,
* but make no expressed or implied warranty of any kind and assume no
* responsibility for errors or omissions. No liability is assumed for
* incidental or consequential damages in connection with or arising out of the
* use of the information or programs contained herein."
*
* Permission is granted for this code to be used for educational purposes in
* association with the book, given proper citation if and when posted or
* reproduced.Any commercial use of this code requires the explicit written
* permission of the publisher, Addison-Wesley Professional, a division of
* Pearson Education, Inc. Send your request for permission, stating clearly
* what code you would like to use, and in what specific way, to the following
* address:
*
* 	Pearson Education, Inc.
* 	Rights and Permissions Department
* 	One Lake Street
* 	Upper Saddle River, NJ  07458
* 	Fax: (201) 236-3290
*/

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<iterator>
#include<utility>


using namespace std;

template <typename T> struct std::hash;

class Sales_data {
	friend struct std::hash <Sales_data>;
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
	friend ostream &operator <<(ostream &os, const Sales_data &item);
	friend istream &operator >> (istream &is, Sales_data &item);
public:
	// constructors
	// using the synthesized version is safe only
	// if we can also use in-class initializers
	Sales_data() : units_sold(0), revenue(0.0) { }
	Sales_data(const std::string &s) : bookNo(s), units_sold(0), revenue(0.0) { }
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n) { }
	Sales_data(std::istream &);

	// operations on Sales_data objects
	Sales_data &operator+=(const Sales_data &rhs);
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	bool operator == (const Sales_data &rhs) const
	{
		return (*this).isbn() == rhs.isbn()
			&& (*this).units_sold == rhs.units_sold
			&& (*this).revenue == rhs.revenue;
	}
	bool operator!= (const Sales_data &rhs) {
		return !((*this) == rhs);
	}
private:
	std::string bookNo;
	unsigned units_sold;
	double revenue;
};


// nonmember Sales_data interface functions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

// used in future chapters
inline
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}

Sales_data::Sales_data(std::istream &is)
{
	// read will read a transaction from is into this object
	read(is, *this);
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;

}

double
Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

// add the value of the given Sales_data into this object
Sales_data&
Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold; // add the members of rhs into 
	revenue += rhs.revenue;       // the members of ``this'' object
	return *this; // return the object on which the function was called
}

Sales_data
add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;  // copy data members from lhs into sum
	sum.combine(rhs);      // add data members from rhs into sum
	return sum;
}

// transactions contain ISBN, number of copies sold, and sales price
istream&
read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream&
print(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

ostream &operator <<(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " <<
		item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}
istream &operator >> (istream &is, Sales_data &item)
{
	double price; // no need to initialize; we'll read into price before we use it 
	is >> item.bookNo >> item.units_sold >> price;
	if (is) // check that the inputs succeeded 
		item.revenue = item.units_sold * price;
	else item = Sales_data(); // input failed: give the object the default state 
	return is;
}
// assumes that both objects refer to the same book 

Sales_data operator +(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs; // copy data members from lhs into sum 
	sum += rhs; // add rhs into sum 
	return sum;
}

// open the std namespace so we can specialize std:: hash 
namespace std {} // close the std namespace
namespace std
{
	template <> // we're defining a specialization with 
	struct hash <Sales_data> // the template parameter of Sales_data 
	{ // the type used to hash an unordered container must define these types 
		typedef size_t result_type;
		typedef Sales_data argument_type; // by default, this type needs == 
		size_t operator()(const Sales_data& s) const; // our class uses synthesized copy control and default constructor
	};
	size_t hash <Sales_data>:: operator()(const Sales_data& s) const
	{
		return hash <string>()(s.bookNo) ^ hash <unsigned>()(s.units_sold) ^
			hash <double>()(s.revenue);
	}
}

#endif

