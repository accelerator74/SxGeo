# Makefile
HX_SOURCEMOD = ../sourcemod
#
# sxgeo.ext.so
#
HX_INCLUDE = -I. \
	-I$(HX_SOURCEMOD)/public \
	-I$(HX_SOURCEMOD)/public/amtl \
	-I$(HX_SOURCEMOD)/public/amtl/amtl \
	-I$(HX_SOURCEMOD)/sourcepawn/include
#
HX_QWERTY = -D_LINUX \
	-Dstricmp=strcasecmp \
	-D_stricmp=strcasecmp \
	-D_strnicmp=strncasecmp \
	-Dstrnicmp=strncasecmp \
	-D_snprintf=snprintf \
	-D_vsnprintf=vsnprintf \
	-D_alloca=alloca \
	-Dstrcmpi=strcasecmp \
	-Wall \
	-Werror \
	-Wno-switch \
	-Wno-unused \
	-Wno-reorder \
	-msse \
	-DSOURCEMOD_BUILD \
	-DHAVE_STDINT_H \
	-m32 \
	-DNDEBUG \
	-O3 \
	-funroll-loops \
	-pipe \
	-fno-strict-aliasing \
	-fvisibility=hidden \
	-DCOMPILER_GCC \
	-mfpmath=sse

CPP_FLAGS = -Wno-non-virtual-dtor \
	-fvisibility-inlines-hidden \
	-fno-exceptions \
	-fno-rtti \
	-std=c++11
#
HX_SO = Release/smsdk_ext.o \
	Release/extension.o \
	Release/db.o \
	Release/location.o \
	Release/sxgeo.o
#
all:
	mkdir -p Release
	ln -sf $(HX_SOURCEMOD)/public/smsdk_ext.cpp
#
	gcc $(HX_INCLUDE) $(HX_QWERTY) $(CPP_FLAGS) -o Release/smsdk_ext.o -c smsdk_ext.cpp
	gcc $(HX_INCLUDE) $(HX_QWERTY) $(CPP_FLAGS) -o Release/db.o -c sxgeo/db.cpp
	gcc $(HX_INCLUDE) $(HX_QWERTY) $(CPP_FLAGS) -o Release/location.o -c sxgeo/location.cpp
	gcc $(HX_INCLUDE) $(HX_QWERTY) $(CPP_FLAGS) -o Release/sxgeo.o -c sxgeo.cpp
	gcc $(HX_INCLUDE) $(HX_QWERTY) $(CPP_FLAGS) -o Release/extension.o -c extension.cpp
#
	gcc $(HX_SO) -static-libgcc -shared -m32 -lm -ldl -o Release/sxgeo.ext.so
#
	rm -rf Release/*.o
