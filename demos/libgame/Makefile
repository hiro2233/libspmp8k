#
# libgame Makefile
#
#   libgame incorporates the SPMP8k game api as well as some glue
#	for newlib usage
#
#	in order to use newlib configure it with:
#		configure --disable-newlib-supplied-syscalls --target=arm-elf
#	build it and use it in conjunction with this libgame.
#

TOOLCHAIN=arm-elf-

TARGET	= libgame.a

CC		= $(TOOLCHAIN)gcc
AS		= $(TOOLCHAIN)as
AR		= $(TOOLCHAIN)ar
CPP		= $(TOOLCHAIN)cpp
RM		= rm -f

include libgame.cfg

ifdef NEWLIB
CFLAGS	= -O2 -c -I$(NEWLIB)/include -nostdlib -march=armv5 -msoft-float
OBJS	= start.o libgame.o glue.o
else
CFLAGS	= -O2 -c -I$(NEWLIB)/include -nostdlib -march=armv5 -msoft-float
OBJS	= start.o libgame.o
endif
ASFLAGS	= -mcpu=arm9
ARFLAGS	= cr

#malloc.o

all		: $(OBJS)
		$(AR) $(ARFLAGS) $(TARGET) $(OBJS)

%.o		: %.c
		$(CC) $(CFLAGS) $< -o $@

%.o		: %.s
		$(CPP) $< $<.tmp
		$(AS) $(ASFLAGS) $<.tmp -o $@
		$(RM) $<.tmp

clean	:
		$(RM) $(OBJS)
		$(RM) $(TARGET)

