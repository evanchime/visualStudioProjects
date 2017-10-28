#pragma once

using namespace System;

namespace ElectronicsStore
{
	public ref class CStoreItem
	{
	private:
		long        nbr;
		__wchar_t ^ cat;
		String    ^ mk;
		String    ^ mdl;
		double      discount;
		double      price;

	public:
		inline long        GetItemNumber();
		inline void        SetItemNumber(const long number);
		inline __wchar_t ^ GetCategory();
		inline void        SetCategory(__wchar_t ^ category);
		inline String    ^ GetMake();
		inline void        SetMake(String ^ make);
		inline String    ^ GetModel();
		inline void        SetModel(String ^ model);
		inline double      GetDiscountRate();
		inline void        SetDiscountRate(const double discountRate);
		inline double      GetUnitPrice();
		inline void        SetUnitPrice(const double unitPrice);
	};
}
