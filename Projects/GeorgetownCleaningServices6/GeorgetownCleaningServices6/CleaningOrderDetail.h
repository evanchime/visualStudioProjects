#pragma once
using namespace System;

public ref class CCleaningOrderDetails sealed
{
public:
	// The date the cleaning items were deposited
	DateTime OrderDate;
	DateTime OrderTime;

	// Numbers to represent cleaning items
	int NumberOfShirts;
	int NumberOfPants;
	int NumberOtherItems;

	// Price of items
	double PriceOneShirt;
	double PriceAPairOfPants;
	double PriceOtherItems;
	double TaxRate;

	// Each of these sub totals will be used for cleaning items
	double SubTotalShirts;
	double SubTotalPants;
	double SubTotalOtherItems;

	// Values used to process an order
	double TotalOrder;
	double TaxAmount;
	double SalesTotal;

	CCleaningOrderDetails(void);
};

