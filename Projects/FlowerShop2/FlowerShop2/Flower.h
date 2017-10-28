#pragma once
#pragma once
using namespace System;

public ref class CFlower
{
private:
	int _tp;
	int _clr;
	__wchar_t _arg;
	double   _price;

public:
	property int Type
	{
		int get() { return _tp; }
		void set(int tp) { _tp = tp; }
	}

	property int Color
	{
		int get() { return _clr; }
		void set(int clr) { _clr = clr; }
	}

	property __wchar_t Arrangement
	{
		__wchar_t get() { return _arg; }
		void set(__wchar_t arg) { _arg = arg; }
	}

	property double UnitPrice
	{
		double get() { return _price; }
		void set(double price) { _price = price; }
	}

public:
	CFlower(void);
	CFlower(int type);
	CFlower(int type, int color,
		__wchar_t argn, double price);
	~CFlower();
};

