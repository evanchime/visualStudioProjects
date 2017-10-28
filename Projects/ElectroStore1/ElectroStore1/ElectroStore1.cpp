// ElectroStore1.cpp : main project file.

#include "stdafx.h"

#include "StoreItem.h"

using namespace System;
using namespace ElectronicsStore;

int main()
{
	String ^ strTitle = L"=-= Nearson Electonics =-=\n"
		L"******* Store Items ******";
	CStoreItem ^ item = gcnew CStoreItem;

	Console::WriteLine(strTitle);

	Console::WriteLine();
	return 0;
}
