//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// hdFillAttribute.h - Default attribute for fill color of figure
//
//////////////////////////////////////////////////////////////////////////

#ifndef HDFILLCOLORATTRIBUTE_H
#define HDFILLCOLORATTRIBUTE_H

#include "hotdraw/figures/hdAttribute.h"

class hdFillAttribute : public hdAttribute
{
public:
	hdFillAttribute();
	virtual void callDefaultChangeDialog(wxWindow *owner = NULL);
	virtual void apply(wxBufferedDC &context);
	wxBrush &brush();
protected:
	wxBrush fillAttributes;
};
#endif
