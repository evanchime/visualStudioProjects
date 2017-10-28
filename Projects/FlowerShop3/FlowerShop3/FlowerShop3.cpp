// FlowerShop3.cpp : main project file.

#include "stdafx.h"
#include "Flower.h"
#include "OrderProcessing.h"

using namespace System;

COrderProcessing ^ CreateFlowerOrder()
{
	double price;
	int arrangement;
	int type, color, qty, mx;
	COrderProcessing ^ order = gcnew COrderProcessing;

	Console::WriteLine(L"=======================");
	Console::WriteLine(L"==-=-=Flower Shop=-=-==");
	Console::WriteLine(L"-----------------------");

	Console::WriteLine(L"Enter the Type of Flower Order");
	Console::WriteLine(L"1. Roses");
	Console::WriteLine(L"2. Lilies");
	Console::WriteLine(L"3. Daisies");
	Console::WriteLine(L"4. Carnations");
	Console::WriteLine(L"5. Live Plant");
	Console::WriteLine(L"6. Mixed");
	Console::Write(L"Your Choice: ");
	type = int::Parse(Console::ReadLine());

	Console::WriteLine(L"Enter the Color");
	Console::WriteLine(L"1. Red");
	Console::WriteLine(L"2. White");
	Console::WriteLine(L"3. Yellow");
	Console::WriteLine(L"4. Pink");
	Console::WriteLine(L"5. Orange");
	Console::WriteLine(L"6. Blue");
	Console::WriteLine(L"7. Lavender");
	Console::WriteLine(L"8. Mixed");
	Console::Write(L"Your Choice: ");
	color = int::Parse(Console::ReadLine());

	Console::WriteLine(L"Enter the Type of Arrangement");
	Console::WriteLine(L"1. Bouquet");
	Console::WriteLine(L"2. Vase");
	Console::WriteLine(L"3. Basket");
	Console::WriteLine(L"4. Mixed");
	Console::Write(L"Your Choice: ");
	arrangement = int::Parse(Console::ReadLine());

	Console::Write(L"Is the Order Mixed (1=Yes/0=No)?");
	mx = int::Parse(Console::ReadLine());

	Console::Write(L"Enter the Unit Price: ");
	price = double::Parse(Console::ReadLine());

	Console::Write(L"Enter Quantity:       ");
	qty = int::Parse(Console::ReadLine());

	CFlower ^ flr = gcnew CFlower(type, color, arrangement,
		mx = 1 ? true : false, price);
	order->Flower = flr;
	order->Quantity = qty;

	return order;
}

int main()
{
	COrderProcessing ^ flower = CreateFlowerOrder();

	Console::WriteLine();
	return 0;
}
