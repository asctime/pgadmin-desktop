//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// hdRectangleFigure.cpp - A simple rectangle  figure
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "hotdraw/figures/hdRectangleFigure.h"
#include "hotdraw/main/hdDrawingView.h"

hdRectangleFigure::hdRectangleFigure()
{
}

hdRectangleFigure::~hdRectangleFigure()
{
}

void hdRectangleFigure::basicDraw(wxBufferedDC &context, hdDrawingView *view)
{
	hdRect copy = displayBox().gethdRect(view->getIdx());
	view->CalcScrolledPosition(copy.x, copy.y, &copy.x, &copy.y);
	context.DrawRectangle(copy);
}

void hdRectangleFigure::basicDrawSelected(wxBufferedDC &context, hdDrawingView *view)
{
	hdRect copy = displayBox().gethdRect(view->getIdx());
	view->CalcScrolledPosition(copy.x, copy.y, &copy.x, &copy.y);
	context.DrawRectangle(copy);
}

void hdRectangleFigure::setRectangle(hdMultiPosRect &rect)
{
	basicDisplayBox = rect;
}

void hdRectangleFigure::setSize(wxSize &size)
{
	basicDisplayBox.SetSize(size);
}
