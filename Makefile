TARGET 		= 	Solaris
OBJS 		= 	 main.o\
				gu_functions.o\
 				sdl_functions.o\
				debug.o\
 				file.o\
				framebuffer.o\
				graphics.o\
				callbacks.o\
				font.c

INCDIR 		=
CFLAGS		=	-O2 -G0 -Wall -g -I/usr/local/pspdev/psp/include/SDL
CXXFLAGS 	= 	$(CFLAGS) -fno-exceptions -fno-rtti -g
ASFLAGS 	= 	$(CFLAGS)

LIBDIR 		=
LDFLAGS 	=
LIBS		= 	-lSDL_mixer\
 				-lSDLmain\
 				-lSDL_ttf\
 				-lSDL_image\
 				-lSDL_gfx\
				-lSDL\
				-lc\
				-g\
				-lObjL\
				-lpspgum\
				-lpspgu\
				-lpng\
				-ljpeg\
 				-lz\
				-lstdc++\
				-lm\
				-lpsppower\
				-lpsprtc\
				-lSDL_ttf\
				-lvorbisfile\
				-lvorbis\
				-logg\
				-lfreetype\
				-lpspsdk\
				-lpspctrl\
				-lpsprtc\
				-lpsppower\
				-lpspaudiolib\
				-lpspaudio\
				-lpsphprm\
				-lmad
		
EXTRA_TARGETS 	= EBOOT.PBP
PSP_EBOOT_TITLE = Solaris v1.1
PSP_EBOOT_ICON 	= ICON0.png
PSP_EBOOT_PIC1 	= PIC1.png
PSP_EBOOT_SND0 	= SND0.at3

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

PSPLIBSDIR = $(PSPSDK)/..

font.c : ../src/font.raw
	bin2c font.raw font.c font
	