#pragma once
#include "CleaningOrderDetails.h"
using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Runtime::Serialization::Formatters::Binary;



public ref class CleaningOrderManagement
{
	// We need a global customer info to 
	// modify/update it from anywhere
	String ^ strCustomerName;
	String ^ strPhoneNumber;

	// This is the list that will hold the cleaning orders
	ArrayList ^ CleaningOrders;
	// This is a list that will hold the combinations of 
	// a customer's name and telephone number
private:
	Hashtable ^ Customers;
public:
	CCleaningOrderDetails ^ depot;

public:
	CleaningOrderManagement();
private:
	void CheckDefaultFolder()
	{
		DirectoryInfo ^ diGCS =
			gcnew DirectoryInfo("C:\\Georgetown "
				"Cleaning Services");
		try
		{
			if (!diGCS->Exists)
				diGCS->Create();
		}
		catch (IOException ^)
		{
			Console::WriteLine(L"The directory could not be created");
		}
	}

	// This method ensures that there are the necessary files 
	// used to process a cleaning order
public:
	void CheckDefaultFiles()
	{
		FileStream ^ fsCustomers = nullptr;
		BinaryFormatter ^ bfCustomers = gcnew BinaryFormatter();

		// The Customers.cst file will contain the 
		// information about the customers
		String ^ strFilename =
			"C:\\Georgetown Cleaning Services\\Customers.cst";

		// When the application starts, if the list of
		// customers doesn't (yet) exist, then create it
		if (!File::Exists(strFilename))
		{
			Customers->Add(strPhoneNumber, strCustomerName);

			try
			{
				fsCustomers = gcnew FileStream(strFilename,
					FileMode::Create,
					FileAccess::Write);
				bfCustomers->Serialize(fsCustomers, Customers);
			}
			finally
			{
				fsCustomers->Close();
			}
		}

		// The CleaningOrders.gco file will 
		// contain the cleaning orders
		strFilename = "C:\\Georgetown Cleaning "
			"Services\\CleaningOrders.gco";

		if (!File::Exists(strFilename))
		{
			FileStream ^ fsCleaningOrders = nullptr;
			BinaryFormatter ^ bfCleaningOrders =
				gcnew BinaryFormatter();

			// This file will contain only useless default values
			// Normally, this cleaning order should never be deleted
			depot->ReceiptNumber = 0;
			depot->CustomerName = strCustomerName;
			depot->CustomerPhoneNumber = strPhoneNumber;
			depot->OrderDate = gcnew DateTime(1960, 1, 1);
			depot->OrderTime = gcnew DateTime(1960, 1, 1,
				1, 1, 1);
			depot->NumberOfShirts = 0;
			depot->NumberOfPants = 0;
			depot->NumberOtherItems = 0;

			depot->PriceOneShirt = 0.00;
			depot->PriceAPairOfPants = 0.00;
			depot->PriceOtherItems = 0.00;
			depot->TaxRate = 0.00;  // 5.75%

			depot->SubTotalShirts = 0;
			depot->SubTotalPants = 0;
			depot->SubTotalOtherItems = 0;

			depot->TotalOrder = 0;
			depot->TaxAmount = 0;
			depot->SalesTotal = 0;

			// After creating this default order, 
			// add it to the collection
			this->CleaningOrders->Add(this->depot);

			// After creating the cleaning order, save it
			try
			{
				fsCleaningOrders = gcnew FileStream(strFilename,
					FileMode::Create,
					FileAccess::Write);
				bfCleaningOrders->Serialize(fsCleaningOrders,
					CleaningOrders);
			}
			finally
			{
				fsCleaningOrders->Close();
			}
		}
	}

	// This method is used to find out if the customer 
	// already exists in our database
private:
	void IdentifyCustomer()
	{
		bool found = false;
		String ^ strTelephoneNumber = L"000";

		do
		{
			Console::Write(L"Enter Customer Phone Number: ");
			strTelephoneNumber = Console::ReadLine();

			// Remove the spaces, parentheses, and dashes, if any
			strTelephoneNumber =
				strTelephoneNumber->Replace(L" ", L"");
			strTelephoneNumber =
				strTelephoneNumber->Replace(L"(L", L"");
			strTelephoneNumber =
				strTelephoneNumber->Replace(L")", L"");
			strTelephoneNumber =
				strTelephoneNumber->Replace(L"-", L"");

			if (strTelephoneNumber->Length != 10)
			{
				// We will use a (small version of) 
				// Canada and US telephone numbers
				Console::WriteLine(L"Invalid telphone number: "
					"you entered {0} "
					"characters instead of 10 digits",
					strTelephoneNumber->Length);
			}
		} while (strTelephoneNumber->Length != 10);

		// We will use the same formula for 
		// telephone numbers: (000) 000-0000
		strPhoneNumber = L"(L" + strTelephoneNumber->Substring(0, 3) +
			") " + strTelephoneNumber->Substring(3, 3) +
			"-" + strTelephoneNumber->Substring(6, 4);

		String ^ strFilename =
			"C:\\Georgetown Cleaning Services\\Customers.cst";

		if (File::Exists(strFilename))
		{
			FileStream ^ fsCustomers = File::Open(strFilename,
				FileMode::Open,
				FileAccess::Read);
			BinaryFormatter ^ bfCustomers = gcnew BinaryFormatter();
			Customers = dynamic_cast<Hashtable ^>(bfCustomers->Deserialize(fsCustomers));
			fsCustomers->Close();

			for each(DictionaryEntry ^ de in Customers)
			{
				if ((String ^)de->Key == strPhoneNumber)
				{
					found = true;
					strPhoneNumber = (String ^)de->Key;
					strCustomerName = (String ^)de->Value;
				}
			}

			if (found == true)
			{
				Console::WriteLine(L"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
				Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
				Console::WriteLine(L"------------------------------------");
				Console::WriteLine(L"Customer Name: {0}", strCustomerName);
				Console::WriteLine(L"Phone Number:  {0}", strPhoneNumber);
				Console::WriteLine(L"------------------------------------\n");
			}
			else // If the customer information was not found in a file
			{
				Console::WriteLine(L"This is the first cleaning order "
					"of this customer");
				FileStream ^ fsCustomer = gcnew FileStream(strFilename,
					FileMode::Create,
					FileAccess::Write);
				BinaryFormatter ^ bfCustomer = gcnew BinaryFormatter();
				Console::Write(L"Enter Customer Name: ");
				strCustomerName = Console::ReadLine();

				Customers->Add(strPhoneNumber, strCustomerName);
				bfCustomer->Serialize(fsCustomer, Customers);
				fsCustomer->Close();
			}
		}
		else
			Console::WriteLine(L"The Customers list was not found");
	}

public:
	void ProcessOrder()
	{
		// These two pieces of information are used for money change
		//double AmountTended;
		//double Difference;

		Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
		this->IdentifyCustomer();

		try
		{
			Console::Write(L"Enter the order date(mm/dd/yyyy):  ");
			depot->OrderDate = DateTime::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"The value you entered is not a valid date");
		}
		try
		{
			Console::Write(L"Enter the order time(hh:mm AM/PM): ");
			depot->OrderTime = DateTime::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"The value you entered is not a valid time");
		}

		// Request the quantity of each category of items
		try
		{
			Console::Write(L"Number of Shirts:      ");
			depot->NumberOfShirts =
				UInt32::Parse(Console::ReadLine());
			if (depot->NumberOfShirts < 0)
				throw gcnew OverflowException(L"Negative value not "
					"allowed for shirts");
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"The value you typed for the number of "
				"shirts is not a valid number");
		}
		try
		{
			Console::Write(L"Number of Pants:       ");
			depot->NumberOfPants =
				UInt32::Parse(Console::ReadLine());
			if (depot->NumberOfPants < 0)
				throw gcnew OverflowException(L"Negative value not "
					"allowed for shirts");
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"The value you typed for the number"
				"pair or pants is not a valid number");
		}
		try
		{
			Console::Write(L"Number of Other Items: ");
			depot->NumberOtherItems = UInt32::Parse(Console::ReadLine());
			if (depot->NumberOtherItems < 0)
				throw gcnew OverflowException(L"Negative value not "
					"allowed for shirts");
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"The value you typed for the number of "
				"other items is not a valid number");
		}
		// Perform the necessary calculations
		depot->SubTotalShirts =
			depot->NumberOfShirts * depot->PriceOneShirt;
		depot->SubTotalPants =
			depot->NumberOfPants * depot->PriceAPairOfPants;
		depot->SubTotalOtherItems =
			depot->NumberOtherItems * depot->PriceOtherItems;
		// Calculate the "temporary" total of the order
		depot->TotalOrder = depot->SubTotalShirts +
			depot->SubTotalPants +
			depot->SubTotalOtherItems;

		// Calculate the tax amount using a constant rate
		depot->TaxAmount = depot->TotalOrder * depot->TaxRate;
		// Add the tax amount to the total order
		depot->SalesTotal = depot->TotalOrder + depot->TaxAmount;

		// Communicate the total to the user...
		Console::WriteLine(L"\nThe Total order is: {0:C}", depot->SalesTotal);
		// and request money for the order
		try
		{
			Console::Write(L"Amount Tended? ");
			depot->AmountTended = double::Parse(Console::ReadLine());
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"You were asked to enter an "
				"amount of money but...");
		}
		// Calculate the difference owed to the customer
		// or that the customer still owes to the store
		depot->Difference = depot->AmountTended - depot->SalesTotal;

		this->PreviewReceipt();
		this->SaveCleaningOrder();
	}

