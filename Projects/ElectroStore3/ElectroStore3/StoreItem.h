#pragma once

using namespace System;

namespace ElectronicsStore
{
	public ref class CStoreItem
	{
	public:
		// An item whose characteristics are not (yet) known
		CStoreItem(void);
		// An item that is known by its make, model, and unit price
		CStoreItem(long itmNbr, String ^ make,
			String ^ model, double unitPrice);
		// An item that is known by its name and unit price
		CStoreItem(long itmNbr, String ^ name, double unitPrice);
		// An item that is known by its category, make, model, discount price and unit price
		CStoreItem(long itmNbr, __wchar_t category, String ^ make,
			String ^ model, double discountPrice, double unitPrice);
		~CStoreItem();
	private:
		long        nbr;
		__wchar_t ^ cat;
		String    ^ mk;
		String    ^ mdl;
		String    ^ nm;
		double      discount;
		double      price;

	public:
		inline long        GetItemNumber();
		inline void        SetItemNumber(const long number);
		inline __wchar_t ^ GetCategory();
		inline void        SetCategory(__wchar_t ^ category);
		inline String    ^ GetMake();
		inline void        SetMake(String ^ make);
		inline String    ^ GetName();
		inline void        SetName(String ^ name);
		inline String    ^ GetModel();
		inline void        SetModel(String ^ model);
		inline double      GetDiscountRate();
		inline void        SetDiscountRate(const double discountRate);
		inline double      GetUnitPrice();
		inline void        SetUnitPrice(const double unitPrice);
	};
}
