// GeorgetownCleaningServices7.cpp : main project file.

#include "stdafx.h"
#include "PayrollInformation.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;

void HireEmployee();
void CreatePayroll();
void SavePayroll(CPayrollInformation ^ pay);
void ShowPayroll(CPayrollInformation ^ payed);

void HireEmployee()
{
	FileStream ^ fsEmployee = nullptr;
	BinaryWriter ^ bwEmployee = nullptr;

	// Ask the clerk to enter an employee number
	// using the format 00-000
	Console::Write(L"Enter Employee Number (00-000): ");
	String ^emplNumber = Console::ReadLine();

	String ^ strPath = L"C:\\Georgetown Cleaning Services\\Employees\\"
		+ emplNumber + L".gce";

	if (File::Exists(strPath))
	{
		Console::Write(L"\nEither the employee has already been hired, ");
		Console::WriteLine(L"or there is already another employee with that number.");
		return;
	}
	else // If no employee with that number was found, create it
	{
		try {
			// If there is not yet a directory named Employees, then create it
			Directory::CreateDirectory(L"C:\\Georgetown Cleaning Services\\Employees");
		}
		catch (DirectoryNotFoundException ^)
		{
			Console::WriteLine(L"The folder could not be created");
		}

		try {
			fsEmployee = File::Create(strPath);
			bwEmployee = gcnew BinaryWriter(fsEmployee);
			Console::Write(L"Enter Employee First Name: ");
			String ^emplFName = Console::ReadLine();
			Console::Write(L"Enter Employee Last Name:  ");
			String ^emplLName = Console::ReadLine();
			Console::Write(L"Enter Hourly Salary: ");
			double emplSalary = double::Parse(Console::ReadLine());

			// The minimum salary in this company is 7.50
			if (emplSalary < 7.50)
				emplSalary = 7.50;

			bwEmployee->Write(emplNumber);
			bwEmployee->Write(emplFName);
			bwEmployee->Write(emplLName);
			bwEmployee->Write(emplSalary);
		}
		finally
		{
			bwEmployee->Close();
			fsEmployee->Close();
		}
	}

	Console::WriteLine();
}

