#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/slony/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	slony/dlgRepCluster.cpp \
	slony/dlgRepListen.cpp \
	slony/dlgRepNode.cpp \
	slony/dlgRepPath.cpp \
	slony/dlgRepProperty.cpp \
	slony/dlgRepSequence.cpp \
	slony/dlgRepSet.cpp \
	slony/dlgRepSubscription.cpp \
	slony/dlgRepTable.cpp \
	slony/slCluster.cpp \
	slony/slListen.cpp \
	slony/slNode.cpp \
	slony/slPath.cpp \
	slony/slSequence.cpp \
	slony/slSet.cpp \
	slony/slSubscription.cpp \
	slony/slTable.cpp

EXTRA_DIST += \
        slony/module.mk


