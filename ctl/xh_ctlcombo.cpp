//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// xh_ctlcombo.cpp - ctlComboBox handler
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

#include "wx/wx.h"
#include "ctl/ctlComboBox.h"
#include "ctl/xh_ctlcombo.h"

IMPLEMENT_DYNAMIC_CLASS(ctlComboBoxXmlHandler, wxComboBoxXmlHandler)


wxObject *ctlComboBoxXmlHandler::DoCreateResource()
{
	ctlComboBox *ctl = new ctlComboBox(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle());

	SetupWindow(ctl);

	return ctl;
}

bool ctlComboBoxXmlHandler::CanHandle(wxXmlNode *node)
{
	return IsOfClass(node, wxT("ctlComboBox"));
}
