#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/hotdraw/figures/defaultAttributes Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	include/hotdraw/figures/defaultAttributes/hdFillAttribute.h \
	include/hotdraw/figures/defaultAttributes/hdFontAttribute.h \
	include/hotdraw/figures/defaultAttributes/hdFontColorAttribute.h \
	include/hotdraw/figures/defaultAttributes/hdLineAttribute.h

EXTRA_DIST += \
	include/hotdraw/figures/defaultAttributes/module.mk
