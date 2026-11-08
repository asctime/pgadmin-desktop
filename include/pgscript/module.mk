#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/pgscript/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/pgscript/location.hh \
	include/pgscript/parser.tab.hh \
	include/pgscript/position.hh \
	include/pgscript/stack.hh \
	include/pgscript/FlexLexer.h \
	include/pgscript/pgsApplication.h \
	include/pgscript/pgScript.h

EXTRA_DIST += \
	include/pgscript/module.mk

include include/pgscript/exceptions/module.mk
include include/pgscript/expressions/module.mk
include include/pgscript/generators/module.mk
include include/pgscript/objects/module.mk
include include/pgscript/statements/module.mk
include include/pgscript/utilities/module.mk
