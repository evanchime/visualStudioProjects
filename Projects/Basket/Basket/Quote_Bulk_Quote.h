#pragma once

#ifndef QUOTE_BULK_QUOTE
#define QUOTE_BULK_QUOTE
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
class Quote {
public:
	Quote() = default; // = default see � 7.1.4 (p. 264) 
	Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { cout << "Quote condtructor\n"; }
	std::string isbn() const {
		return bookNo;
	}
	Quote(const Quote &Q) : bookNo(Q.bookNo), price(Q.price) { cout << " Quote copy constructor\n"; } // copy constructor
	Quote(Quote &&Q) : bookNo(std::move(Q.bookNo)), price(std::move(Q.price)) { cout << " Quote move constructor\n"; } // move constructor
	Quote &operator=(Quote &&Q) { // move assignment operator
		bookNo = std::move(Q.bookNo);
		price = std::move(Q.price);
		cout << " Quote move assignment\n";
		return *this;
	}
	Quote &operator=(const Quote &Q) { // assignment operator
		bookNo = Q.bookNo;
		price = Q.price;
		cout << " Quote copy assignment\n";
		return *this;
	}
	// returns the total sales price for the specified number of items // derived classes will override and apply different discount algorithms 
	virtual double net_price(std::size_t n) const {
		return n * price;
	}
	// returns the average sales price for the specified number of items // derived classes will override and apply different discount algorithms 
	virtual double average_price(std::size_t n) const {
		return (n * price) / n;
	}
	// virtual debug function for the Quote class hierarchy that displays the data members of the respective classes.
	virtual void Debug() const
	{
		cout << bookNo << " " << price;
	}
	virtual Quote* clone() const & {
		return new Quote(*this);
	}
	virtual Quote* clone() &&
	{
		return new Quote(std::move(*this));
	}
	virtual ~Quote() = default; // dynamic binding for the destructor 
								//~Quote(){ cout << " Quote destructor\n"; }
private:
	std::string bookNo; // ISBN number of this item 
protected:
	double price = 0.0; // normal, undiscounted price 
};




// calculate and print the price for the given number of copies, applying any discounts 
double print_total(ostream &os, const Quote &item, size_t n)
{ // depending on the type of the object bound to the item parameter 
  // calls either Quote::net_price or Bulk_quote::net_price 
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() // calls Quote::isbn 
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

double print_total(ostream &os, const Quote *item, size_t n)
{ // depending on the type of the object bound to the item parameter 
  // calls either Quote::net_price or Bulk_quote::net_price 
	auto ret = item->net_price(n);
	os << "ISBN: " << item->isbn() // calls Quote::isbn 
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) { }
	double net_price(std::size_t) const = 0;
	double average_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0; // purchase size for the discount to apply 
	double discount = 0.0; // fractional discount to apply 
};

class Limit_quote : public Disc_quote { // Limit_quote inherits from Disc_quote 
public:
	Limit_quote() = default;
	Limit_quote(const std::string&, double, std::size_t, double); // overrides the base version in order to implement the bulk purchase discount policy 
	double net_price(std::size_t) const override;
	double average_price(std::size_t) const override;
	void Debug() const override;
private:
	std::size_t Max_quantity = 10; // maximum purchase for the discount to discontinue
								   //double discount = 0.0; //fractional discount to apply
};


Limit_quote::Limit_quote(const std::string &book, double p, std::size_t min_qty, double disc) :
	Disc_quote(book, p, min_qty, disc) {}

double Limit_quote::net_price(size_t cnt)const
{
	if ((cnt >= quantity) && (cnt <= Max_quantity))
	{
		return cnt * (1 - discount) * price;
	}
	else
		return cnt * price;
}

double Limit_quote::average_price(std::size_t cnt) const
{
	if ((cnt >= quantity) && (cnt <= Max_quantity))
	{
		return (cnt * (1 - discount) * price) / cnt;
	}
	else
		return (cnt * price) / cnt;
}

void Limit_quote::Debug() const
{
	cout << isbn() << " " << price << " " << quantity << " " << discount;
}

class Bulk_quote : public Disc_quote { // Bulk_quote inherits from Quote 
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double); // overrides the base version in order to implement the bulk purchase discount policy 
	Bulk_quote(const Bulk_quote &Q) : Disc_quote(Q) { cout << " Bulk_quote copy constructor\n"; } // copy constructor
	Bulk_quote(Bulk_quote &&Q) : Disc_quote(std::move(Q)) { cout << " Bulk_quote move constructor\n"; } // move constructor
	Bulk_quote &operator=(const Bulk_quote &Q) { // assignment operator
		Disc_quote::operator=(Q);
		cout << " Bulk_quote copy assignment\n";
		return *this;
	}
	Bulk_quote &operator=(Bulk_quote &&Q) { // assignment operator
		Disc_quote::operator=(std::move(Q));
		cout << " Bulk_quote move assignment\n";
		return *this;
	}
	// virtual ~Quote() override { cout << " Quote destructor\n"; }
	~Bulk_quote() { cout << " Bulk_Quote destructor\n"; }
	double net_price(std::size_t) const override;
	double average_price(std::size_t) const override;
	void Debug() const override;
	Bulk_quote* clone() const &
	{
		return new Bulk_quote(*this);
	}
	Bulk_quote* clone() &&
	{
		return new Bulk_quote(std::move(*this));
	}
private:
	/*std::size_t min_qty = 0; // minimum purchase for the discount to apply
	double discount = 0.0; //fractional discount to apply*/
};

Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) :
	Disc_quote(book, p, qty, disc) {
	cout << " Bulk_Quote constructor\n";
}

double Bulk_quote::net_price(size_t cnt)const
{
	if (cnt >= quantity)
	{
		return cnt * (1 - discount) * price;
	}
	else
		return cnt * price;
}

double Bulk_quote::average_price(std::size_t cnt) const
{
	if (cnt >= quantity)
	{
		return (cnt * (1 - discount) * price) / cnt;
	}
	else
		return (cnt * price) / cnt;
}

void Bulk_quote::Debug() const
{
	cout << isbn() << " " << price << " " << quantity << " " << discount;
}

#endif // !QUOTE_BULK_QUOTE
