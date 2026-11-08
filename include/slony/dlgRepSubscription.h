//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// dlgRepSubscription.h - Slony-I Subscription property
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_REPSUBSCPROP
#define __DLG_REPSUBSCPROP

#include "slony/dlgRepProperty.h"

class slSubscription;
class slSet;

class dlgRepSubscription : public dlgRepProperty
{
public:
	dlgRepSubscription(pgaFactory *factory, frmMain *frame, slSubscription *sub, slSet *s);
	int Go(bool modal);
	wxString GetHelpPage() const
	{
		return wxT("slony-set#subscription");
	}

	void CheckChange();
	wxString GetSql();
	pgObject *CreateObject(pgCollection *collection);
	pgObject *GetObject();

private:
	slSubscription *subscription;
	slSet *set;

	DECLARE_EVENT_TABLE()
};


#endif
