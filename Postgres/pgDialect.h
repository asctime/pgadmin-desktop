//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2026, asctime
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// One catalogue dialect per connection. Call sites ask for a phrase.
// They do not spell prokind, proisagg, adsrc, or a version number.
//
//////////////////////////////////////////////////////////////////////////

#ifndef PGDIALECT_H
#define PGDIALECT_H

#include <wx/string.h>
#include "Postgres/pgDiscipline.h"

class pgDialect
{
public:
	pgDialect();

	void Bind(int major, int minor);
	int Major() const
	{
		return major;
	}
	int Minor() const
	{
		return minor;
	}

	bool Has(int feature) const;

	// Expression of type "char". Alias it yourself when it is a select item.
	wxString ProcKindColumn(const wxString &qual = wxEmptyString) const;
	// Boolean SQL: the row's kind is this letter (a, f, p, w).
	wxString ProcKindIs(const wxString &kind, const wxString &qual = wxEmptyString) const;
	wxString ProcKindIsNot(const wxString &kind, const wxString &qual = wxEmptyString) const;

	// pg_get_expr(adbin, adrelid). qual is the pg_attrdef alias, or empty.
	wxString AttrDefault(const wxString &qual = wxEmptyString) const;

private:
	int major;
	int minor;
	static wxString Qual(const wxString &qual, const wxString &column);
};

bool pgDialectSelfCheck();

#endif
