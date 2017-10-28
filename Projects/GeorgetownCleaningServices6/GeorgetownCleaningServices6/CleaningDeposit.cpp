#include "stdafx.h"
#include "CleaningDeposit.h"


using namespace System;
using namespace System::IO;

CCleaningDeposit::CCleaningDeposit(void)
{
	this->custInfo = gcnew CCustomer;
	this->depot = gcnew CCleaningOrderDetails;
}


CCustomer ^ CCleaningDeposit::IdentifyCustomer()
{
	String ^ strCustomerName;
	String ^ strTelephoneNumber, ^ strPhoneFormatted;

	Console::Write(L"Enter Customer Phone Number: ");
	strTelephoneNumber = Console::ReadLine();

	// Remove the spaces, parentheses, if any, and dashes, if any
	strTelephoneNumber = strTelephoneNumber->Replace(L" ", "");
	strTelephoneNumber = strTelephoneNumber->Replace(L"(L", "");
	strTelephoneNumber = strTelephoneNumber->Replace(L")", "");
	strTelephoneNumber = strTelephoneNumber->Replace(L"-", "");

	if (strTelephoneNumber->Length != 10)
	{
		Console::WriteLine(L"Invalid telphone number: {0} "
			L"characters instead of 10 digits",
			strTelephoneNumber->Length);
		return nullptr;
	}

	strPhoneFormatted = String::Concat(L"(L",
		strTelephoneNumber->Substring(0, 3),
		L") ",
		strTelephoneNumber->Substring(3, 3),
		L"-",
		strTelephoneNumber->Substring(6, 4));

	String ^ strFilename = strTelephoneNumber + L".gcs";
	String ^ strPath = L"C:\\Georgetown Cleaning Services\\Customers\\"
		L"\\" + strFilename;

	if (File::Exists(strPath))
	{
		FileStream ^ stmCustomer =
			File::Open(strPath, FileMode::Open, FileAccess::Read);
		BinaryReader ^ bnrCustomer = gcnew BinaryReader(stmCustomer);

		custInfo->Name = bnrCustomer->ReadString();
		custInfo->PhoneNumber = bnrCustomer->ReadString();

		Console::WriteLine(L"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
		Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
		Console::WriteLine(L"------------------------------------");
		Console::WriteLine(L"Customer Name: {0}", custInfo->Name);
		Console::WriteLine(L"Phone Number:  {0}", custInfo->PhoneNumber);
		Console::WriteLine(L"------------------------------------\n");
	}
	else // If the customer information was not found in a file
	{
		Console::WriteLine(L"It looks like this is the first time you "
			L"are trusting  us with your cleaning order");
		Directory::CreateDirectory(L"C:\\Georgetown Cleaning Services\\Customers");
		FileStream ^ stmCustomer = File::Create(strPath);
		BinaryWriter ^ bnwCustomer =
			gcnew BinaryWriter(stmCustomer);
		Console::Write(L"Enter Customer Name: ");
		strCustomerName = Console::ReadLine();
		bnwCustomer->Write(strCustomerName);
		bnwCustomer->Write(strPhoneFormatted);

		custInfo->Name = strCustomerName;
		custInfo->PhoneNumber = strTelephoneNumber;
	}

	return custInfo;
	//throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}


void CCleaningDeposit::ProcessOrder()
{
	Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
	CCustomer ^ client = this->IdentifyCustomer();

	try {
		Console::Write(L"Enter the order date(mm/dd/yyyy):  ");
		this->depot->OrderDate = DateTime::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"The value you entered is not a valid date");
	}

	try {
		Console::Write(L"Enter the order time(hh:mm AM/PM): ");
		this->depot->OrderTime = DateTime::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"The value you entered is not a valid time");
	}

	// Request the quantity of each category of items
	try {
		Console::Write(L"Number of Shirts:      ");
		this->depot->NumberOfShirts =
			int::Parse(Console::ReadLine());

		if (this->depot->NumberOfShirts < int::MinValue)
			throw gcnew OverflowException(L"Negative value not "
				L"allowed for shirts");
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"The value you typed for the number of "
			L"shirts is not a valid number");
	}
	try {
		Console::Write(L"Number of Pants:       ");
		this->depot->NumberOfPants =
			int::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"The value you typed for the number of "
			L"pair or pants is not a valid number");
	}
	try {
		Console::Write(L"Number of Other Items: ");
		this->depot->NumberOtherItems = int::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"The value you typed for the number of "
			L"other items is not a valid number");
	}

	// Perform the necessary calculations
	this->depot->SubTotalShirts =
		this->depot->NumberOfShirts * this->depot->PriceOneShirt;
	this->depot->SubTotalPants =
		this->depot->NumberOfPants * this->depot->PriceAPairOfPants;
	this->depot->SubTotalOtherItems =
		this->depot->NumberOtherItems * this->depot->PriceOtherItems;
	// Calculate the "temporary" total of the order
	this->depot->TotalOrder = this->depot->SubTotalShirts +
		this->depot->SubTotalPants +
		this->depot->SubTotalOtherItems;

	// Calculate the tax amount using a constant rate
	this->depot->TaxAmount = this->depot->TotalOrder * this->depot->TaxRate;
	// Add the tax amount to the total order
	this->depot->SalesTotal = this->depot->TotalOrder + this->depot->TaxAmount;

	// Communicate the total to the user...
	Console::WriteLine(L"\nThe Total order is: {0:C}", this->depot->SalesTotal);
	// and request money for the order
	try {
		Console::Write(L"Amount Tended? ");
		AmountTended = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You were asked to enter an "
			L"amount of money but...");
	}
	// Calculate the difference owed to the customer
	// or that the customer still owes to the store
	Difference = AmountTended - this->depot->SalesTotal;

	this->ShowReceipt();
	this->Save();
	//throw gcnew System::NotImplementedException();
}


