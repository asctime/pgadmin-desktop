//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSCONTINUEEXCEPTION_H_
#define PGSCONTINUEEXCEPTION_H_

#include "pgscript/pgScript.h"
#include "pgscript/exceptions/pgsException.h"

class pgsContinueException : public pgsException
{

public:

	pgsContinueException();

	virtual ~pgsContinueException();

	virtual const wxString message() const;

};

#endif /*PGSCONTINUEEXCEPTION_H_*/
