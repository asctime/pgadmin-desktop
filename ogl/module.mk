#######################################################################
#
# 
# Copyright (C) 2002 - 2016, The pgAdmin Development Team
# Copyright (C) 2027, asctime
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/ogl/ Makefile fragment
#
#######################################################################

pgadmin_desktop_SOURCES += \
	ogl/basic.cpp \
	ogl/bmpshape.cpp \
	ogl/composit.cpp \
	ogl/divided.cpp \
	ogl/lines.cpp \
	ogl/oglmisc.cpp \
	ogl/basic2.cpp \
	ogl/canvas.cpp \
	ogl/constrnt.cpp \
	ogl/drawn.cpp \
	ogl/mfutils.cpp \
	ogl/ogldiag.cpp

EXTRA_DIST += \
	ogl/module.mk \
	ogl/README


