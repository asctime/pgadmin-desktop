//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// Events.h - IDs for GQB Events
//
//////////////////////////////////////////////////////////////////////////

#ifndef GQBEVENTS_H
#define GQBEVENTS_H

enum gqb_Events
{
	GQB_COLSTREE = 1000,
	GQB_BROWSER,
	GQB_HORZ_SASH
};

enum gqb_rMenus
{
	GQB_RMJ_DELETE = 2000,
	GQB_RMJ_SETTYPE,
	GQB_RMT_DELETE,
	GQB_RMT_SETALIAS,
	GQB_REFRESH
};
#endif
