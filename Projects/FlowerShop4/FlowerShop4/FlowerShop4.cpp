// FlowerShop4.cpp : main project file.

#include "stdafx.h"
#include "OrderProcessing.h"
#include "FlowerInventory.h"

using namespace System;

CFlowerInventory ^ CreateFlowers()
{
	CFlowerInventory ^ NewFlowers = gcnew CFlowerInventory();
	CFlower ^ nice;

	nice = gcnew CFlower;
	nice->Type = Lilies;
	nice->Color = White;
	nice->Arrangement = Bouquet;
	nice->UnitPrice = 39.95;
	NewFlowers->Add(nice);

	nice = gcnew CFlower;
	nice->Type = Daisies;
	nice->Color = Various;
	nice->Arrangement = Bouquet;
	nice->UnitPrice = 40.50;
	NewFlowers->Add(nice);

	nice = gcnew CFlower;
	nice->Type = Carnations;
	nice->Color = Lavender;
	nice->Arrangement = Any;
	nice->UnitPrice = 34.85;
	NewFlowers->Add(nice);

	nice = gcnew CFlower;
	nice->Type = Roses;
	nice->Color = Pink;
	nice->Arrangement = Bouquet;
	nice->UnitPrice = 29.95;
	NewFlowers->Add(nice);

	nice = gcnew CFlower;
	nice->Type = Daisies;
	nice->Color = Yellow;
	nice->Arrangement = Vase;
	nice->UnitPrice = 29.95;
	NewFlowers->Add(nice);

	return NewFlowers;
}

void ShowInventory(CFlowerInventory ^ FlowersList)
{
	Console::WriteLine(L"//=//=//=//=//=//=//=//=//=//=//=//=//=//=//");
	Console::WriteLine(L"Total: {0} flower items in current inventory",
		FlowersList->Count);
	Console::WriteLine(L"--------------------------------------------");
	Console::WriteLine(L"Inventory Summary");
	for (int i = 0; i < FlowersList->Count; i++)
	{
		Console::WriteLine(L"------------------------");
		Console::WriteLine(L"Flower Information");
		Console::Write(L"Type:        ");
		switch (FlowersList->Get(i)->Type)
		{
		case 1:
			Console::WriteLine(L"Roses");
			break;
		case 2:
			Console::WriteLine(L"Lilies");
			break;
		case 3:
			Console::WriteLine(L"Daisies");
			break;
		case 4:
			Console::WriteLine(L"Carnations");
			break;
		case 5:
			Console::WriteLine(L"Live Plant");
			break;
		default:
			Console::WriteLine(L"Mixed");
		}

		Console::Write(L"Color:       ");
		switch (FlowersList->Get(i)->Color)
		{
		case 1:
			Console::WriteLine(L"Red");
			break;
		case 2:
			Console::WriteLine(L"White");
			break;
		case 3:
			Console::WriteLine(L"Yellow");
			break;
		case 4:
			Console::WriteLine(L"Pink");
			break;
		case 5:
			Console::WriteLine(L"Orange");
			break;
		case 6:
			Console::WriteLine(L"Blue");
			break;
		case 7:
			Console::WriteLine(L"Lavender");
			break;
		default:
			Console::WriteLine(L"Various");
		}

		Console::Write(L"Arrangement: ");
		switch (FlowersList->Get(i)->Arrangement)
		{
		case 1:
			Console::WriteLine(L"Bouquet");
			break;
		case 2:
			Console::WriteLine(L"Vase");
			break;
		case 3:
			Console::WriteLine(L"Basket");
			break;
		default:
			Console::WriteLine(L"Any");
		}

		Console::WriteLine(L"Unit Price:  {0:F}",
			FlowersList->Get(i)->UnitPrice);
	}
	Console::WriteLine(L"//=//=//=//=//=//=//=//=//=//=//=//=//=//=//");
}
int main()
{
	CFlowerInventory ^ flowers = CreateFlowers();

	ShowInventory(flowers);

	flowers->Delete();
	flowers->Delete();

	Console::Write(L"Press Enter to see the new inventory...");
	Console::ReadLine();

	ShowInventory(flowers);

	Console::WriteLine();
	return 0;
}