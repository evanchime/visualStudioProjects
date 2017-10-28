#pragma once
#include "CarInventory.h"
#include "CarIdentifier.h"

using namespace System::Collections;

public ref class CCars : public IEnumerable
{
private:
	CCarInventory ^ items;

public:
	void Locate(CCarInventory ^ list);
	virtual IEnumerator ^ GetEnumerator();

	CCars(void);
};

