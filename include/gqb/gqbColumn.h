//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// gqbColumn.h - Column Object for GQB
//
//////////////////////////////////////////////////////////////////////////

#ifndef GQBCOLUMN_H
#define GQBCOLUMN_H

// App headers
#include "gqb/gqbObject.h"
#include "gqb/gqbTable.h"

// Create Array Objects used as base for gqbCollections
class gqbColumn : public gqbObject
{
public:
	gqbColumn(gqbObject *parent, wxString name, pgConn *connection);
};
#endif
