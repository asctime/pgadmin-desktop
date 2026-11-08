#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/db/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	  include/db/pgConn.h \
	  include/db/pgQueryThread.h \
	  include/db/pgQueryResultEvent.h \
	  include/db/pgSet.h

EXTRA_DIST += \
    include/db/module.mk

