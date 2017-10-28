#pragma once
#include "Customer.h"
#include "CleaningOrderDetail.h"

public ref class CCustomerOrder abstract
{
public:
	virtual void ProcessOrder() = 0;
	virtual void ShowReceipt() = 0;
};

public ref class CCleaningDeposit : CCustomerOrder
{
private:
	CCustomer ^ custInfo;
	double AmountTended;
	double Difference;

public:
	CCleaningOrderDetails ^ depot;
	CCleaningDeposit(void);
	CCustomer ^ IdentifyCustomer();
	void ProcessOrder() override;
	void Save();
	void ShowReceipt() override;
};

