#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/pgscript/exceptions/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	pgscript/exceptions/pgsArithmeticException.cpp \
	pgscript/exceptions/pgsAssertException.cpp \
	pgscript/exceptions/pgsBreakException.cpp \
	pgscript/exceptions/pgsCastException.cpp \
	pgscript/exceptions/pgsContinueException.cpp \
	pgscript/exceptions/pgsException.cpp \
	pgscript/exceptions/pgsInterruptException.cpp \
	pgscript/exceptions/pgsParameterException.cpp

EXTRA_DIST += \
	pgscript/exceptions/module.mk

