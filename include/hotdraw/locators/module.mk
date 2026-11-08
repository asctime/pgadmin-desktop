#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/hotdraw/locator/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/hotdraw/locators/hdILocator.h \
	include/hotdraw/locators/hdPolyLineLocator.h

EXTRA_DIST += \
	include/hotdraw/locators/module.mk
