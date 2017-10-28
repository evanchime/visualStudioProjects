#include "Flower.h"

CFlower::CFlower(void)
	: _tp(0), _clr(0),
	_arg(0), _mx(false),
	_price(45.95)
{
}

CFlower::CFlower(int type, int color,
	int argn, bool mx,
	double price)
	: _tp(type),
	_clr(color),
	_arg(argn),
	_mx(mx),
	_price(price)
{
}

CFlower::~CFlower()
{
}

/*void CFlower::Show(const int qty)
{
	double totalPrice = UnitPrice * qty;

	Console::WriteLine(L"=======================");
	Console::WriteLine(L"==-=-=Flower Shop=-=-==");
	Console::WriteLine(L"-----------------------");
	Console::WriteLine(L"Flower Type:  {0}", Type);
	Console::WriteLine(L"Flower Color: {0}", Color);
	Console::WriteLine(L"Arrangement:  {0}", Arrangement);
	Console::WriteLine(L"Price:        {0:C}", UnitPrice);
	Console::WriteLine(L"Quantity:     {0}", qty);
	Console::WriteLine(L"Total Price:  {0:C}", totalPrice);
	Console::WriteLine(L"=======================");
}*/
