#pragma once
template <class T>
public value struct CItem
{
	T Item;
	CItem ^ Next;
};

public ref class CListOfItems
{
private:
	int Size;

public:
	// List Initialization
	CListOfItems(void);
	CItem<double> ^ Head;

	// List Finalization
	~CListOfItems();
	!CListOfItems();

	// Operations on list
	int Count();
	int Add(CItem<double> ^ item);
	CItem<double> ^ Retrieve(int Position);
};