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
		// An item completely defined
		CStoreItem(long itmNbr, __wchar_t category,
			String ^ make, String ^ model,
			double discountRate, double unitPrice);
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
		property long ItemNumber
		{
			long get() { return nbr; }
			void set(long n) { this->nbr = n; }
		}

		property __wchar_t ^ Category
		{
			__wchar_t ^ get() { return cat; }
			void set(__wchar_t ^ n) { this->cat = n; }
		}

		property String ^ Make
		{
			String ^ get() { return mk; }
			void set(String ^ m) { this->mk = m; }
		}

		property String ^ Model
		{
			String ^ get() { return mdl; }
			void set(String ^ m) { this->mdl = m; }
		}

		property String ^ Name
		{
			String ^ get() { return nm; }
			void set(String ^ n) { this->nm = n; }
		}

		property double DiscountRate
		{
			double get() { return discount; }
			void set(double d) { this->discount = d; }
		}

		property double UnitPrice
		{
			double get() { return price; }
			void set(double p) { this->price = p; }
		}
	};
}