public:
	void PreviewReceipt()
	{
		Console::WriteLine();
		// Display the receipt
		Console::WriteLine(L"====================================");
		Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
		Console::WriteLine(L"====================================");
		Console::WriteLine(L"Customer:    {0}", /*this->*/strCustomerName);
		Console::WriteLine(L"Home Phone:  {0}", /*this->*/strPhoneNumber);
		Console::WriteLine(L"Order Date:  {0:D}", depot->OrderDate);
		Console::WriteLine(L"Order Time:  {0:t}", depot->OrderTime);
		Console::WriteLine(L"------------------------------------");
		Console::WriteLine(L"Item Type    Qty Unit/Price Sub-Total");
		Console::WriteLine(L"------------------------------------");
		Console::WriteLine(L"Shirts      {0,3}   {1,4}      {2,6}",
			depot->NumberOfShirts,
			depot->PriceOneShirt,
			depot->SubTotalShirts);
		Console::WriteLine(L"Pants       {0,3}   {1,4}      {2,6}",
			depot->NumberOfPants,
			depot->PriceAPairOfPants,
			depot->SubTotalPants);
		Console::WriteLine(L"Other Items {0,3}   {1,4}      {2,6}",
			depot->NumberOtherItems,
			depot->PriceOtherItems,
			depot->SubTotalOtherItems);
		Console::WriteLine(L"------------------------------------");
		Console::WriteLine(L"Total Order:   {0,6}",
			depot->TotalOrder.ToString(L"C"));
		Console::WriteLine(L"Tax Rate:      {0,6}",
			depot->TaxRate.ToString(L"P"));
		Console::WriteLine(L"Tax Amount:    {0,6}",
			depot->TaxAmount.ToString(L"C"));
		Console::WriteLine(L"Net Price:     {0,6}",
			depot->SalesTotal.ToString(L"C"));
		Console::WriteLine(L"------------------------------------");
		Console::WriteLine(L"Amount Tended: {0,6}",
			depot->AmountTended.ToString(L"C"));
		Console::WriteLine(L"Difference:    {0,6}",
			depot->Difference.ToString(L"C"));
		Console::WriteLine(L"====================================");
	}

