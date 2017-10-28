// IceCream4.cpp : main project file.

#include "stdafx.h"
#include "IceCream.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	String ^ answer = L"n";
	CIceCream ^ ic = gcnew CIceCream();

	Console::Write(L"Do you want to re-order a previously "
		L"saved order(y/n)? ");
	answer = Console::ReadLine();

	if ((answer == L"y") || (answer == L"Y"))
		ic->OpenOrder();
	else
	{
		ic->ProcessAnOrder();
		Console::Write(L"Do you want us to remember this "
			L"order the next time you come to "
			L"get your ice scream (y/n)? ");
		answer = Console::ReadLine();
		if ((answer == L"y") || (answer == L"Y"))
			ic->SaveOrder();
		else
			Console::WriteLine(L"\nIt was nice serving you."
				L"\nCome Again!!!\n");
	}
    return 0;
}
