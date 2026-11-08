//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2026, asctime
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////

#include "Postgres/pgDialect.h"

pgDialect::pgDialect()
	: major(0), minor(0)
{
}

void pgDialect::Bind(int major_, int minor_)
{
	major = major_;
	minor = minor_;
}

bool pgDialect::Has(int feature) const
{
	return pgFeatureEnabled(major, minor, feature);
}

wxString pgDialect::Qual(const wxString &qual, const wxString &column)
{
	if (qual.IsEmpty())
		return column;
	return qual + wxT(".") + column;
}

wxString pgDialect::ProcKindColumn(const wxString &qual) const
{
	if (Has(PG_F_PROKIND))
		return Qual(qual, wxT("prokind"));
	return wxT("CASE WHEN ") + Qual(qual, wxT("proisagg"))
	       + wxT(" THEN 'a' WHEN ") + Qual(qual, wxT("proiswindow"))
	       + wxT(" THEN 'w' ELSE 'f' END");
}

wxString pgDialect::ProcKindIs(const wxString &kind, const wxString &qual) const
{
	if (kind.length() != 1)
		return wxT("FALSE");
	if (Has(PG_F_PROKIND))
		return Qual(qual, wxT("prokind")) + wxT(" = '") + kind + wxT("'");
	if (kind == wxT("a"))
		return Qual(qual, wxT("proisagg"));
	if (kind == wxT("w"))
		return Qual(qual, wxT("proiswindow"));
	if (kind == wxT("f"))
		return wxT("(NOT ") + Qual(qual, wxT("proisagg")) + wxT(" AND NOT ")
		       + Qual(qual, wxT("proiswindow")) + wxT(")");
	return wxT("FALSE");
}

wxString pgDialect::ProcKindIsNot(const wxString &kind, const wxString &qual) const
{
	if (kind.length() != 1)
		return wxT("TRUE");
	if (Has(PG_F_PROKIND))
		return Qual(qual, wxT("prokind")) + wxT(" <> '") + kind + wxT("'");
	if (kind == wxT("a"))
		return wxT("(NOT ") + Qual(qual, wxT("proisagg")) + wxT(")");
	if (kind == wxT("w"))
		return wxT("(NOT ") + Qual(qual, wxT("proiswindow")) + wxT(")");
	if (kind == wxT("f"))
		return wxT("(") + Qual(qual, wxT("proisagg")) + wxT(" OR ")
		       + Qual(qual, wxT("proiswindow")) + wxT(")");
	return wxT("TRUE");
}

wxString pgDialect::AttrDefault(const wxString &qual) const
{
	return wxT("pg_get_expr(") + Qual(qual, wxT("adbin")) + wxT(", ")
	       + Qual(qual, wxT("adrelid")) + wxT(")");
}

bool pgDialectSelfCheck()
{
	pgDialect v94;
	v94.Bind(9, 4);
	if (v94.ProcKindColumn(wxT("p")).Find(wxT("proisagg")) == wxNOT_FOUND)
		return false;
	if (v94.ProcKindIs(wxT("p"), wxT("p")) != wxT("FALSE"))
		return false;
	if (v94.ProcKindIsNot(wxT("p")) != wxT("TRUE"))
		return false;
	if (v94.Has(PG_F_PROKIND) || v94.Has(PG_F_RLS) || !v94.Has(PG_F_JSONB))
		return false;

	pgDialect v11;
	v11.Bind(11, 0);
	if (v11.ProcKindColumn(wxT("pr")) != wxT("pr.prokind"))
		return false;
	if (v11.ProcKindIs(wxT("p")) != wxT("prokind = 'p'"))
		return false;
	if (!v11.Has(PG_F_PROCEDURE) || v11.Has(PG_F_NO_ADSRC))
		return false;

	pgDialect v12;
	v12.Bind(12, 0);
	if (!v12.Has(PG_F_NO_ADSRC) || v12.Has(PG_F_NO_PLTEMPLATE))
		return false;
	if (v12.AttrDefault(wxT("d")) != wxT("pg_get_expr(d.adbin, d.adrelid)"))
		return false;

	pgDialect v19;
	v19.Bind(19, 0);
	if (!v19.Has(PG_F_REPACK) || !v19.Has(PG_F_PROKIND) || !v19.Has(PG_F_NO_PLTEMPLATE))
		return false;
	return true;
}