void CreatePayroll()
{
	FileStream ^   fsPayroll = nullptr;
	BinaryReader ^ brPayroll = nullptr;
	DateTime dteStartDate;

	CPayrollInformation ^ payroll = gcnew CPayrollInformation();

	double monday1 = 0.00, tuesday1 = 0.00,
		wednesday1 = 0.00, thursday1 = 0.00,
		friday1 = 0.00, monday2 = 0.00,
		tuesday2 = 0.00, wednesday2 = 0.00,
		thursday2 = 0.00, friday2 = 0.00;
	double totalHoursWeek1 = 0.00,
		totalHoursWeek2 = 0.00;

	double regHours1 = 0.00, regHours2 = 0.00,
		ovtHours1 = 0.00, ovtHours2 = 0.00;
	double regAmount1 = 0.00, regAmount2 = 0.00,
		ovtAmount1 = 0.00, ovtAmount2 = 0.00;
	double regularHours = 0.00, overtimeHours = 0.00;
	double regularAmount = 0.00,
		overtimeAmount = 0.00,
		totalEarnings = 0.00;

	Console::Write(L"Enter Employee Number: ");
	String ^emplNumber = Console::ReadLine();

	String ^ strEmployeePath = L"C:\\Georgetown "
		L"Cleaning Services\\Employees\\"
		+ emplNumber + ".gce";

	if (!File::Exists(strEmployeePath))
	{
		Console::WriteLine(L"There is no employee with "
			L"that number in our records");
		return;
	}
	// If an employee with that number was found,
	// continue with the payroll
	else
	{
		try {
			fsPayroll = gcnew FileStream(strEmployeePath,
				FileMode::Open,
				FileAccess::Read);
			brPayroll = gcnew BinaryReader(fsPayroll);

			payroll->EmployeeNumber = brPayroll->ReadString();
			payroll->FirstName = brPayroll->ReadString();
			payroll->LastName = brPayroll->ReadString();
			payroll->HourlySalary = brPayroll->ReadDouble();

			Console::WriteLine(L"\n------------------------"
				L"------------------------");
			Console::WriteLine(L"Employee #:    {0}",
				payroll->EmployeeNumber);
			Console::WriteLine(L"Full Name:     {0}, {1}",
				payroll->LastName,
				payroll->FirstName);
			Console::WriteLine(L"Hourly Salary: {0:C}",
				payroll->HourlySalary);
			Console::WriteLine(L"-------------------------"
				L"-----------------------\n");
		}
		finally
		{
			brPayroll->Close();
			fsPayroll->Close();
		}

		try {
			do {
				Console::Write(L"Enter Payroll Start "
					L"Date (mm/dd/yyyy): ");
				dteStartDate = DateTime::Parse(Console::ReadLine());

				if (dteStartDate.DayOfWeek != DayOfWeek::Sunday)
				{
					Console::WriteLine(L"Invalid Date Entry");
					Console::WriteLine(L"Payrolls start "
						L"on a Sunday");
				}
			} while (dteStartDate.DayOfWeek !=
				DayOfWeek::Sunday);

			payroll->StartPeriod = dteStartDate;
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"Invalid Date Entry");
		}
	}

	// Retrieve the value of each day worked
	Console::WriteLine(L"\nEnter the time worked "
		L"for each day (0.00)");
	Console::WriteLine(L"=-= Week 1 =-=");
	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(1).ToString(L"D"));
		monday1 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(2).ToString(L"D"));
		tuesday1 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(3).ToString(L"D"));
		wednesday1 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(4).ToString(L"D"));
		thursday1 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(5).ToString(L"D"));
		friday1 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	Console::WriteLine(L"=-= Week 2 =-=");
	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(8).ToString(L"D"));
		monday2 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(9).ToString(L"D"));
		tuesday2 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(10).ToString(L"D"));
		wednesday2 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(11).ToString(L"D"));
		thursday2 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	try {
		Console::Write(L"{0}: ",
			payroll->StartPeriod.AddDays(12).ToString(L"D"));
		friday2 = double::Parse(Console::ReadLine());
	}
	catch (FormatException ^)
	{
		Console::WriteLine(L"You typed an invalid value");
	}

	// Calculate the total number of hours for each week
	totalHoursWeek1 = monday1 + tuesday1 + wednesday1 +
		thursday1 + friday1;
	totalHoursWeek2 = monday2 + tuesday2 + wednesday2 +
		thursday2 + friday2;

	// The overtime is paid time and half
	double ovtSalary = payroll->HourlySalary * 1.5;

	// If the employee worked under 40 hours,
	// there is no overtime
	if (totalHoursWeek1 < 40)
	{
		regHours1 = totalHoursWeek1;
		regAmount1 = payroll->HourlySalary * regHours1;
		ovtHours1 = 0.00;
		ovtAmount1 = 0.00;
	} // If the employee worked over 40 hours,
	  // calculate the overtime
	else if (totalHoursWeek1 >= 40)
	{
		regHours1 = 40;
		regAmount1 = payroll->HourlySalary * 40;
		ovtHours1 = totalHoursWeek1 - 40;
		ovtAmount1 = ovtHours1 * ovtSalary;
	}

	if (totalHoursWeek2 < 40)
	{
		regHours2 = totalHoursWeek2;
		regAmount2 = payroll->HourlySalary * regHours2;
		ovtHours2 = 0.00;
		ovtAmount2 = 0.00;
	}
	else if (totalHoursWeek2 >= 40)
	{
		regHours2 = 40;
		regAmount2 = payroll->HourlySalary * 40;
		ovtHours2 = totalHoursWeek2 - 40;
		ovtAmount2 = ovtHours2 * ovtSalary;
	}

	regularHours = regHours1 + regHours2;
	overtimeHours = ovtHours1 + ovtHours2;
	regularAmount = regAmount1 + regAmount2;
	overtimeAmount = ovtAmount1 + ovtAmount2;
	totalEarnings = regularAmount + overtimeAmount;

	payroll->Week1Monday = monday1;
	payroll->Week1Tuesday = tuesday1;
	payroll->Week1Wednesday = wednesday1;
	payroll->Week1Thursday = thursday1;
	payroll->Week1Friday = friday1;

	payroll->Week2Monday = monday2;
	payroll->Week2Tuesday = tuesday2;
	payroll->Week2Wednesday = wednesday2;
	payroll->Week2Thursday = thursday2;
	payroll->Week2Friday = friday2;

	payroll->RegularHours = regularHours;
	payroll->OvertimeHours = overtimeHours;
	payroll->RegularAmount = regularAmount;
	payroll->OvertimeAmount = overtimeAmount;
	payroll->TotalEarnings = totalEarnings;

	ShowPayroll(payroll);

	Console::Write(L"Do you want to save "
		L"the payroll (y/n): ");
	String ^ strAnswer = Console::ReadLine();

	if (strAnswer->ToUpper() == L"Y")
		SavePayroll(payroll);
}

