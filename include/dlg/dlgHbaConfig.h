//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// dlgHbaConfig.h - Configure setting
//
//////////////////////////////////////////////////////////////////////////

#ifndef __DLGHBACONFIG_H
#define __DLGHBACONFIG_H

#include "dlg/dlgClasses.h"
#include "utils/pgconfig.h"

// Class declarations
class dlgHbaConfig : public DialogWithHelp
{
public:
	dlgHbaConfig(pgFrame *parent, pgHbaConfigLine *line, pgConn *_conn);
	~dlgHbaConfig();
	wxString GetHelpPage() const;

	int Go();

private:
	pgHbaConfigLine *line;

	void OnOK(wxCommandEvent &ev);
	void OnCancel(wxCommandEvent &ev);
	void OnChange(wxCommandEvent &ev);
	void OnAddDatabase(wxCommandEvent &ev);
	void OnAddUser(wxCommandEvent &ev);
	void OnAddValue(wxCommandEvent &ev);

	wxString database, user;

	bool databaseAdding, userAdding;

	pgConn *conn;

	DECLARE_EVENT_TABLE()
};

#endif
