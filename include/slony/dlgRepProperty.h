//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// dlgRepSet.h - Slony-I property
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_REPPROP
#define __DLG_REPPROP

#include "dlg/dlgProperty.h"

class slCluster;

class dlgRepProperty : public dlgProperty
{
public:
	dlgRepProperty(pgaFactory *f, frmMain *frame, slCluster *c, const wxString &resName);

protected:
	slCluster *cluster;
};


#endif
