// IceCream3.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::IO;

// This class is used to create and manage an ice scream
// and to process an order
public ref class CIceCream sealed
{
public:
	// This is the base price of an ice scream
	// Optional values may be added to it
	static const double BasePrice = 1.55;

	// These arrays are used to build the components 
	// of various ice screams
private:
	array<String ^> ^ Flavor;
	array<String ^> ^ Container;
	array<String ^> ^ Ingredient;

	// Additional factor used to process an ice scream order
	int Scoops;
	double TotalPrice;

	// Variables that will hold the user's choice
	// These are declared "globally" so they can be 
	// shared among methods
	int ChoiceFlavor;
	int ChoiceContainer;
	int ChoiceIngredient;

	// This default constructor is the best place for 
	// us to initialize the array
public:
	CIceCream()
	{
		Flavor = gcnew array<String ^>(10);
		Flavor[0] = L"Vanilla";
		Flavor[1] = L"Cream of Cocoa";
		Flavor[2] = L"Chocolate Chip";
		Flavor[3] = L"Organic Strawberry";
		Flavor[4] = L"Butter Pecan";
		Flavor[5] = L"Cherry Coke";
		Flavor[6] = L"Chocolate Brownies";
		Flavor[7] = L"Caramel Au Lait";
		Flavor[8] = L"Chunky Butter";
		Flavor[9] = L"Chocolate Cookie";

		Ingredient = gcnew array<String^>(4);
		Ingredient[0] = L"No Ingredient";
		Ingredient[1] = L"Peanuts";
		Ingredient[2] = L"M & M";
		Ingredient[3] = L"Cookies";

		Container = gcnew array<String^>(3);
		Container[0] = L"Cone";
		Container[1] = L"Cup";
		Container[2] = L"Bowl";
	}

	// This method requests a flavor from the user and
	// returns the choice
	void ChooseFlavor()
	{
		// Make sure the user selects a valid number 
		//that represents a flavor...
		do {
			// In case the user types a symbol that 
			// is not a number
			try {
				Console::WriteLine(L"What type of flavor do you want?");
				for (int i = 0; i < Flavor->Length; i++)
					Console::WriteLine(L"{0} - {1}", i + 1, Flavor[i]);
				Console::Write(L"Your Choice? ");
				ChoiceFlavor = int::Parse(Console::ReadLine());
			}
			catch (FormatException ^)	// display an appropriate message
			{
				Console::WriteLine(L"You must enter a valid number "
					L"and no other character!");
			}

			// If the user typed an invalid number out of the 
			// allowed range
			// let him or her know and provide another chance
			if (ChoiceFlavor < 1 || ChoiceFlavor > Flavor->Length)
				Console::WriteLine(L"Invalid Choice - Try Again!\n");
		} while (ChoiceFlavor < 1 || ChoiceFlavor > Flavor->Length);
	}

	// This method allows the user to select a container
	void ChooseContainer()
	{
		// Make sure the user selects a valid number that 
		// represents a container
		do {
			// If the user types a symbol that is not a number
			try
			{
				Console::WriteLine(L"What type of container do you want?");
				for (int i = 0; i < Container->Length; i++)
					Console::WriteLine(L"{0} - {1}", i + 1, Container[i]);
				Console::Write(L"Your Choice? ");
				ChoiceContainer = int::Parse(Console::ReadLine());
			}
			catch (FormatException ^)	// display an appropriate message
			{
				Console::WriteLine(L"You must enter a valid "
					L"number and no other character!");
			}

			// If the user typed an invalid number out of the 
			// allowed range
			// let him or her know and provide another chance
			if ((ChoiceContainer < 1) ||
				(ChoiceContainer > Container->Length))
				Console::WriteLine(L"Invalid Choice - Try Again!");
		} while ((ChoiceContainer < 1) ||
			(ChoiceContainer > Container->Length));
	}

	void ChooseIngredient()
	{
		do {
			try {
				Console::WriteLine(L"Do you want an ingredient or not");
				for (int i = 0; i < Ingredient->Length; i++)
					Console::WriteLine(L"{0} - {1}",
						i + 1, Ingredient[i]);
				Console::Write(L"Your Choice? ");
				ChoiceIngredient = int::Parse(Console::ReadLine());
			}
			catch (FormatException ^)
			{
				Console::WriteLine(L"You must enter a valid "
					L"number and no other character!");
			}

			if ((ChoiceIngredient < 1) ||
				(ChoiceIngredient > Ingredient->Length))
				Console::WriteLine(L"Invalid Choice - Try Again!");
		} while ((ChoiceIngredient < 1) ||
			(ChoiceIngredient > Ingredient->Length));
	}

	void SpecifyNumberOfScoops()
	{
		do {
			try {
				Console::Write(L"How many scoops(1, 2, or 3)? ");
				Scoops = int::Parse(Console::ReadLine());
			}
			catch (FormatException ^)
			{
				Console::WriteLine(L"You must enter a valid number "
					L"and no other character!");
			}

			if (Scoops < 1 || Scoops > 3)
				Console::WriteLine(L"Invalid Choice - Try Again!");
		} while (Scoops < 1 || Scoops > 3);
	}

	// This method is used to process a customer order
	// It uses the values of the above methods
	void ProcessAnOrder()
	{
		double PriceIngredient, PriceScoop;

		// Let the user know that this is a vending machine
		Console::WriteLine(L"=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=");
		Console::WriteLine(L"Ice Scream Vending Machine");
		Console::WriteLine(L"-----------------------------------");

		// Let the user select the components of the ice scream
		ChooseFlavor();
		Console::WriteLine(L"-----------------------------------");
		ChooseContainer();
		Console::WriteLine(L"-----------------------------------");
		ChooseIngredient();
		Console::WriteLine(L"-----------------------------------");
		SpecifyNumberOfScoops();
		Console::WriteLine(L"-----------------------------------");

		// If the user selects an ingredient instead of "No Ingredient",
		// add $0.50 to the order
		if ((ChoiceIngredient == 2) ||
			(ChoiceIngredient == 3) ||
			(ChoiceIngredient == 4))
			PriceIngredient = 0.50;
		else
			PriceIngredient = 0.00;

		// Instead of multiplying a number scoops to a value,
		// We will use an incremental value depending on 
		// the number of scoops
		if (Scoops == 1)
			PriceScoop = 0.65;
		else if (Scoops == 2)
			PriceScoop = 1.05;
		else
			PriceScoop = 1.55;

		// Calculate the total price of the ice scream
		TotalPrice = BasePrice + PriceScoop + PriceIngredient;

		// Create the ice scream...

		// And display a receipt to the user
		DisplayReceipt();
	}

	// This method is used to display a receipt to the user
	void DisplayReceipt()
	{
		Console::WriteLine(L"\n=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=");
		Console::WriteLine(L"Ice Scream Order");
		Console::WriteLine(L"-----------------------------------");
		Console::WriteLine(L"Flavor:      {0}",
			Flavor[ChoiceFlavor - 1]);
		Console::WriteLine(L"Container:   {0}",
			Container[ChoiceContainer - 1]);
		Console::WriteLine(L"Ingredient:  {0}",
			Ingredient[ChoiceIngredient - 1]);
		Console::WriteLine(L"Scoops:      {0}", Scoops);
		Console::WriteLine(L"Total Price: {0:C}", TotalPrice);
		Console::WriteLine(L"=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
	}

	void SaveOrder()
	{
		String ^ strNameOfFile;

		Console::Write(L"Please enter your initials or the name "
			L"we will use to remember your order: ");
		strNameOfFile = Console::ReadLine();
		strNameOfFile = strNameOfFile + L".icr";

		// Find out if the user entered a name of a file 
		// that is already in the machine
		if (File::Exists(strNameOfFile))
		{
			__wchar_t  answer;

			FileStream ^ stmIceCream =
				gcnew FileStream(strNameOfFile, FileMode::Create);
			BinaryWriter ^ bnwIceCream =
				gcnew BinaryWriter(stmIceCream);

			// If so, find out if the user wants to 
			// replace the old file
			Console::WriteLine(L"The file you entered exists already.");
			Console::Write(L"Do you want to replace it(y/n)?");
			answer = __wchar_t::Parse(Console::ReadLine());

			// If the customer wants to replace it...
			if ((answer == L'y') || (answer == L'Y'))
			{
				// ... do so
				Console::WriteLine(L"The former order with the same "
					L"name will be replaced");

				Console::WriteLine(L"\n=-= Ice Scream Vending Machine =-=");
				Console::WriteLine(L" Saving Order: {0}", strNameOfFile);

				bnwIceCream->Write(Flavor[ChoiceFlavor - 1]);
				bnwIceCream->Write(Container[ChoiceContainer - 1]);
				bnwIceCream->Write(Ingredient[ChoiceIngredient - 1]);
				bnwIceCream->Write(Scoops);
				bnwIceCream->Write(TotalPrice);
			}
			// If the customer wants to save the new order with 
			// a different name
			else if ((answer == L'n') || (answer == 'N'))
			{
				// Ask the user to enter a name to remember the order
				Console::Write(L"Please enter a name we will use "
					L"to remember this order: ");
				strNameOfFile = Console::ReadLine();
				strNameOfFile = strNameOfFile + L".icr";

				stmIceCream = gcnew FileStream(strNameOfFile, FileMode::Create);
				bnwIceCream = gcnew BinaryWriter(stmIceCream);

				Console::WriteLine(L"\n=-= Ice Scream Vending Machine =-=");
				Console::WriteLine(L" Saving Order: {0}", strNameOfFile);

				bnwIceCream->Write(Flavor[ChoiceFlavor - 1]);
				bnwIceCream->Write(Container[ChoiceContainer - 1]);
				bnwIceCream->Write(Ingredient[ChoiceIngredient - 1]);
				bnwIceCream->Write(Scoops);
				bnwIceCream->Write(TotalPrice);
			}
			else
				Console::WriteLine(L"Invalid Answer - We will close");

			bnwIceCream->Close();
			stmIceCream->Close();
		}
		else
		{
			FileStream ^ stmIceCream =
				gcnew FileStream(strNameOfFile, FileMode::Create);
			BinaryWriter ^ bnwIceCream =
				gcnew BinaryWriter(stmIceCream);

			Console::WriteLine(L"\n=-= Ice Scream Vending Machine =-=");
			Console::WriteLine(L" Saving Order: {0}", strNameOfFile);

			bnwIceCream->Write(Flavor[ChoiceFlavor - 1]);
			bnwIceCream->Write(Container[ChoiceContainer - 1]);
			bnwIceCream->Write(Ingredient[ChoiceIngredient - 1]);
			bnwIceCream->Write(Scoops);
			bnwIceCream->Write(TotalPrice);

			bnwIceCream->Close();
			stmIceCream->Close();
		}
	}
	
	void OpenOrder()
	{

		String ^ strNameOfFile;

		String ^ SelectedFlavor;
		String ^ SelectedContainer;
		String ^ SelectedIngredient;

		// Ask the user to enter a name of a previously saved order
		Console::Write(L"Please enter the name you previously "
			L"gave to remember your order: ");
		strNameOfFile = Console::ReadLine();
		strNameOfFile = strNameOfFile + L".icr";

		FileStream ^ stmIceCream =
			gcnew FileStream(strNameOfFile, FileMode::Open);
		BinaryReader ^ bnrIceCream =
			gcnew BinaryReader(stmIceCream);

		// Find out if this order was previously saved in the machine
		if (File::Exists(strNameOfFile))
		{
			// If so, open it
			SelectedFlavor = bnrIceCream->ReadString();
			SelectedContainer = bnrIceCream->ReadString();
			SelectedIngredient = bnrIceCream->ReadString();
			Scoops = bnrIceCream->ReadInt32();
			TotalPrice = bnrIceCream->ReadDouble();

			// And display it to the user
			Console::WriteLine(L"\n=-= Ice Scream Vending Machine =-=");
			Console::WriteLine(L" Previous Order: {0}", strNameOfFile);
			Console::WriteLine(L"Flavor:      {0}", SelectedFlavor);
			Console::WriteLine(L"Container:   {0}", SelectedContainer);
			Console::WriteLine(L"Ingredient:  {0}", SelectedIngredient);
			Console::WriteLine(L"Scoops:      {0}", Scoops);
			Console::WriteLine(L"Total Price: {0:C}\n", TotalPrice);

			bnrIceCream->Close();
			stmIceCream->Close();
		}
		else
			Console::WriteLine(L"The name you entered is not "
				L"registered in our previous orders");
	}
};

int main(array<System::String ^> ^args)
{
	String ^ answer = L"n";
	CIceCream ^ ic = gcnew CIceCream();

	Console::Write(L"Do you want to re-order a previously "
		L"saved order(y/n)? ");
	answer = Console::ReadLine();

	if ((answer == L"y") || (answer == L"Y"))
		ic->OpenOrder();
	else
	{
		ic->ProcessAnOrder();

		Console::Write(L"Do you want us to remember this "
			L"order the next time you come to "
			L"get your ice scream (y/n)? ");
		answer = Console::ReadLine();

		if ((answer == L"y") || (answer == L"Y"))
			ic->SaveOrder();
		else
			Console::WriteLine(L"\nIt was nice serving you."
				L"\nCome Again!!!\n");
	}

	Console::WriteLine();
	return 0;
}
