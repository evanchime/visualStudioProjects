#pragma once

public enum class FlowerType
{
	Roses = 1,
	Lilies,
	Daisies,
	Carnations,
	LivePlant,
	Mixed
};

public enum class FlowerColor
{
	Red = 1,
	White,
	Yellow,
	Pink,
	Orange,
	Blue,
	Lavender,
	Mixed
};

public enum class FlowerArrangement
{
	Bouquet = 1,
	Vase,
	Basket,
	Mixed
};

public ref class CFlower
{
private:
	int _tp;
	int _clr;
	int _arg;
	bool _mx;
	double   _price;

public:
	property int Type
	{
		int get() { return _tp; }
		void set(int tp)
		{
			_tp = (tp <= 0 ? 0 : tp);
		}
	}

	property int Color
	{
		int get() { return _clr; }
		void set(int clr)
		{
			_clr = (clr <= 0 ? 0 : clr);
		}
	}

	property int Arrangement
	{
		int get() { return _arg; }
		void set(int arg)
		{
			_arg = (arg <= 0 ? 0 : arg);
		}
	}

	property bool Mixed
	{
		bool get() { return _mx; }
		void set(bool mx) { _mx = mx; }
	}

	property double UnitPrice
	{
		double get() { return _price; }
		void set(double price)
		{
			_price = (price <= 0.00 ? 0.00 : price);
		}
	}

public:
	CFlower(void);
	CFlower(int type, int color,
		int argn, bool mx, double price);
	~CFlower();
};

