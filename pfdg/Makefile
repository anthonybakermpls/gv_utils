

CC = cc

CCDBGFLAGS = -g -Weverything
LIBS =
OBJS = rd.o

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CCFLAGS += -D LINUX
    LIBS += -ldl
endif
ifeq ($(UNAME_S),Darwin)
    CCFLAGS += -D OSX
endif
ifeq ($(UNAME_S),FreeBSD)
    CCFLAGS += -D FREEBSD
endif
ifeq ($(UNAME_S),solaris)
    CCFLAGS += -D solaris
endif

UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
    CCFLAGS += -D AMD64
endif
ifneq ($(filter %86,$(UNAME_P)),)
    CCFLAGS += -D IA32
endif
ifneq ($(filter arm%,$(UNAME_P)),)
    CCFLAGS += -D ARM
endif







all: rd

rd: $(OBJS)
$(CC) $(CCFLAGS) $(CCDBGFLAGS) $(LIBS) $(OBJS) rd.c -o rd



clean:
rm -rf *o rd
