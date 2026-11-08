#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/db/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	db/keywords.c \
	db/pgConn.cpp \
	db/pgSet.cpp \
	db/pgQueryThread.cpp

EXTRA_DIST += \
        db/module.mk

