// GeorgetownCleaningServices6.cpp : main project file.

#include "stdafx.h"

#include "CleaningDeposit.h"
#include "CleaningRetrieval.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	String ^ answer = L"q";

	Console::WriteLine(L"Is this a new order or the customer is "
		L"retrieving items previously left for cleaning?");
	Console::WriteLine(L"0. Quit");
	Console::WriteLine(L"1. This is a new order");
	Console::WriteLine(L"2. The customer is retrieving an existing order");
	Console::Write(L"Your Choice: ");
	answer = Console::ReadLine();

	if (answer == L"1")
	{
		CCleaningDeposit ^ depotOrder = gcnew CCleaningDeposit;
		depotOrder->ProcessOrder();
	}
	else if (answer == L"2")
	{
		CCleaningRetrieval ^ previousOrder = gcnew CCleaningRetrieval;
		previousOrder->Open();
	}

	Console::WriteLine();
	return 0;
}