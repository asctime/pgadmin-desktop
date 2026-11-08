#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dd/dditems/locators/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/dd/dditems/locators/ddAddColLocator.h \
	include/dd/dditems/locators/ddAddFkLocator.h \
	include/dd/dditems/locators/ddMinMaxTableLocator.h \
	include/dd/dditems/locators/ddRemoveTableLocator.h \
	include/dd/dditems/locators/ddScrollBarTableLocator.h \
	include/dd/dditems/locators/ddTableBottomLocator.h

EXTRA_DIST += \
	include/dd/dditems/locators/module.mk
