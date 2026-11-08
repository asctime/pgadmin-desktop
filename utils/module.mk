#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/utils/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	utils/csvfiles.cpp \
	utils/factory.cpp \
	utils/favourites.cpp \
	utils/misc.cpp \
	utils/pgconfig.cpp \
	utils/registry.cpp \
	utils/sysLogger.cpp \
	utils/sysProcess.cpp \
	utils/sysSettings.cpp \
	utils/tabcomplete.c \
	utils/utffile.cpp \
	utils/macros.cpp

if BUILD_SSH_TUNNEL
pgadmin_desktop_SOURCES += \
	utils/sshTunnel.cpp
endif

EXTRA_DIST += \
	utils/module.mk \
	utils/tab-complete.inc \
	utils/tabcomplete.pl
