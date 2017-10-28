#include "Flower.h"
using namespace System;

private delegate void Display(const int x);

int main()
{
	CFlower ^ flower = gcnew CFlower;

	flower->Type = L"Daisies";
	flower->Color = L"Yellow";
	flower->Arrangement = L"Vase";
	flower->UnitPrice = 45.65;

	Display ^ disp = gcnew Display(flower, &CFlower::Show);
	disp->Invoke(3);

	Console::WriteLine();
	return 0;
	return 0;
}