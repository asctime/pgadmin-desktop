//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// hdFontAttribute.cpp - Default attribute for color of fonts
//
//////////////////////////////////////////////////////////////////////////

#ifndef HDFONTCOLORATTRIBUTE_H
#define HDFONTCOLORATTRIBUTE_H

#include "hotdraw/figures/hdAttribute.h"

class hdFontColorAttribute : public hdAttribute
{
public:
	hdFontColorAttribute();
	virtual void callDefaultChangeDialog(wxWindow *owner = NULL);
	virtual void apply(wxBufferedDC &context);
//	void setFontColorAttribute(wxColour color);
	wxColour fontColor;
protected:


};
#endif
