#include "stdafx.h"
#include "OrderProcessing.h"

COrderProcessing::COrderProcessing(void)
{
	FlowerOrder = gcnew CFlower;
}

void COrderProcessing::GetFlowerType()
{
	int choice = 0;

	do {
		try {
			Console::WriteLine(L"Enter the Type of Flower Order");
			Console::WriteLine(L"1. Roses");
			Console::WriteLine(L"2. Lilies");
			Console::WriteLine(L"3. Daisies");
			Console::WriteLine(L"4. Carnations");
			Console::WriteLine(L"5. Live Plant");
			Console::WriteLine(L"6. Mixed");
			Console::Write("Your Choice: ");
			choice = int::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"You failed to enter an "
				L"appropriate number!");
		}

		if ((choice < 1) || (choice > 6))
			Console::WriteLine(L"Invalid Value: Please enter "
				L"a value between 1 and 6");
	} while ((choice < 1) || (choice > 6));

	switch (choice)
	{
	case 1:
		FlowerOrder->Type = Roses;
		break;
	case 2:
		FlowerOrder->Type = Lilies;
		break;
	case 3:
		FlowerOrder->Type = Daisies;
		break;
	case 4:
		FlowerOrder->Type = Carnations;
		break;
	case 5:
		FlowerOrder->Type = LivePlant;
		break;
	default:
		FlowerOrder->Type = Mixed;
		break;
	}
}

void COrderProcessing::GetFlowerColor()
{
	int choice = 0;

	do {
		try {
			Console::WriteLine(L"Enter the Color");
			Console::WriteLine(L"1. Red");
			Console::WriteLine(L"2. White");
			Console::WriteLine(L"3. Yellow");
			Console::WriteLine(L"4. Pink");
			Console::WriteLine(L"5. Orange");
			Console::WriteLine(L"6. Blue");
			Console::WriteLine(L"7. Lavender");
			Console::WriteLine(L"8. Mixed");
			Console::Write("Your Choice: ");
			choice = int::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"You didn't enter an "
				L"appropriate number!");
		}

		if ((choice < 1) || (choice > 8))
			Console::WriteLine(L"Invalid Value: Please "
				L"enter a value between 1 and 8");
	} while ((choice < 1) || (choice > 8));

	switch (choice)
	{
	case 1:
		FlowerOrder->Color = Red;
		break;
	case 2:
		FlowerOrder->Color = White;
		break;
	case 3:
		FlowerOrder->Color = Yellow;
		break;
	case 4:
		FlowerOrder->Color = Pink;
		break;
	case 5:
		FlowerOrder->Color = Orange;
		break;
	case 6:
		FlowerOrder->Color = Blue;
		break;
	case 7:
		FlowerOrder->Color = Lavender;
		break;
	default:
		FlowerOrder->Color = Various;
		break;
	}
}

void COrderProcessing::GetFlowerArrangement()
{
	int choice = 0;

	do {
		try {
			Console::WriteLine(L"Enter the Type of Arrangement");
			Console::WriteLine(L"1. Bouquet");
			Console::WriteLine(L"2. Vase");
			Console::WriteLine(L"3. Basket");
			Console::WriteLine(L"4. Mixed");
			Console::Write("Your Choice: ");
			choice = int::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"You didn't provide an "
				L"acceptable number!");
		}

		if ((choice < 1) || (choice > 4))
			Console::WriteLine(L"Invalid Value: Please enter "
				L"a value between 1 and 4");
	} while ((choice < 1) || (choice > 4));

	switch (choice)
	{
	case 1:
		FlowerOrder->Arrangement = Bouquet;
		break;
	case 2:
		FlowerOrder->Arrangement = Vase;
		break;
	case 3:
		FlowerOrder->Arrangement = Basket;
		break;
	default:
		FlowerOrder->Arrangement = Any;
		break;
	}
}

void COrderProcessing::ProcessOrder()
{
	GetFlowerType();
	GetFlowerColor();
	GetFlowerArrangement();

	try {
		Console::Write("Enter the Unit Price: ");
		FlowerOrder->UnitPrice =
			Math::Abs(double::Parse(Console::ReadLine()));
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You didn't specify a valid price!");
	}

	try {
		Console::Write("Enter Quantity:       ");
		Quantity = Math::Abs(int::Parse(Console::ReadLine()));
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"The quantity you entered "
			L"is not acceptable!");
	}
}

void COrderProcessing::ShowOrder()
{
	Console::WriteLine(L"=======================");
	Console::WriteLine(L"==-=-=Flower Shop=-=-==");
	Console::WriteLine(L"-----------------------");
	Console::Write(L"Flower Type:  ");
	switch (FlowerOrder->Type)
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

	Console::Write(L"Flower Color: ");
	switch (FlowerOrder->Color)
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

	Console::Write(L"Arrangement:  ");
	switch (FlowerOrder->Arrangement)
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

	Console::Write(L"Price:        ");
	Console::WriteLine(FlowerOrder->UnitPrice);
	Console::Write(L"Quantity:     ");
	Console::WriteLine(Quantity);
	Console::Write(L"Total Price:  ");
	Console::WriteLine(TotalPrice.ToString(L"C"));
	Console::WriteLine(L"=======================");
}
