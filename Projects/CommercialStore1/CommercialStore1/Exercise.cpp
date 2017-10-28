#include <iostream>
using namespace std;

typedef double ItemType;

struct CItem
{
	ItemType Item;
	CItem *Next;
};

CItem * Head = NULL;
int Size;

int Count()
{
	return Size;
}

int Add(CItem * NewItem)
{
	CItem * Sample = new CItem;

	Sample = NewItem;
	Sample->Next = Head;
	Head = Sample;

	return Size++;
}
CItem * Retrieve(int Position)
{
	CItem * Current = Head;

	for (int i = Count() - 1; i > Position && Current != NULL; i--)
	{
		Current = Current->Next;
	}

	return Current;
}


template <class T>
void ShowItem(T item)
{
	cout << "Item: " << item << endl;
}

int main()
{
	CItem * Part;

	Part = new CItem;
	Part->Item = 97.43;
	Add(Part);

	Part = new CItem;
	Part->Item = 274.87;
	Add(Part);

	Part = new CItem;
	Part->Item = 8.7873;
	Add(Part);

	Part = new CItem;
	Part->Item = 2764.4;
	Add(Part);

	Part = new CItem;
	Part->Item = 92.4662;
	Add(Part);

	Part = new CItem;
	Part->Item = 66800.85;
	Add(Part);

	cout << "-=- List of Items -=-" << endl;

	for (int i = 0; i < Count(); i++)
	{
		CItem * One = Retrieve(i);

		ShowItem(One->Item);
	}

	cout << "\nNumber of Items: " << Count() << "\n\n";

	return 0;
}