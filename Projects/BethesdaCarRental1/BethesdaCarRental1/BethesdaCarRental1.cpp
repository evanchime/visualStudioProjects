// BethesdaCarRental1.cpp : main project file.

#include "stdafx.h"
#include "CarInventory.h"
#include "Car.h"
#include "Cars.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	CCarInventory ^ cars = gcnew CCarInventory;
	CCar ^ nice;

	nice = gcnew CCar;
	nice->TagNumber = L"527 495";
	nice->Make = L"Honda";
	nice->Model = L"Civic";
	nice->CarYear = 2006;
	nice->Mileage = 8631;
	nice->Category = L"Compact";
	nice->HasK7Player = false;
	nice->HasCDPlayer = true;
	nice->HasDVDPlayer = false;
	nice->Available = true;
	cars->Add(nice);

	nice = gcnew CCar;
	nice->TagNumber = L"M838400";
	nice->Make = L"Ford";
	nice->Model = L"Expedition";
	nice->CarYear = 2004;
	nice->Mileage = 48631;
	nice->Category = L"SUV";
	nice->HasK7Player = false;
	nice->HasCDPlayer = true;
	nice->HasDVDPlayer = true;
	nice->Available = false;
	cars->Add(nice);

	nice = gcnew CCar;
	nice->TagNumber = L"LRT825";
	nice->Make = L"Kia";
	nice->Model = L"Rio";
	nice->CarYear = 2007;
	nice->Mileage = 12504;
	nice->Category = L"Economy";
	nice->HasK7Player = false;
	nice->HasCDPlayer = false;
	nice->HasDVDPlayer = false;
	nice->Available = false;
	cars->Add(nice);

	nice = gcnew CCar;
	nice->TagNumber = L"917035";
	nice->Make = L"Toyota";
	nice->Model = L"Camry";
	nice->CarYear = 2006;
	nice->Mileage = 10664;
	nice->Category = L"Full Size";
	nice->HasK7Player = true;
	nice->HasCDPlayer = true;
	nice->HasDVDPlayer = false;
	nice->Available = true;
	cars->Add(nice);

	CCars ^ collection = gcnew CCars;
	collection->Locate(cars);

	Console::WriteLine(L"=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=");
	Console::WriteLine(L"Total: {0} Cars in company inventory",
		cars->Count);
	Console::WriteLine(L"=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=");
	Console::WriteLine(L"Inventory Summary");
	for each(CCar ^ car in collection)
	{
		Console::WriteLine(L"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
		Console::WriteLine(L"Car Information");
		Console::WriteLine(L"-------------------------------");
		Console::WriteLine(L"Tag #:      {0}", car->TagNumber);
		Console::WriteLine(L"Make:       {0}", car->Make);
		Console::WriteLine(L"Model:      {0}", car->Model);
		Console::WriteLine(L"Year:       {0}", car->CarYear);
		Console::WriteLine(L"Mileage:    {0}", car->Mileage);
		Console::WriteLine(L"Category:   {0}", car->Category);
		Console::WriteLine(L"K7 Plaher:  {0}", car->HasK7Player);
		Console::WriteLine(L"CD Player:  {0}", car->HasCDPlayer);
		Console::WriteLine(L"DVD Plaher: {0}", car->HasDVDPlayer);
		Console::WriteLine(L"Available:  {0}", car->Available);
	}
	Console::WriteLine(L"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	return 0;
}
