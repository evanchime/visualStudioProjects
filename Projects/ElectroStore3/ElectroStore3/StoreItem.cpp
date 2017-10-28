
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

	CStoreItem::CStoreItem(long itmNbr, String ^ name, double unitPrice)
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
	{}

	CStoreItem::~CStoreItem()
	{

	}

	inline long CStoreItem::GetItemNumber()
	{
		return nbr;
	}

	inline void CStoreItem::SetItemNumber(const long number)
	{
		this->nbr = number;
	}

	inline __wchar_t ^ CStoreItem::GetCategory()
	{
		return cat;
	}

	inline void CStoreItem::SetCategory(__wchar_t ^ category)
	{
		this->cat = category;
	}

	inline String ^ CStoreItem::GetMake()
	{
		return mk;
	}

	inline void CStoreItem::SetMake(String ^ make)
	{
		this->mk = make;
	}

	inline String ^ CStoreItem::GetModel()
	{
		return mdl;
	}

	inline void CStoreItem::SetModel(String ^ model)
	{
		this->mdl = model;
	}

	inline double CStoreItem::GetDiscountRate()
	{
		return discount / 100;
	}

	inline void CStoreItem::SetDiscountRate(const double discountRate)
	{
		this->discount = discountRate;
	}

	inline double CStoreItem::GetUnitPrice()
	{
		return price;
	}

	inline String ^ CStoreItem::GetName()
	{
		return nm;
	}

	inline void CStoreItem::SetName(String ^ name)
	{
		name = nm;
	}

	inline void CStoreItem::SetUnitPrice(const double unitPrice)
	{
		this->price = unitPrice;
	}
}