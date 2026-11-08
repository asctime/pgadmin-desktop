#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/hotdraw/main/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	hotdraw/main/hdDrawing.cpp \
	hotdraw/main/hdDrawingEditor.cpp \
	hotdraw/main/hdDrawingView.cpp

EXTRA_DIST += \
	hotdraw/main/module.mk
