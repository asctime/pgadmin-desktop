#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/hotdraw/connectors/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/hotdraw/connectors/hdChopBoxConnector.h \
	include/hotdraw/connectors/hdIConnector.h \
	include/hotdraw/connectors/hdLocatorConnector.h \
	include/hotdraw/connectors/hdStickyRectangleConnector.h

EXTRA_DIST += \
	include/hotdraw/connectors/module.mk
