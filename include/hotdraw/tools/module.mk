#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/hotdraw/tools/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/hotdraw/tools/hdAbstractTool.h \
	include/hotdraw/tools/hdCanvasMenuTool.h \
	include/hotdraw/tools/hdCompositeFigureTool.h \
	include/hotdraw/tools/hdConnectionCreationTool.h \
	include/hotdraw/tools/hdCreationTool.h \
	include/hotdraw/tools/hdDragCreationTool.h \
	include/hotdraw/tools/hdDragTrackerTool.h \
	include/hotdraw/tools/hdFigureTool.h \
	include/hotdraw/tools/hdHandleTrackerTool.h \
	include/hotdraw/tools/hdITool.h \
	include/hotdraw/tools/hdMenuTool.h \
	include/hotdraw/tools/hdPolyLineFigureTool.h \
	include/hotdraw/tools/hdSelectAreaTool.h \
	include/hotdraw/tools/hdSelectionTool.h \
	include/hotdraw/tools/hdSimpleTextTool.h

EXTRA_DIST += \
	include/hotdraw/tools/module.mk
