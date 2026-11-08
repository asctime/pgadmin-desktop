#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/agent/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
    agent/dlgJob.cpp \
	  agent/dlgSchedule.cpp \
	  agent/dlgStep.cpp \
	  agent/pgaJob.cpp \
	  agent/pgaSchedule.cpp \
	  agent/pgaStep.cpp

EXTRA_DIST += \
    agent/module.mk


