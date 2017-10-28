#pragma once

using namespace System;

public enum class ItemsCategories
{
	Unknown,
	CablesAndConnectors,
	CellPhonesAndAccessories,
	Headphones,
	DigitalCameras,
	PDAsAndAccessories,
	TelephonesAndAccessories,
	TVsAndVideos,
	SurgeProtectors,
	Instructional
};

namespace ElectronicsStore
{
	public ref class CStoreItem
	{
	public:
		// An item whose characteristics are not (yet) defined
		CStoreItem(void);
		// An item that is known by its make, model, and unit price
		CStoreItem(long itmNbr, String ^ make,
			String ^ model, double unitPrice);
		// An item that is known by its name and unit price
		CStoreItem(long itmNbr, String ^ name, double unitPrice);
		// An item completely defined
		CStoreItem(long itmNbr, ItemsCategories category,
			String ^ make, String ^ model, double unitPrice);
		~CStoreItem();

	private:
		long            nbr;
		ItemsCategories cat;
		String        ^ mk;
		String        ^ mdl;
		String        ^ nm;
		double          price;

	public:
		property long ItemNumber
		{
			long get() { return nbr; }
			void set(long n) { this->nbr = n; }
		}

		property ItemsCategories Category
		{
			ItemsCategories get() { return cat; }
			void set(ItemsCategories c) { this->cat = c; }
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

		property double UnitPrice
		{
			double get() { return price; }
			void set(double p)
			{
				if (p <= 0)
					this->price = 0.00;
				else
					this->price = p;
			}
		}
	};
}

