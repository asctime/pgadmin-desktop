#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/hotdraw/main/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/hotdraw/main/hdDrawing.h \
	include/hotdraw/main/hdDrawingEditor.h \
	include/hotdraw/main/hdDrawingView.h \
	include/hotdraw/main/hdObject.h

EXTRA_DIST += \
	include/hotdraw/main/module.mk
