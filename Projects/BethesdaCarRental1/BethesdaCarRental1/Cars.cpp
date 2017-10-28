#include "stdafx.h"
#include "Cars.h"


CCars::CCars()
{
}

void CCars::Locate(CCarInventory ^ list)
{
	items = gcnew CCarInventory();

	for (int i = 0; i < list->Count; i++)
		items->Add(list->Get(i));
}

IEnumerator ^ CCars::GetEnumerator()
{
	CCarIdentifier ^ cid = gcnew CCarIdentifier;

	cid->Identify(items);
	return cid;
}
