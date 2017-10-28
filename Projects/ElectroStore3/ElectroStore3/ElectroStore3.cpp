// ElectroStore3.cpp : main project file.

#include "stdafx.h"

#include "StoreItem.h"

using namespace System;
using namespace ElectronicsStore;

static void DescribeStoreItem(CStoreItem ^ %);

int main()
{
	String ^ strTitle = L"=-= Nearson Electonics =-=\n"
		L"******* Store Items ******";

	CStoreItem ^ saleItem = gcnew CStoreItem();

	Console::WriteLine(L"==/==A store item with default values==/==");
	DescribeStoreItem(saleItem);
	Console::WriteLine();

	saleItem = gcnew CStoreItem(606302, L"Altec Lansing",
		L"AHP-712I", 85.95);
	saleItem->SetCategory(L'H');
	saleItem->SetDiscountRate(25);
	Console::WriteLine(L"==/==A store item known for its make, "
		L"model, and unit price==/==");
	DescribeStoreItem(saleItem);
	Console::WriteLine();

	Console::WriteLine(L"==/==A store item with default values==/==");
	saleItem = gcnew CStoreItem(162864, L"External Sound Card", 85.95);
	DescribeStoreItem(saleItem);
	Console::WriteLine();

	Console::WriteLine(L"==/==A store item completely defined==/==");
	saleItem = gcnew CStoreItem(513497, L'T',
		L"Uniden",
		L"8x8 Packet8 Broadband Internet Phone System",
		10, 145.95);
	DescribeStoreItem(saleItem);
	Console::WriteLine();

	Console::WriteLine(L"==/==A store item with each "
		L"characteristic defined==/==");
	saleItem = gcnew CStoreItem();
	saleItem->SetItemNumber(913846);
	saleItem->SetCategory(L'S');
	saleItem->SetMake(L"APC");
	saleItem->SetModel(L"Personal SurgeArrest");
	saleItem->SetDiscountRate(25.00);
	saleItem->SetUnitPrice(14.95);
	DescribeStoreItem(saleItem);
	Console::WriteLine();
	Console::ReadLine();


	return 0;
}

void DescribeStoreItem(CStoreItem ^ %item)
{
	Console::WriteLine(L"Store Item Description");
	Console::WriteLine(L"Item Number:   {0}", item->GetItemNumber());
	Console::WriteLine(L"Category:      {0}", item->GetCategory());
	Console::WriteLine(L"Make           {0}", item->GetMake());
	Console::WriteLine(L"Model:         {0}", item->GetModel());
	Console::WriteLine(L"Name:          {0}", item->GetName());
	Console::WriteLine(L"Discount Rate: {0:P}", item->GetDiscountRate());
	Console::WriteLine(L"Unit Price:    {0:C}", item->GetUnitPrice());
}