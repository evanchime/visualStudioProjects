#include"stdafx.h"

#include "StoreItem.h"
using namespace System;

namespace ElectronicsStore
{
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

	inline void CStoreItem::SetUnitPrice(const double unitPrice)
	{
		this->price = unitPrice;
	}
}