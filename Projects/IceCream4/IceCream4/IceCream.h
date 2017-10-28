#pragma once
using namespace System;
using namespace System::IO;

public ref class CIceCream sealed
{
	// This is the base price of an ice scream
	// Optional values may be added to it
public:
	static const double BasePrice = 1.55;

	// These arrays are used to build the components 
	// of various ice creams
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
	CIceCream(void);
	void ChooseFlavor();
	void ChooseContainer();
	void ChooseIngredient();
	void SpecifyNumberOfScoops();
	void ProcessAnOrder();
	void DisplayReceipt();
	void SaveOrder();
	void OpenOrder();
};

