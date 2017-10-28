// Nested_Classes.cpp : Defines the entry point for the console application.
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
#include<map>
#include<set>
#include "Sales_data.h"

using namespace std;

//using line_no = std::vector<std::string>::size_type;


class TextQuery
{
public:
	class QueryResult; // declaration needed for return type in the query function 
	using line_no = std::vector<std::string>::size_type; 
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
	TextQuery(const TextQuery &Tq) : file(make_shared<std::vector<std::string>>(*(Tq.file))) // copy constructor
	{
		for (auto x = Tq.wm.begin(); x != Tq.wm.end(); ++x)
		{
			wm[x->first] = make_shared<set<line_no>>(*(x->second));
		}
	}
	TextQuery &operator=(const TextQuery &Tq)
	{
		file = make_shared<std::vector<std::string>>(*(Tq.file));
		for (auto x = Tq.wm.cbegin(); x != Tq.wm.cend(); ++x)
		{
			wm[x->first] = make_shared<set<line_no>>(*(x->second));
		}
		return *this;
	}
	~TextQuery() {}
private:
	std::shared_ptr<std::vector<std::string>> file; // input file 
													//map of each word to the set of the lines in which that word appears 
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
// read the input file and build the map of lines to line numbers 
TextQuery::TextQuery(ifstream &is) :file(new vector<string>)
{
	string text;
	while (getline(is, text))
	{
		// for each line in the file 
		(file)->push_back(text); // remember this line of text 
		int n = (file)->size() - 1; // the current line number 
		istringstream line(text); // separate the line into words 
		string word;
		while (line >> word)
		{ // for each word in that line 
		  // if word isn't already in wm, subscripting adds a new entry 
			auto &lines = wm[word]; // lines is a shared_ptr 
			if (!lines) // that pointer is null the first time we see word
				lines.reset(new set<line_no>); // allocate a new set 
			lines->insert(n); // insert this line number 
		}
	}
}
class TextQuery::QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
	QueryResult(const QueryResult &Qr) : sought(Qr.sought), lines(make_shared<std::set<line_no >>(*(Qr.lines))), file(make_shared<std::vector<std::string>>(*(Qr.file))) {}
	QueryResult &operator=(const QueryResult &Qr)
	{
		sought = Qr.sought;
		lines = make_shared<std::set<line_no >>(*(Qr.lines));
		file = make_shared<std::vector<std::string>>(*(Qr.file));
		return *this;
	}
	~QueryResult() {}
	set<line_no>::iterator begin() const;
	//TextQuery(const TextQuery &Tq) : file(make_shared<std::vector<std::string>>(*(Tq.file)))
	set<line_no>::iterator end() const;
	std::shared_ptr<std::vector<std::string>> get_file() const;

private: std::string sought; // word this query represents 
		 std::shared_ptr<std::set<line_no>> lines; // lines it's on
		 std::shared_ptr<std::vector<std::string>> file; // input file 
};

TextQuery::QueryResult TextQuery::query(const string &sought) const
{ // we'll return a pointer to this set if we don't find sought
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	// use find and not a subscript to avoid adding words to wm!
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file); // not found 
	else
		return QueryResult(sought, loc->second, file);
}

set<TextQuery::line_no>::iterator TextQuery::QueryResult::begin() const
{
	return (*lines).begin();
}

set<TextQuery::line_no>::iterator TextQuery::QueryResult::end() const
{
	return lines->end();
}

std::shared_ptr<std::vector<std::string>> TextQuery::QueryResult::get_file() const
{
	return file;
}
ostream &print(ostream & os, const TextQuery::QueryResult &qr)
{ // if the word was found, print the count and all occurrences 
	os << qr.sought << " occurs " << qr.lines->size() << " " << ((qr.lines->size() > 1) ? "times" : "time") << endl;
	// print each line in which the word appeared 
	for (auto num : *qr.lines) // for every element in the set 
							   // don't confound the user with text lines starting at 0 
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
	return os;
}

class Token
{
public: // copy control needed because our class has a union with a string member 
		//defining the move constructor and move-assignment operator is left as an exercise 
	Token() :tok(INT), ival{ 0 } { }
	Token(const Token &t) : tok(t.tok) { copyUnion(t); }
	Token &operator =(const Token&);
	// if the union holds a string, we must destroy it; see § 19.1.2 (p. 824)
	~Token()
	{
		if (tok == STR)
			sval. ~string();
		else if (tok == SDATA)
			s_dval. ~Sales_data();
	}
	Token(Token &&t) noexcept : tok(std::move(t.tok)) { moveUnion(std::move(t)); }
	Token &operator=(Token &&t)noexcept;
	// assignment operators to set the differing members of the union 
	Token &operator = (const std::string&);
	Token &operator = (const Sales_data&);
	Token &operator = (char);
	Token &operator = (int);
	Token &operator = (double);
private:
	enum { INT, CHAR, DBL, STR, SDATA } tok; // discriminant 
	union { // anonymous union 
		char cval; int ival; double dval; std::string sval; Sales_data s_dval;
	}; // each Token object has an unnamed member of this unnamed union type 
	   // check the discriminant and copy the union member as appropriate 
	void copyUnion(const Token&);
	void moveUnion(Token &&t);
};

