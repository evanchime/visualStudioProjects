// findbook.cpp : Defines the entry point for the console application.
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
#include"Sales_data.h"
#include<math.h>
#include<utility>
#include<algorithm>
#include<tuple>
#include<numeric>

#define MAXLINE 1000


using namespace std;

typedef vector<Sales_data>::const_iterator citerator;
typedef vector<Sales_data>::size_type stype;
class my_aux_class
{
public:
	my_aux_class() = default;
	my_aux_class(const stype &index, citerator &pos1, citerator &pos2) : index(index), pos1(pos1), pos2(pos2) {}
	my_aux_class(my_aux_class &&x) noexcept : index(x.index), pos1(x.pos1), pos2(x.pos2) {}
	~my_aux_class()
	{
	}

//private:
	stype index{};
	citerator pos1{};
	citerator pos2{};
};


// matches has three members: an index of a store and iterators into that store's vector 
typedef tuple <vector <Sales_data>::size_type, vector <Sales_data>::const_iterator, vector <Sales_data >::const_iterator> matches; 
// files holds the transactions for every store 
// findBook returns a vector with an entry for each store that sold the given book 
/*vector <matches> findBook(const vector <vector <Sales_data>> &files, const string &book) 
{
	vector <matches> ret; // initially empty 
	// for each store find the range of matching books, if any 
	for (auto it = files.cbegin(); it != files.cend(); ++it) 
	{ // find the range of Sales_data that have the same ISBN
	auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn); 
	if (found.first != found.second) // this store had sales 
	// remember the index of this store and the matching range
		ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second)); 
	} 
	return ret; // empty if no matches found
}*/

vector <my_aux_class> findBook(const vector <vector <Sales_data>> &files, const string &book)
{
	vector <my_aux_class> ret; 
							   // for each store find the range of matching books, if any 
	for (auto it = files.cbegin(); it != files.cend(); ++it)
	{ // find the range of Sales_data that have the same ISBN
		auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
		if (found.first != found.second) // this store had sales 
		// remember the index of this store and the matching range
			ret.push_back(my_aux_class((it - files.cbegin()), found.first, found.second));
	}
	return ret; // empty if no matches found
}
/*void reportResults(istream &in, ostream &os, const vector < vector < Sales_data > > &files)
{
	string s; // book to look for 
	while (in >> s) 
	{ 
		auto trans = findBook( files, s); // stores that sold this book 
	if (trans.empty()) {
		cout << s << " not found in any stores" << endl; 
		continue; // get the next book to look for
	} 
	for (const auto &store : trans) // for every store with a sale // get <n> returns the specified member from the tuple in store 
		os << "store " << get <0>(store) << " sales: " <<
			accumulate(get <1>(store), get <2>(store), Sales_data(s)) << endl;
	} 
}*/

void reportResults(istream &in, ostream &os, const vector <vector <Sales_data>> &files)
{
	string s; // book to look for 
	while (in >> s)
	{
		auto trans = findBook(files, s); // stores that sold this book 
		if (trans.empty()) {
			cout << s << " not found in any stores" << endl;
			continue; // get the next book to look for
		}
		for (const auto &store : trans) // for every store with a sale // get <n> returns the specified member from the tuple in store 
			os << "store " << store.index << " sales: " <<
			accumulate(store.pos1, store.pos2, Sales_data(s)) << endl;
	}
}



int main()
{
	vector<Sales_data>savec{ { "aaaa", 3, 23.10 },{ "aaaa", 3, 23.10 },{ "ssss", 2, 21.10 } };
	vector<Sales_data>savec1{ { "0000", 3, 23.10 },{ "aaaa", 3, 23.10 },{ "ssss", 2, 21.10 } };
	vector<Sales_data>savec2{ { "222222", 3, 23.10 },{ "aaaa", 3, 23.10 },{ "ssss", 2, 21.10 } };
	vector<vector<Sales_data>>v_v_sales{ savec,savec1,savec2 };

	reportResults(cin, cout, v_v_sales);
    return 0;
}

