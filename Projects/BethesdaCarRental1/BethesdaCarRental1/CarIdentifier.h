#pragma once
#include "CarInventory.h"

using namespace System;
using namespace System::Collections;

public ref class CCarIdentifier : public IEnumerator
{
private:
	int curPosition;

public:
	CCarInventory ^ counts;
	void Identify(CCarInventory ^ list);

	property Object ^ Current
	{
		virtual Object ^ get()
		{
			try {
				return counts->Get(this->curPosition);
			}
			catch (IndexOutOfRangeException ^)
			{
				Console::WriteLine(L"The current item must be accessed "
					L"within the range of available items");
				return nullptr;
			}
		}
	}

	virtual void Reset();
	virtual bool MoveNext();
	CCarIdentifier(void);
};

