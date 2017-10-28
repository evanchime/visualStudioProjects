#pragma once
using namespace System;

[Serializable]
public ref class CPayrollInformation
{
private:
	String ^ number;
	String ^ fname;
	String ^ lname;
	double salary;
	DateTime start;

public:
	CPayrollInformation(void);

	property String ^ EmployeeNumber
	{
		String ^ get() { return this->number; }
		void set(String ^ value) { this->number = value; }
	}

	property String ^ FirstName
	{
		String ^ get() { return this->fname; }
		void set(String ^ value) { this->fname = value; }
	}

	property String ^ LastName
	{
		String ^ get() { return this->lname; }
		void set(String ^ value) { this->lname = value; }
	}

	property double HourlySalary
	{
		double get() { return this->salary; }
		void set(double value) { this->salary = value; }
	}

	property DateTime StartPeriod
	{
		DateTime get() { return this->start; }
		void set(DateTime value) { this->start = value; }
	}

	property DateTime EndPeriod
	{
		DateTime get() { return start.AddDays(13); }
	}

	double Week1Monday;
	double Week1Tuesday;
	double Week1Wednesday;
	double Week1Thursday;
	double Week1Friday;
	double Week2Monday;
	double Week2Tuesday;
	double Week2Wednesday;
	double Week2Thursday;
	double Week2Friday;

	double RegularHours;
	double OvertimeHours;
	double RegularAmount;
	double OvertimeAmount;
	double TotalEarnings;
};

