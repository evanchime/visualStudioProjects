#pragma once
using namespace System;

public ref class CCar
{
public:
	String ^ TagNumber;
	String ^ Make;
	String ^ Model;
	short    CarYear;
	int      Mileage;
	String ^ Category;
	bool     HasK7Player;
	bool     HasCDPlayer;
	bool     HasDVDPlayer;
	bool     Available;

	CCar ^ Next;

	CCar(void);
};