void CCleaningDeposit::Save()
{
	String ^ strPhoneNumber = this->custInfo->PhoneNumber;

	// Remove the spaces, parentheses, and dashes
	strPhoneNumber = strPhoneNumber->Replace(L" ", "");
	strPhoneNumber = strPhoneNumber->Replace(L"(L", "");
	strPhoneNumber = strPhoneNumber->Replace(L")", "");
	strPhoneNumber = strPhoneNumber->Replace(L"-", "");

	String ^ strMonth = depot->OrderDate.Month.ToString();
	if (depot->OrderDate.Month < 10)
		strMonth = L"0" + strMonth;

	String ^ strDay = depot->OrderDate.Day.ToString();
	if (depot->OrderDate.Day < 10)
		strDay = L"0" + strDay;

	String ^ strYear = depot->OrderDate.Year.ToString();

	String ^ strFilename = strMonth + strDay + strYear + L".gcs";

	String ^ strPath = L"C:\\Georgetown Cleaning Services\\Cleaning Orders\\"
		L"\\" + strPhoneNumber + L"\\" + strFilename;

	Directory::CreateDirectory(
		L"C:\\Georgetown Cleaning Services\\Cleaning Orders\\"
		+ strPhoneNumber);

	FileStream ^ stmCleaningOrder = File::Create(strPath);
	BinaryWriter ^ bnwCleaningOrder =
		gcnew BinaryWriter(stmCleaningOrder);

	bnwCleaningOrder->Write(this->custInfo->Name);
	bnwCleaningOrder->Write(this->custInfo->PhoneNumber);
	bnwCleaningOrder->Write(this->depot->OrderDate.ToString());
	bnwCleaningOrder->Write(this->depot->OrderTime.ToString());
	bnwCleaningOrder->Write(this->depot->NumberOfShirts.ToString());
	bnwCleaningOrder->Write(this->depot->NumberOfPants.ToString());
	bnwCleaningOrder->Write(this->depot->NumberOtherItems.ToString());
	bnwCleaningOrder->Write(this->depot->PriceOneShirt.ToString());
	bnwCleaningOrder->Write(this->depot->PriceAPairOfPants.ToString());
	bnwCleaningOrder->Write(this->depot->PriceOtherItems.ToString());
	bnwCleaningOrder->Write(this->depot->TaxRate.ToString());
	bnwCleaningOrder->Write(this->depot->SubTotalShirts.ToString());
	bnwCleaningOrder->Write(this->depot->SubTotalPants.ToString());
	bnwCleaningOrder->Write(this->depot->SubTotalOtherItems.ToString());
	bnwCleaningOrder->Write(this->depot->TotalOrder.ToString());
	bnwCleaningOrder->Write(this->depot->TaxAmount.ToString());
	bnwCleaningOrder->Write(this->depot->SalesTotal.ToString());
	//throw gcnew System::NotImplementedException();
}


void CCleaningDeposit::ShowReceipt()
{
	Console::WriteLine();
	// Display the receipt
	Console::WriteLine(L"====================================");
	Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
	Console::WriteLine(L"====================================");
	Console::WriteLine(L"Customer:    {0}", this->custInfo->Name);
	Console::WriteLine(L"Home Phone:  {0}", this->custInfo->PhoneNumber);
	Console::WriteLine(L"Order Date:  {0:D}", this->depot->OrderDate);
	Console::WriteLine(L"Order Time:  {0:t}", this->depot->OrderTime);
	Console::WriteLine(L"------------------------------------");
	Console::WriteLine(L"Item Type   Qty Unit/Price Sub-Total");
	Console::WriteLine(L"------------------------------------");
	Console::WriteLine(L"Shirts      {0,3}   {1,4}      {2,6}",
		this->depot->NumberOfShirts,
		this->depot->PriceOneShirt,
		this->depot->SubTotalShirts);
	Console::WriteLine(L"Pants       {0,3}   {1,4}      {2,6}",
		this->depot->NumberOfPants,
		this->depot->PriceAPairOfPants,
		this->depot->SubTotalPants);
	Console::WriteLine(L"Other Items {0,3}   {1,4}      {2,6}",
		this->depot->NumberOtherItems,
		this->depot->PriceOtherItems,
		this->depot->SubTotalOtherItems);
	Console::WriteLine(L"------------------------------------");
	Console::WriteLine(L"Total Order:   {0,6}",
		this->depot->TotalOrder.ToString(L"C"));
	Console::WriteLine(L"Tax Rate:      {0,6}",
		this->depot->TaxRate.ToString(L"P"));
	Console::WriteLine(L"Tax Amount:    {0,6}",
		this->depot->TaxAmount.ToString(L"C"));
	Console::WriteLine(L"Net Price:     {0,6}",
		this->depot->SalesTotal.ToString(L"C"));
	Console::WriteLine(L"====================================");
	//throw gcnew System::NotImplementedException();
}
