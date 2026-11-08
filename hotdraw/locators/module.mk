#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/hotdraw/locator/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	hotdraw/locators/hdILocator.cpp \
	hotdraw/locators/hdPolyLineLocator.cpp

EXTRA_DIST += \
	hotdraw/locators/module.mk