void SavePayroll(CPayrollInformation ^ pay)
{
	// We will need this value to create the
	// name of the payroll file
	String ^ strMonth = L"0", ^strDay = L"0", ^strYear = L"0";

	// We want the month and day to include 0 if necessary
	strMonth = pay->StartPeriod.Month.ToString();

	if (pay->StartPeriod.Month < 10)
		strMonth = L"0" + pay->StartPeriod.Month.ToString();

	strDay = pay->StartPeriod.Day.ToString();
	if (pay->StartPeriod.Day < 10)
		strDay = L"0" + pay->StartPeriod.Day.ToString();

	strYear = pay->StartPeriod.Year.ToString();

	String ^ strPayrollFilename = L"C:\\Georgetown "
		L"Cleaning Services\\Payrolls\\"
		+ pay->LastName[0] +
		pay->FirstName[0] +
		strMonth + strDay +
		strYear + ".epr";

	try {
		// If there is not yet a directory for the 
		// payrolls, then create it
		Directory::CreateDirectory(L"C:\\Georgetown Cleaning "
			L"Services\\Payrolls");
	}
	catch (DirectoryNotFoundException ^)
	{
		Console::WriteLine(L"The employee payroll file "
			L"could not be created");
	}

	if (File::Exists(strPayrollFilename))
	{
		Console::WriteLine(L"The employee's payroll "
			L"for that period exists already");
	}

	FileStream ^ fsEmployeePayroll =
		gcnew FileStream(strPayrollFilename,
			FileMode::Create);
	BinaryFormatter ^ bfEmployeePayroll =
		gcnew BinaryFormatter();

	bfEmployeePayroll->Serialize(fsEmployeePayroll, pay);
	fsEmployeePayroll->Close();
}

void ShowPayroll(CPayrollInformation ^ payed)
{
	Console::WriteLine(L"\n============================="
		L"===================");
	Console::WriteLine(L"=$= Payroll summary =$=");
	Console::WriteLine(L"-------------------------------"
		L"-----------------");
	Console::WriteLine(L"Employee #:    {0}",
		payed->EmployeeNumber);
	Console::WriteLine(L"Full Name:     {0}, {1}",
		payed->FirstName, payed->LastName);
	Console::WriteLine(L"Hourly Salary: {0:C}",
		payed->HourlySalary);
	Console::WriteLine(L"Start Period:  {0:D}",
		payed->StartPeriod);
	Console::WriteLine(L"End Period:    {0:D}",
		payed->EndPeriod);
	Console::WriteLine(L"--------------------------------"
		L"----------------");
	Console::WriteLine(L"        Monday Tuesday Wednesday "
		L"Thursday Friday");
	Console::WriteLine(L"Week 1:  {0:F}   {1:F}     "
		L"{2:F}      {3:F}    {4:F}",
		payed->Week1Monday, payed->Week1Tuesday,
		payed->Week1Wednesday, payed->Week1Thursday,
		payed->Week1Friday);
	Console::WriteLine(L"Week 2:  {0:F}   {1:F}     "
		L"{2:F}      {3:F}    {4:F}",
		payed->Week2Monday, payed->Week2Tuesday,
		payed->Week2Wednesday, payed->Week2Thursday,
		payed->Week2Friday);
	Console::WriteLine(L"-------------------------------"
		L"-----------------");
	Console::WriteLine(L"Monetary Summary");
	Console::WriteLine(L"            Hours   Amount");
	Console::WriteLine(L"Regular:   {0,6}   {1,6}",
		payed->RegularHours.ToString(L"F"),
		payed->RegularAmount.ToString(L"F"));
	Console::WriteLine(L"Overtime:  {0,6}   {1,6}",
		payed->OvertimeHours.ToString(L"F"),
		payed->OvertimeAmount.ToString(L"F"));
	Console::WriteLine(L"-------------------------------"
		L"-----------------");
	Console::WriteLine(L"Net Pay:   {0:F}",
		payed->TotalEarnings);
	Console::WriteLine(L"==============================="
		L"=================\n");
}