public:
	void SaveCleaningOrder()
	{
		//int highReceiptNumber = 0;
		FileStream ^ fsCleaningOrders = nullptr;
		BinaryFormatter ^ bfCleaningOrders = gcnew BinaryFormatter();

		String ^ strFilename =
			"C:\\Georgetown Cleaning Services\\CleaningOrders.gco";

		if (File::Exists(strFilename))
		{
			/*try
			{
				fsCleaningOrders = gcnew FileStream(strFilename,
					FileMode::Open,
					FileAccess::Read);
				CleaningOrders =
					dynamic_cast<ArrayList ^>(bfCleaningOrders->Deserialize(fsCleaningOrders));
			}
			finally
			{
				fsCleaningOrders->Close();
			}*/
			//highReceiptNumber = (dynamic_cast<CCleaningOrderDetails ^>(CleaningOrders[CleaningOrders->Count]))->ReceiptNumber;

			depot->ReceiptNumber = /*highReceiptNumber*/ CleaningOrders->Count + 1;
			depot->CustomerName = strCustomerName;
			depot->CustomerPhoneNumber = strPhoneNumber;

			this->CleaningOrders->Add(this->depot);

			try
			{
				fsCleaningOrders = gcnew FileStream(strFilename,
					FileMode::Create,
					FileAccess::Write);
				bfCleaningOrders->Serialize(fsCleaningOrders,
					CleaningOrders);
			}
			finally
			{
				fsCleaningOrders->Close();
			}
		}
		else
			Console::WriteLine(L"The cleaning orders could "
				"not be retrieved");
	}

