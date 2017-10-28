// Blob_BlobPtr_Templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>

using namespace std;

// forward declarations needed for friend declarations in Blob 
template <typename> class BlobPtr;
template <typename> class Blob; // needed for parameters in operator== 
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> bool operator<(const Blob<T>&, const Blob<T>&);

template <typename T> 
class Blob 
{// each instantiation of Blob grants access to the version of 
// BlobPtr and the equality operator instantiated with the same type 
	friend class BlobPtr<T>;
	friend bool operator==<T> (const Blob<T>&, const Blob<T>&);
	friend bool operator< <T>(const Blob<T> &, const Blob<T> &);
public: 
	typedef T value_type; 
	typedef typename std::vector<T>::size_type size_type; 
	// constructors 
	Blob(); 
	Blob(std::initializer_list<T> il); 
	template <typename it>
	Blob(it,  it);
	// number of elements in the Blob 
	size_type size() const { return data->size(); }
	bool empty() const 
	{
		return data->empty();
	} 
	// add and remove elements 
	void push_back(const T &t) {data->push_back(t);} 
	//move version; see § 13.6.3 (p. 548) 
	void push_back(T &&t) { data->push_back(std::move(t)); } 
	void pop_back(); // element access 
	T &front();
	const T &front() const;
	T &back(); 
	const T& back() const;
	T& operator[](size_type i); // defined in § 14.5 (p. 566)
	const T& operator[](size_type i) const;
	// interface to StrBlobPtr
	BlobPtr begin();  // can't be defined until StrBlobPtr is
	BlobPtr end();
private: 
	std::shared_ptr<std::vector<T>> data; 
	// throws msg if data[i] isn't valid 
	void check(size_type i, const std::string &msg) const;
};

template <typename T> 
void Blob<T>::check(size_type i, const std::string &msg) const 
{
	if (i >= data->size()) 
		throw std::out_of_range(msg);
}

template <typename T> 
inline T& Blob<T>::back() 
{
	check(0, "back on empty Blob"); 
	return data->back();
}

// Blob::front definition
template <typename T>
inline T &Blob<T>::front()
{
	if (data->size() > 0)
		return data->front();
}

// const Blob::front definition
template <typename T>
inline const T &Blob<T>::front() const
{
	if (data->size() > 0)
		return data->front();
}

template <typename T>
inline const T& Blob<T>::back() const
{
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T> 
inline T& Blob<T>::operator[](size_type i)
{ // if i is too big, check will throw, preventing access to a nonexistent element 
	check(i, "subscript out of range"); return (*data)[i];
}

template <typename T> 
inline const T& Blob<T>::operator[](size_type i) const
{ // if i is too big, check will throw, preventing access to a nonexistent element 
	check(i, "subscript out of range"); return (*data)[i];
}

template <typename T> 
inline void Blob<T>::pop_back()
{
	check(0, "pop_back on empty Blob"); 
	data ->pop_back();
}

template <typename T> 
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template <typename T> 
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }

template <typename T> template <typename it>
Blob<T>::Blob(it begin, it end) : data(std::make_shared<std::vector<T>>(begin, end)) {}

// equality operation definitions
template <typename T>
bool operator==(const Blob<T> &x, const Blob<T> &y)
{
	return x.data == y.data;
}

template <typename T>
bool operator!=(const Blob<T> &x, const Blob<T> &y)
{
	return !(x == y);
}

// comparison operation definitions
template <typename T>
bool operator<(const Blob<T> &lhs, const Blob<T> &rhs)
{
	if (lhs != rhs) // compare StrBlobs for equality
	{
		// for loop through vector pointed to by StrBlob's data
		for (auto lhs_pt = lhs.data->begin(), rhs_pt = rhs.data->begin(); (lhs_pt != lhs.data->end()) && (rhs_pt != rhs.data->end());)
		{
			if (*(lhs_pt++) != *(rhs_pt++)) // compare elements pointed to for equality
			{
				return *(--lhs_pt) < *(--rhs_pt); //return relation
			}
		}
	}
	else
		return false;
}

template <typename T>
bool operator>(const Blob<T> &lhs, const Blob<T> &rhs)
{
	return (lhs != rhs) && !(lhs < rhs);
}



// BlobPtr throws an exception on attempts to access a nonexistent element
// forward declarations needed for friends declarations in BlobPtr
template <typename T> bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T> 
class BlobPtr{
	friend bool operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);
