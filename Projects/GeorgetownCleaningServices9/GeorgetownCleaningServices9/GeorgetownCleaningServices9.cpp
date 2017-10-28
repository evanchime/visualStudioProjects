// GeorgetownCleaningServices9.cpp : main project file.

#include "stdafx.h"
#include "CleaningOrderManagement.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	Char answer = 'q';
	CleaningOrderManagement ^ depotOrder = gcnew CleaningOrderManagement();

	do
	{
		Console::WriteLine(L"================================================");
		Console::WriteLine(L"Georgetown Cleaning Services");
		Console::WriteLine(L"================================================");
		try
		{
			Console::WriteLine(L"What do you want to do?");
			Console::WriteLine(L"1. Process a new cleaning order");
			Console::WriteLine(L"2. Retrieve an existing order");
			Console::WriteLine(L"0. Quit");
			Console::Write(L"Your Choice: ");
			answer = Char::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"Invalid Answer");
		}

		switch (answer)
		{
		case '1':
			depotOrder->ProcessOrder();
			break;

		case '2':
			depotOrder->OpenCleaningOrder();
			break;

		default:
			break;
		}
	} while ((answer == '1') ||
		(answer == '2'));
	Console::WriteLine();
	return 0;
}