public:
	void OpenCleaningOrder()
	{
		bool foundReceipt = false;

		try
		{
			Console::Write(L"Enter Receipt Number: ");
			int recNumber = int::Parse(Console::ReadLine());

			FileStream ^ fsCleaningOrders = nullptr;
			BinaryFormatter ^ bfCleaningOrders = gcnew BinaryFormatter();

			String ^ strFilename =
				"C:\\Georgetown Cleaning Services\\CleaningOrders.gco";

			if (File::Exists(strFilename))
			{
				try
				{
					fsCleaningOrders = gcnew FileStream(strFilename,
						FileMode::Open,
						FileAccess::Read);
					CleaningOrders =
						(ArrayList ^)(bfCleaningOrders->Deserialize(fsCleaningOrders));
				}
				finally
				{
					fsCleaningOrders->Close();
				}

				for each(CCleaningOrderDetails ^ cod in CleaningOrders)
				{
					if (cod->ReceiptNumber == recNumber)
					{
						foundReceipt = true;

						// Display the
						Console::WriteLine(L"====================================");
						Console::WriteLine(L"-/- Georgetown Cleaning Services -/-");
						Console::WriteLine(L"====================================");
						Console::WriteLine(L"Receipt #:   {0}", cod->ReceiptNumber);
						Console::WriteLine(L"Customer:    {0}", cod->CustomerName);
						Console::WriteLine(L"Home Phone:  {0}",
							cod->CustomerPhoneNumber);
						Console::WriteLine(L"Order Date:  {0:D}", cod->OrderDate);
						Console::WriteLine(L"Order Time:  {0:t}", cod->OrderTime);
						Console::WriteLine(L"------------------------------------");
						Console::WriteLine(L"Item Type   Qty Unit/Price Sub-Total");
						Console::WriteLine(L"------------------------------------");
						Console::WriteLine(L"Shirts      {0,3}   {1,4}      {2,6}",
							cod->NumberOfShirts,
							cod->PriceOneShirt,
							cod->SubTotalShirts);
						Console::WriteLine(L"Pants       {0,3}   {1,4}      {2,6}",
							cod->NumberOfPants,
							cod->PriceAPairOfPants,
							cod->SubTotalPants);
						Console::WriteLine(L"Other Items {0,3}   {1,4}      {2,6}",
							cod->NumberOtherItems,
							cod->PriceOtherItems,
							cod->SubTotalOtherItems);
						Console::WriteLine(L"------------------------------------");
						Console::WriteLine(L"Total Order:   {0,6}",
							cod->TotalOrder.ToString(L"C"));
						Console::WriteLine(L"Tax Rate:      {0,6}",
							cod->TaxRate.ToString(L"P"));
						Console::WriteLine(L"Tax Amount:    {0,6}",
							cod->TaxAmount.ToString(L"C"));
						Console::WriteLine(L"Net Price:     {0,6}",
							cod->SalesTotal.ToString(L"C"));
						Console::WriteLine(L"====================================");

						return;
					} // if found receipt number
				}// foreach

				if (foundReceipt == false)
					Console::WriteLine(L"No cleaning order with that "
						"receipt number was found");
			}// if file exists
			else
				Console::WriteLine(L"The cleaning orders were not found");
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"Invalid Choice");
		}
	}
};

