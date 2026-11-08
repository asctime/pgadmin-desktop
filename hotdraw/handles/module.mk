#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/hotdraw/handles/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	hotdraw/handles/hdButtonHandle.cpp \
	hotdraw/handles/hdChangeConnectionEndHandle.cpp \
	hotdraw/handles/hdChangeConnectionHandle.cpp \
	hotdraw/handles/hdChangeConnectionStartHandle.cpp \
	hotdraw/handles/hdIHandle.cpp \
	hotdraw/handles/hdLineConnectionHandle.cpp \
	hotdraw/handles/hdLocatorHandle.cpp \
	hotdraw/handles/hdPolyLineHandle.cpp

EXTRA_DIST += \
	hotdraw/handles/module.mk
