#pragma once
#include "Customer.h"
#include "CleaningOrderDetail.h"

using namespace System;
using namespace System::IO;

ref class CCleaningRetrieval
{
private:
	CCustomer ^ custInfo;
	CCleaningOrderDetails ^ depot;
	String ^ strPhoneNumber;

public:
	CCleaningRetrieval(void);
	virtual void Open();
	void ShowReceipt();
};

