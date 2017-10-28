#include "stdafx.h"

#include "StoreItem.h"
using namespace System;

namespace ElectronicsStore
{
	CStoreItem::CStoreItem(void)
		: nbr(0),
		cat(L'U'),
		mk(L"Unknown"),
		mdl(L"Unspecified"),
		nm(L"N/A"),
		discount(0.00),
		price(0.00)
	{
	}

	CStoreItem::CStoreItem(long itmNbr, String ^ make,
		String ^ model, double unitPrice)
		: nbr(itmNbr),
		cat(L'U'),
		mk(make),
		mdl(model),
		nm(L"N/A"),
		discount(0.00),
		price(unitPrice)
	{
	}

	CStoreItem::CStoreItem(long itmNbr, String ^ name,
		double unitPrice)
		: nbr(itmNbr),
		cat(L'U'),
		mk(L"Unknown"),
		mdl(L"Unspecified"),
		nm(name),
		discount(0.00),
		price(unitPrice)
	{
	}

	CStoreItem::CStoreItem(long itmNbr, __wchar_t category,
		String ^ make, String ^ model,
		double discountRate, double unitPrice)
		: nbr(itmNbr),
		cat(category),
		mk(make),
		mdl(model),
		discount(discountRate),
		price(unitPrice)
	{
	}

	CStoreItem::~CStoreItem()
	{
	}
}