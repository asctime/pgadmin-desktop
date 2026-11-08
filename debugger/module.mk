#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/debugger/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	debugger/ctlMessageWindow.cpp \
	debugger/ctlResultGrid.cpp \
	debugger/ctlStackWindow.cpp \
	debugger/ctlTabWindow.cpp \
	debugger/ctlVarWindow.cpp \
	debugger/dbgBreakPoint.cpp \
	debugger/dbgController.cpp \
	debugger/dbgEvents.cpp \
	debugger/dbgModel.cpp \
 	debugger/dbgTargetInfo.cpp \
	debugger/debugger.cpp \
	debugger/dlgDirectDbg.cpp \
	debugger/frmDebugger.cpp

EXTRA_DIST += \
	debugger/module.mk


