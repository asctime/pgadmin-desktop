#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/pgscript/exceptions/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/pgscript/exceptions/pgsArithmeticException.h \
	include/pgscript/exceptions/pgsAssertException.h \
	include/pgscript/exceptions/pgsBreakException.h \
	include/pgscript/exceptions/pgsCastException.h \
	include/pgscript/exceptions/pgsContinueException.h \
	include/pgscript/exceptions/pgsException.h \
	include/pgscript/exceptions/pgsInterruptException.h \
	include/pgscript/exceptions/pgsParameterException.h

EXTRA_DIST += \
	include/pgscript/exceptions/module.mk

