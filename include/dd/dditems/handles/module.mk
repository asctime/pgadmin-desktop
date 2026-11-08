#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/dditems/handles/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/dd/dditems/handles/ddAddColButtonHandle.h \
	include/dd/dditems/handles/ddAddFkButtonHandle.h \
	include/dd/dditems/handles/ddMinMaxTableButtonHandle.h \
	include/dd/dditems/handles/ddRemoveTableButtonHandle.h \
	include/dd/dditems/handles/ddScrollBarHandle.h \
	include/dd/dditems/handles/ddSouthTableSizeHandle.h

EXTRA_DIST += \
	include/dd/dditems/handles/module.mk
