#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/pgscript/objects/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	pgscript/objects/pgsGenerator.cpp \
	pgscript/objects/pgsNumber.cpp \
	pgscript/objects/pgsRecord.cpp \
	pgscript/objects/pgsString.cpp \
	pgscript/objects/pgsVariable.cpp

EXTRA_DIST += \
	pgscript/objects/module.mk

