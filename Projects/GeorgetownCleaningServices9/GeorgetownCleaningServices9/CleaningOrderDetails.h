#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;

[Serializable]
public ref class CCleaningOrderDetails
{
public:
	// Receipt identification
	int ReceiptNumber;
	String ^ CustomerName;
	String ^ CustomerPhoneNumber;
	// The date the cleaning items were deposited
	DateTime ^ OrderDate;
	DateTime ^ OrderTime;
	// Numbers to represent cleaning items
	unsigned int NumberOfShirts;
	unsigned int NumberOfPants;
	unsigned int NumberOtherItems;

	// Price of items
	double PriceOneShirt = 0.95;
	double PriceAPairOfPants = 2.95;
	double PriceOtherItems = 4.55;
	double TaxRate = 0.0575;  // 5.75%

							  // Each of these sub totals will be used for cleaning items
	double SubTotalShirts;
	double SubTotalPants;
	double SubTotalOtherItems;

	// Values used to process an order
	double TotalOrder;
	double TaxAmount;
	double SalesTotal;
	double AmountTended;
	double Difference;

	CCleaningOrderDetails();
};

