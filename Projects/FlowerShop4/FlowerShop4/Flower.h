#pragma once
using namespace System;

public enum FlowerType
{
	Roses = 1,
	Lilies,
	Daisies,
	Carnations,
	LivePlant,
	Mixed
};

public enum FlowerColor
{
	Red = 1,
	White,
	Yellow,
	Pink,
	Orange,
	Blue,
	Lavender,
	Various
};

public enum FlowerArrangement
{
	Bouquet = 1,
	Vase,
	Basket,
	Any
};

public ref class CFlower
{
private:
	double pc;

public:
	FlowerType Type;
	FlowerColor Color;
	FlowerArrangement Arrangement;

	property double UnitPrice
	{
		double get() { return pc; }
		void set(double value) { pc = value; }
	}

	CFlower();

protected:
	int items;

public:
	property int Count
	{
		int get() { return items; }
	}

	CFlower ^ Next;
};