Token &Token:: operator =(int i)
{
	if (tok == STR)
		sval. ~string(); // if we have a string, free it 
	else if (tok == SDATA)
		s_dval. ~Sales_data(); // else if we have a Sales_data, free it 
	ival = i; // assign to the appropriate member 
	tok = INT; // update the discriminant 
	return *this;
}

Token &Token:: operator =(char i)
{
	if (tok == STR)
		sval. ~string(); // if we have a string, free it 
	else if (tok == SDATA)
		s_dval. ~Sales_data(); // else if we have a Sales_data, free it 
	cval = i; // assign to the appropriate member 
	tok = CHAR; // update the discriminant 
	return *this;
}

Token &Token:: operator =(double i)
{
	if (tok == STR)
		sval. ~string(); // if we have a string, free it 
	else if (tok == SDATA)
		s_dval. ~Sales_data(); // else if we have a Sales_data, free it 
	dval = i; // assign to the appropriate member 
	tok = DBL; // update the discriminant 
	return *this;
}

Token &Token:: operator =(const std::string &s)
{
	if (tok == STR) // if we already hold a string, just do an assignment 
		sval = s;
	else
	{
		if (tok == SDATA)
			s_dval. ~Sales_data(); // else if we have a Sales_data, free it
		new(&sval) string(s); // otherwise construct a string   
	}
	tok = STR; // update the discriminant 
	return *this;
}

Token &Token:: operator =(const Sales_data &sd)
{
	if (tok == SDATA) // if we already hold a Sales_data, just do an assignment 
		s_dval = sd;
	else
	{
		if (tok == STR)
			sval. ~string(); // else if we have a string, free it
		new(&s_dval) Sales_data(sd); // otherwise construct a sales_data   
	}
	tok = SDATA; // update the discriminant 
	return *this;
}

void Token::copyUnion(const Token &t)
{
	switch (t.tok)
	{
	case Token::INT: ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL: dval = t.dval; break;
		// to copy a string/sales_data construct it using placement new; see (§ 19.1.2 (p. 824)) 
	case Token::STR: new(&sval) string(t.sval); break;
	case Token::SDATA: new(&s_dval) Sales_data(t.s_dval); break;
	}
}

// common operations for move
void Token::moveUnion(Token &&t)
{
	switch (t.tok) {
	case Token::INT: ival = std::move(t.ival); break;
	case Token::CHAR: cval = std::move(t.cval); break;
	case Token::DBL: dval = std::move(t.dval); break;
	case Token::STR: new(&sval) std::string(std::move(t.sval)); break;
		// to copy a Sales_data, construct it using placement new
	case Token::SDATA: new(&s_dval) Sales_data(std::move(t.s_dval)); break;
	}
}

Token &Token:: operator =(const Token &t)
{
	// if this object holds a string/Sales_data and t doesn't, we have to free the old string / Sales_data
	if (tok == STR && t.tok != STR)
		sval. ~string();
	if (tok == SDATA && t.tok != SDATA)
		s_dval. ~Sales_data();
	if (tok == STR && t.tok == STR)
		sval = t.sval; // no need to construct a new string 
	else if (tok == SDATA && t.tok == SDATA)
		s_dval = t.s_dval; // no need to construct a new Sales_data
	else
		copyUnion(t); // will construct a string if t.tok is STR 
	tok = t.tok;
	return *this;
}

Token &Token::operator=(Token &&t)noexcept
{
	if (this != &t)
	{	// if this object holds a string/Sales_data and t doesn't, we have to free the old string / Sales_data
		if (tok == STR && t.tok != STR)
			sval. ~string();
		if (tok == SDATA && t.tok != SDATA)
			s_dval. ~Sales_data();
		if (tok == STR && t.tok == STR)
			sval = std::move(t.sval); // no need to construct a new string 
		else if (tok == SDATA && t.tok == SDATA)
			s_dval = std::move(t.s_dval); // no need to construct a new Sales_data
		else
			moveUnion(std::move(t)); // will construct a string if t.tok is STR 
		tok = std::move(t.tok);
	}
	return *this;
}



int main(int argc, char *argv[])
{
	///string s{"boy"};
	ifstream Input_file(argv[1]);
	ifstream Input_file2(argv[2]);
	//TextQuery Tq(ifstream(argv[1]));
	TextQuery Tq(Input_file);
	TextQuery cTq(Input_file2);
	//Tq.query(string("boy"));
	//print(cout, Tq.query(string("boy")));
	Tq = cTq;
	TextQuery::QueryResult Qr = Tq.query(string("boy"));
	TextQuery::QueryResult cQr = cTq.query(string("boy"));
	Qr = cQr;
	//auto y = (Tq.query(s)).begin();
	auto y = Qr.begin();
	cout << *y;
	return 0;
}


