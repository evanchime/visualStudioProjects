#include "stdafx.h"
#include "CleaningRetrieval.h"


CCleaningRetrieval::CCleaningRetrieval()
{
	this->custInfo = gcnew CCustomer;
	this->depot = gcnew CCleaningOrderDetails;
}


void CCleaningRetrieval::Open()
{
	Console::Write(L"Enter Receipt Number: ");
	String ^ strFilename = Console::ReadLine();

	String ^ strPath = L"C:\\Georgetown Cleaning Services\\Cleaning Orders\\"
		L"\\" + strFilename + L"\\" + strFilename + ".gcs";

	DirectoryInfo ^ di =
		gcnew DirectoryInfo(L"C:\\Georgetown Cleaning Services\\Cleaning Orders");
	array<FileInfo ^> ^ aryFiles = di->GetFiles(L"*", SearchOption::AllDirectories);

	String ^ strFileFullname = L"";
	bool found = false;

	for each(FileInfo ^ fle in aryFiles)
	{
		if (fle->Name == (strFilename + L".gcs"))
		{
			found = true;
			strFileFullname = fle->FullName;
		}
	}

	if (found == true)
	{
		FileStream ^ stmCleaningOrder =
			File::Open(strFileFullname,
				FileMode::Open,
				FileAccess::Read);
		BinaryReader ^ bnrCleaningOrder = gcnew BinaryReader(stmCleaningOrder);
		this->custInfo->Name = bnrCleaningOrder->ReadString();
		this->custInfo->PhoneNumber = bnrCleaningOrder->ReadString();
		this->depot->OrderDate = DateTime::Parse(bnrCleaningOrder->ReadString());
		this->depot->OrderTime = DateTime::Parse(bnrCleaningOrder->ReadString());
		this->depot->NumberOfShirts = int::Parse(bnrCleaningOrder->ReadString());
		this->depot->NumberOfPants = int::Parse(bnrCleaningOrder->ReadString());
		this->depot->NumberOtherItems =
			int::Parse(bnrCleaningOrder->ReadString());
		this->depot->PriceOneShirt =
			double::Parse(bnrCleaningOrder->ReadString());
		this->depot->PriceAPairOfPants =
			double::Parse(bnrCleaningOrder->ReadString());
		this->depot->PriceOtherItems =
			double::Parse(bnrCleaningOrder->ReadString());
		this->depot->TaxRate = double::Parse(bnrCleaningOrder->ReadString());
		this->depot->SubTotalShirts =
			double::Parse(bnrCleaningOrder->ReadString());
		this->depot->SubTotalPants =
			double::Parse(bnrCleaningOrder->ReadString());
		this->depot->SubTotalOtherItems =
			double::Parse(bnrCleaningOrder->ReadString());
		this->depot->TotalOrder = double::Parse(bnrCleaningOrder->ReadString());
		this->depot->TaxAmount = double::Parse(bnrCleaningOrder->ReadString());
		this->depot->SalesTotal = double::Parse(bnrCleaningOrder->ReadString());

		this->strPhoneNumber = String::Concat(L"(L",
			this->custInfo->PhoneNumber->Substring(0, 3),
			L") ",
			this->custInfo->PhoneNumber->Substring(3, 3),
			L"-",
			this->custInfo->PhoneNumber->Substring(6, 4));
		this->ShowReceipt();
	}
	else
		Console::WriteLine(L"No cleaning order of "
			L"that receipt number was found");
	//throw gcnew System::NotImplementedException();
}


void CCleaningRetrieval::ShowReceipt()
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
