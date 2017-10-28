#pragma once

using namespace System;

namespace ElectronicsStore
{
	public ref class CStoreItem
	{
	private:
		long        ItemNumber;
		__wchar_t ^ Category;
		String ^    Make;
		String ^    Model;
		double      DiscountRate;
		double      UnitPrice;
	};
}