void ViewPayroll()
{
	String ^ strEmplNumber, ^strFName, ^strLName;
	String ^ strMonth, ^strDay, ^strYear;

	// Ask the clerk to enter an employee number
	// using the format 00-000
	Console::Write(L"Enter Employee Number (00-000): ");
	strEmplNumber = Console::ReadLine();

	String ^ strFilename = L"C:\\Georgetown Cleaning "
		L"Services\\Employees\\"
		+ strEmplNumber + ".gce";

	if (!File::Exists(strFilename))
	{
		Console::Write(L"There is no employee "
			L"with that number.");
	}
	else
	{
		FileStream ^ fsEmployee = nullptr;
		BinaryReader ^ brEmployee = nullptr;

		try {
			// We need to formally open the file 
			// because we need the employees initials
			fsEmployee = gcnew FileStream(strFilename,
				FileMode::Open,
				FileAccess::Read);
			brEmployee = gcnew BinaryReader(fsEmployee);

			// Read the file, mainly to get the 
			// employee's name
			strEmplNumber = brEmployee->ReadString();
			strFName = brEmployee->ReadString();
			strLName = brEmployee->ReadString();
		}
		finally
		{
			brEmployee->Close();
			fsEmployee->Close();
		}

		Console::Write(L"Enter the start date of the "
			L"payroll you want to see (mm/dd/yyyy): ");
		DateTime dteStartDate =
			DateTime::Parse(Console::ReadLine());

		// We want the month and day to include 0 if necessary
		strMonth = dteStartDate.Month.ToString();
		if (dteStartDate.Month < 10)
			strMonth = L"0" + dteStartDate.Month.ToString();

		strDay = dteStartDate.Day.ToString();
		if (dteStartDate.Day < 10)
			strDay = L"0" + dteStartDate.Day.ToString();

		strYear = dteStartDate.Year.ToString();

		strFilename = L"C:\\Georgetown Cleaning "
			L"Services\\Payrolls\\"
			+ strLName[0] +
			strFName[0] + strMonth +
			strDay + strYear + ".epr";

		if (!File::Exists(strFilename))
		{
			Console::Write(L"{0}, {1} doesn't have a "
				L"payroll in that time frame",
				strLName, strFName);
		}
		else
		{
			// Open the payroll and display it
			FileStream ^ fsPayroll =
				gcnew FileStream(strFilename,
					FileMode::Open);
			BinaryFormatter ^ bfPayroll =
				gcnew BinaryFormatter();
			CPayrollInformation ^ pay =
				dynamic_cast<CPayrollInformation ^>
				(bfPayroll->Deserialize(fsPayroll));

			ShowPayroll(pay);
		}
	}
}

int main()
{
	wchar_t answer = L'0';

	Console::WriteLine(L"========================"
		L"========================");
	Console::WriteLine(L"Georgetown Cleaning Services");
	Console::WriteLine(L"========================"
		L"========================");

	do {
		try {
			Console::WriteLine(L"\nWhat do you want to do?");
			Console::WriteLine(L"0. Quit");
			Console::WriteLine(L"1. Hire a new employee");
			Console::WriteLine(L"2. Process a payroll");
			Console::WriteLine(L"3. View an employee's payroll");
			Console::Write(L"Your Choice: ");
			answer = wchar_t::Parse(Console::ReadLine());
			Console::WriteLine();
		}
		catch (FormatException ^)
		{
			Console::WriteLine(L"Invalid Answer!");
		}

		switch (answer)
		{
		case L'1':
			HireEmployee();
			break;
		case L'2':
			CreatePayroll();
			break;
		case L'3':
			ViewPayroll();
			break;
		default:
			break;
		}

	} while ((answer == L'1') ||
		(answer == L'2') ||
		(answer == L'3'));

	Console::WriteLine();
	return 0;
}