#include "stdafx.h"
#include "CarIdentifier.h"


CCarIdentifier::CCarIdentifier(void)
{
	curPosition = -1;
}

void CCarIdentifier::Identify(CCarInventory ^ list)
{
	counts = list;
}

void CCarIdentifier::Reset()
{
	curPosition = -1;
}

bool CCarIdentifier::MoveNext()
{
	curPosition++;

	if (curPosition < counts->Count)
		return true;
	else
		return false;
}