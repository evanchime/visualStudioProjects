#include "stdafx.h"
#include "CleaningOrderManagement.h"


CleaningOrderManagement::CleaningOrderManagement()
{
		this->Customers = gcnew Hashtable();
		this->CleaningOrders = gcnew ArrayList();
		this->strPhoneNumber = L"(000) 000-0000";
		this->strCustomerName = L"Unknown";
		this->depot = gcnew CCleaningOrderDetails();

		CheckDefaultFolder();
		CheckDefaultFiles();
}
