#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dd/ddmodel/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	dd/ddmodel/ddDatabaseDesign.cpp \
	dd/ddmodel/ddDrawingEditor.cpp \
	dd/ddmodel/ddDBReverseEnginering.cpp \
	dd/ddmodel/ddModelBrowser.cpp \
	dd/ddmodel/ddGenerationWizard.cpp \
	dd/ddmodel/ddDrawingView.cpp \
	dd/ddmodel/ddBrowserDataContainer.cpp

EXTRA_DIST += \
	dd/ddmodel/module.mk
