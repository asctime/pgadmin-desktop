//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// hdDragCreationTool.h - A Tool that allow to move figure around view
//
//////////////////////////////////////////////////////////////////////////

#ifndef HDDRAGCREATIONTOOL_H
#define HDDRAGCREATIONTOOL_H

#include "hotdraw/tools/hdCreationTool.h"
#include "hotdraw/main/hdDrawingEditor.h"


class hdDragCreationTool : public hdCreationTool
{
public:
	hdDragCreationTool(hdDrawingView *view, hdIFigure *prototype);
	~hdDragCreationTool();
	virtual void mouseDrag(hdMouseEvent &event);
};
#endif
