// FlowerShop2.cpp : main project file.

#include "stdafx.h"

#include "Flower.h"
#include "OrderProcessing.h"
using namespace System;

COrderProcessing ^ CreateFlowerOrder()
{
	COrderProcessing ^ order = gcnew COrderProcessing;
	int type, color, qty;
	__wchar_t arrangement;
	double price;

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
	Console::WriteLine(L"U. Bouquet");
	Console::WriteLine(L"V. Vase");
	Console::WriteLine(L"B. Basket");
	Console::WriteLine(L"M. Mixed");
	Console::Write(L"Your Choice: ");
	arrangement = __wchar_t::Parse(Console::ReadLine());

	Console::Write(L"Enter the Unit Price: ");
	price = double::Parse(Console::ReadLine());

	Console::Write(L"Enter Quantity:       ");
	qty = int::Parse(Console::ReadLine());

	CFlower ^ flr = gcnew CFlower(type, color, arrangement, price);
	order->Flower = flr;
	order->Quantity = qty;

	return order;
}

void ShowFlowerOrder(COrderProcessing ^ order)
{
	Console::WriteLine(L"=======================");
	Console::WriteLine(L"==-=-=Flower Shop=-=-==");
	Console::WriteLine(L"-----------------------");
	Console::WriteLine(L"Flower Type:  {0}", order->Flower->Type);
	Console::WriteLine(L"Flower Color: {0}", order->Flower->Color);
	Console::WriteLine(L"Arrangement:  {0}", order->Flower->Arrangement);
	Console::WriteLine(L"Price:        {0:C}", order->Flower->UnitPrice);
	Console::WriteLine(L"Quantity:     {0}", order->Quantity);
	Console::WriteLine(L"Total Price:  {0:C}", order->GetTotalPrice());
	Console::WriteLine(L"=======================");
}

int main()
{
	COrderProcessing ^ flower = CreateFlowerOrder();
	ShowFlowerOrder(flower);

	Console::WriteLine();
	return 0;
}
