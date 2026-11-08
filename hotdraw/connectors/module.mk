#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/hotdraw/connectors/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	hotdraw/connectors/hdChopBoxConnector.cpp \
	hotdraw/connectors/hdIConnector.cpp \
	hotdraw/connectors/hdLocatorConnector.cpp \
	hotdraw/connectors/hdStickyRectangleConnector.cpp

EXTRA_DIST += \
	hotdraw/connectors/module.mk
