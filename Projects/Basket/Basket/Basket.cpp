// Basket.cpp : Defines the entry point for the console application.
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
#include<set>
#include"Quote_Bulk_Quote.h"

using namespace std;


class Basket {
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs);
public: // Basket uses synthesized default constructor and copy-control members
	/*void add_item(const std::shared_ptr<Quote> &sale) 
	{ 
		items.insert(sale); 
	} // prints the total price for each book and the overall total for all items in the basket */
	void add_item(const Quote& sale) // copy the given object
	{
		items.insert(std::shared_ptr<Quote>(sale.clone()));
	}
	void add_item(Quote&& sale) // move the given object 
	{
		items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
	}
	double total_receipt(std::ostream&) const;
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> myitems()
	{
		return items;
	}
private: // function to compare shared_ptr s needed by the multiset member 
	 // multiset to hold multiple quotes, ordered by the compare member
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
};

bool Basket::compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) {
	return lhs->isbn() < rhs->isbn();
}

double Basket::total_receipt(ostream &os) const {
	double sum = 0.0; // holds the running total 
	// iter refers to the first element in a batch of elements with the same ISBN 
	// upper_bound returns an iterator to the element just past the end of that batch 
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
	{ // we know there's at least one element with this key in the Basket 
	  // print the line item for this book 
		sum += print_total(os, **iter, items.count(*iter)); 
	} 
	os << "Total Sale: " << sum << endl; // print the final overall total 
	return sum; 
}






int main()
{
	Basket myBasket{};
	Quote Notes{ "052109982775",1.25 };
	Quote Notes1{ "052109982775",1.25 };
	Bulk_quote Notes2{ "052109982775", 1.25, 4, 0.25 };

	//vector<Quote>Qvec{ Notes, Notes1, Notes2 };
	vector<shared_ptr<Quote>>SQvec{ make_shared<Quote>(Notes), make_shared<Quote>(Notes1), make_shared<Bulk_quote>(Notes2) };

	double total{};

	//for each (auto var in SQvec)
	//{
	//	total += var->net_price(5);
	//}

	for each (auto var in SQvec)
	{
		myBasket.add_item(*var);
	}

	for each (auto var in myBasket.myitems())
	{
		total += var->net_price(5);
	}

	//total = myBasket.total_receipt(cout);

	cout << total;
	//Quote Notes3{ std::move(Notes)};

	//Notes = Notes1;

	//Limit_quote Notes3{ "052109982775", 1.25, 4, 0.25 };

	//cout << Notes3.net_price(10);

	//Disc_quote Notes4{ "052109982775", 1.25, 4, 0.25 };

	//Notes2.Debug();

	//print_total(cout, &Notes2, 5);

	//cout << total;

    return 0;
}

