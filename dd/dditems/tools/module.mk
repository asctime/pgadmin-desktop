#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/dditems/tools/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	dd/dditems/tools/ddColumnFigureTool.cpp \
	dd/dditems/tools/ddColumnTextTool.cpp

EXTRA_DIST += \
	dd/dditems/tools/module.mk
