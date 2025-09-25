EE_OBJS = libpngps2.o upng/upng.o
EE_LIBS = -lpad -lc -lkernel -ldebug -L$(GSKIT)/lib -lgskit -ldmakit -lgskit_toolkit
EE_CFLAGS = -w -I$(GSKIT)/include -I$(PS2SDK)/ports/include
LIB_NAME = libpngps2.a

$(LIB_NAME): $(EE_OBJS)
	ar rcs $(LIB_NAME) $(EE_OBJS)

all: $(LIB_NAME)

clean:
	rm -f $(EE_BIN) $(EE_OBJS) $(LIB_NAME)

install:
	cp $(LIB_NAME) $(PS2SDK)/ports/lib
	cp libpngps2.h $(PS2SDK)/ports/include
	cp -r upng $(PS2SDK)/ports/include

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
