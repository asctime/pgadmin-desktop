//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// ddAddColLocator.h - Locate table add column button inside a table.
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDADDCOLLOCATOR_H
#define DDADDCOLLOCATOR_H

#include "hotdraw/locators/hdILocator.h"
#include "hotdraw/figures/hdIFigure.h"

class ddAddColLocator : public hdILocator
{
public:
	ddAddColLocator();
	~ddAddColLocator();

	virtual hdPoint &locate(int posIdx, hdIFigure *owner);

protected:

private:
};
#endif
