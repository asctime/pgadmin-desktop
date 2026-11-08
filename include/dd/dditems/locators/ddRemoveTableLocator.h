//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// ddRemoveColLocator.cpp - Locate table delete button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDREMOVETABLELOCATOR_H
#define DDREMOVETABLELOCATOR_H

#include "hotdraw/locators/hdILocator.h"
#include "hotdraw/figures/hdIFigure.h"

class ddRemoveTableLocator : public hdILocator
{
public:
	ddRemoveTableLocator();
	~ddRemoveTableLocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner);

protected:

private:
};
#endif
