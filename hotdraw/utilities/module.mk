#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/hotdraw/utilities/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	hotdraw/utilities/hdArrayCollection.cpp \
	hotdraw/utilities/hdCollection.cpp \
	hotdraw/utilities/hdGeometry.cpp \
	hotdraw/utilities/hdKeyEvent.cpp \
	hotdraw/utilities/hdMouseEvent.cpp \
	hotdraw/utilities/hdMultiPosRect.cpp \
	hotdraw/utilities/hdPoint.cpp \
	hotdraw/utilities/hdRect.cpp \
	hotdraw/utilities/hdRemoveDeleteDialog.cpp

EXTRA_DIST += \
	hotdraw/utilities/module.mk
