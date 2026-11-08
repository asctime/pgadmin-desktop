#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/hotdraw/handles/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/hotdraw/handles/hdButtonHandle.h \
	include/hotdraw/handles/hdChangeConnectionEndHandle.h \
	include/hotdraw/handles/hdChangeConnectionHandle.h \
	include/hotdraw/handles/hdChangeConnectionStartHandle.h \
	include/hotdraw/handles/hdIHandle.h \
	include/hotdraw/handles/hdLineConnectionHandle.h \
	include/hotdraw/handles/hdLocatorHandle.h \
	include/hotdraw/handles/hdPolyLineHandle.h

EXTRA_DIST += \
	include/hotdraw/handles/module.mk
