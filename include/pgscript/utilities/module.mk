#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/pgscript/utilities/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/pgscript/utilities/pgsAlloc.h \
	include/pgscript/utilities/pgsContext.h \
	include/pgscript/utilities/pgsCopiedPtr.h \
	include/pgscript/utilities/pgsDriver.h \
	include/pgscript/utilities/pgsMapm.h \
	include/pgscript/utilities/pgsScanner.h \
	include/pgscript/utilities/pgsSharedPtr.h \
	include/pgscript/utilities/pgsThread.h \
	include/pgscript/utilities/pgsUtilities.h

EXTRA_DIST += \
	include/pgscript/utilities/module.mk

include include/pgscript/utilities/mapm-lib/module.mk
