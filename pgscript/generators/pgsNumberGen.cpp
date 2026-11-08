//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/generators/pgsNumberGen.h"

pgsNumberGen::pgsNumberGen(const MAPM &range) :
	m_range(range)
{

}

pgsNumberGen::~pgsNumberGen()
{

}
