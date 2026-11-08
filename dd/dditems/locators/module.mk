#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/dditems/locators/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	dd/dditems/locators/ddAddColLocator.cpp \
	dd/dditems/locators/ddAddFkLocator.cpp \
	dd/dditems/locators/ddMinMaxTableLocator.cpp \
	dd/dditems/locators/ddRemoveTableLocator.cpp \
	dd/dditems/locators/ddScrollBarTableLocator.cpp \
	dd/dditems/locators/ddTableBottomLocator.cpp

EXTRA_DIST += \
	dd/dditems/locators/module.mk