public: 
	BlobPtr() : curr(0) { } 
	BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) { } 
	T &operator*() 
	{
		auto p = check(curr, "dereference past end"); 
		return (*p)[curr];  
		//(*p) is the vector to which this object points
	} 
	
	BlobPtr &operator--(int);
	BlobPtr &operator++(int);
	BlobPtr &operator--();
	BlobPtr &operator++();
	BlobPtr &operator+(int);
	BlobPtr &operator-(int);
	T &deref() const;
	BlobPtr &incr();       // prefix version
	BlobPtr &decr();       // prefix version

	T &operator[](std::size_t n)
	{
		auto p = check(n, "dereference past end");
		return (*p)[n];  // (*p) is the vector to which this object points
	}

	const T &operator[](std::size_t n) const
	{
		auto p = check(n, "dereference past end");
		return (*p)[n];  // (*p) is the vector to which this object points
	}

	const T &operator*() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr]; // (*p) is the vector to which this object points
	}

	T *operator->() const
	{ // delegate the real work to the dereference operator 
		return &this->operator*();
	}

	private: // check returns a shared_ptr to the vector if the check succeeds 
		std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const; 
		// store a weak_ptr, which means the underlying vector might be destroyed
		std::weak_ptr<std::vector<T>> wptr; 
		std::size_t curr;      // current position within the array 
};

template <typename T>
inline std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string &msg) const
{
	auto ret = wptr.lock();   // is the vector still around?
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");

	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret; // otherwise, return a shared_ptr to the vector
}

// prefix: return a reference to the incremented object
template <typename T>
inline BlobPtr<T> &BlobPtr<T>::incr()
{
	// if curr already points past the end of the container, can't increment it
	check(curr, "increment past end of StrBlobPtr");
	++curr;       // advance the current state
	return *this;
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::decr()
{
	// if curr is zero, decrementing it will yield an invalid subscript
	--curr;       // move the current state back one element}
	check(-1, "decrement past begin of StrBlobPtr");
	return *this;
}

template <typename T>
inline BlobPtr<T>& BlobPtr<T>::operator++()
{ // if curr already points past the end of the container, can't increment it 
	check(curr, "increment past end of StrBlobPtr");
	++curr; // advance the current state 
	return *this;
}

template <typename T>
inline BlobPtr<T>& BlobPtr<T>::operator--()
{ // if curr is zero, decrementing it will yield an invalid subscript
	--curr; // move the current state back one element 
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++(int x)
{ // no check needed here; the call to prefix increment will do the check 
	BlobPtr<T> ret = *this; // save the current value 
	++*this; // advance one element; prefix ++ checks the increment 
	return ret; // return the saved state 
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator--(int y)
{ // no check needed here; the call to prefix decrement will do the check 
	BlobPtr<T> ret = *this; // save the current value 
	--*this; // move backward one element; prefix checks the decrement 
	return ret; // return the saved state 
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator+(int n)
{
	auto p = check(curr, "pointer past end");
	curr += n;
	return *this;
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator-(int n)
{
	auto p = check(curr, "pointer within range");
	curr -= n;
	return *this;
}

template <typename T>
inline T &BlobPtr<T>::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];  // (*p) is the vector to which this object points
}

// begin and end members for StrBlob
template <typename T>
inline BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr<T>(*this);
}

template <typename T>
inline BlobPtr<T> Blob<T>::end()
{
	auto ret = BlobPtr<T>(*this, data->size());
	return ret;
}

// equality operators for StrBlobPtr
template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
	// if the underlying vector is the same 
	if (l == r)
		// then they're equal if they're both null or 
		// if they point to the same element
		return (!r || lhs.curr == rhs.curr);
	else
		return false; // if they point to difference vectors, they're not equal
}

template <typename T>
bool operator!=(const BlobPtr<T> &a, const BlobPtr<T> &b)
{
	return !(a == b);
}


int main()
{
	initializer_list<string>il{ "jk", "kk", "ww" };
	Blob<string> x{ il };
	Blob<string> y{ "mn", "kk" , "vcx" };
	Blob<string> z{}; //(x > y) << y.size();

	BlobPtr<string> a{ y };
	//Ptr_StrBlobPtr b{ a };
	//cout << b->deref();
	BlobPtr<string> b = a + 2;
	BlobPtr<string> c = a + 1;
	cout << (b - 2).deref();
	return 0;
}
