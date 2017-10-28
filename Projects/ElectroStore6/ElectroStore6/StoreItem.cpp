#include "stdafx.h"

#include "StoreItem.h"

namespace ElectronicsStore
{
	CStoreItem::CStoreItem(void)
	{
		nbr = 0;
		cat = ItemsCategories::Unknown;
		mk = L"Unknown";
		mdl = L"Unspecified";
		nm = L"N/A";
		price = 0.00;
	}

	CStoreItem::CStoreItem(long itmNbr, String ^ make,
		String ^ model, double unitPrice)
	{
		nbr = itmNbr;
		cat = ItemsCategories::Unknown;
		mk = make;
		mdl = model;
		nm = L"N/A";
		price = unitPrice;
	}

	CStoreItem::CStoreItem(long itmNbr, String ^ name,
		double unitPrice)
	{
		nbr = itmNbr;
		cat = ItemsCategories::Unknown;
		mk = L"Unknown";
		mdl = L"Unspecified";
		nm = name;
		price = unitPrice;
	}

	CStoreItem::CStoreItem(long itmNbr, ItemsCategories category,
		String ^ make, String ^ model,
		double unitPrice)
	{
		nbr = itmNbr;
		cat = category;
		mk = make;
		mdl = model;
		price = unitPrice;
	}

	CStoreItem::~CStoreItem()
	{
	}
}
