APPNAME	= raw_uyvy_player
DESTDIR	= ../bin
SRCDIR		= ../src

DEL_FILE	= rm -rf
CP_FILE	= cp -rf    

ROOTFS_DIR = $(SDKTARGETSYSROOT)

TARGET_PATH_LIB 	= $(ROOTFS_DIR)/usr/lib
TARGET_PATH_INCLUDE 	= $(ROOTFS_DIR)/usr/include

CFLAGS			= -DLINUX -Wall -O2 -fsigned-char -march=armv8-a -mtune=cortex-a34  \
			  -I. -I$(TARGET_PATH_INCLUDE) \
                          -I$(TARGET_PATH_INCLUDE)/glib-2.0 -I$(TARGET_PATH_LIB)/glib-2.0/include \
                          -I$(TARGET_PATH_INCLUDE)/libxml2  -I$(TARGET_PATH_INCLUDE)/gstreamer-1.0 \

LFLAGS			= -Wl,--library-path=$(TARGET_PATH_LIB),-rpath-link=$(TARGET_PATH_LIB) -lm -lstdc++ \
			  -lpthread -lgstreamer-1.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lglib-2.0 



OBJECTS			= $(APPNAME).o gstcontrol.o

first: all

all: $(APPNAME)

$(APPNAME): $(OBJECTS) 
	$(CXX) $(LFLAGS) -o $(DESTDIR)/$(APPNAME) $(OBJECTS)  

$(APPNAME).o: $(APPNAME).cpp
	$(CXX) $(CFLAGS) -c -o $(APPNAME).o $(APPNAME).cpp

gstcontrol.o: gstcontrol.cpp
	$(CXX) $(CFLAGS) -c -o gstcontrol.o gstcontrol.cpp

clean:
	$(DEL_FILE) $(SRCDIR)/$(OBJECTS)
	$(DEL_FILE) $(DESTDIR)/$(OBJECTS)
	$(DEL_FILE) $(DESTDIR)/*~ $(DESTDIR)/*.core
	$(DEL_FILE) $(DESTDIR)/$(APPNAME)
	
distclean: clean
	$(DEL_FILE) $(DESTDIR)/$(APPNAME)

install: all
	#${CP_FILE} $(SRCDIR)/$(APPNAME) $(DESTDIR)/$(APPNAME)
	#${CP_FILE} $(DESTDIR)/$(APPNAME) $(ROOTFS_DIR)/home/opencv

