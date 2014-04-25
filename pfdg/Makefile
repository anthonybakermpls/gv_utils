ifeq ($(OS),Windows_NT)
    exit;
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Solaris)
        CCFLAGS += -D Solaris
    endif
    ifeq ($(UNAME_S),freebsd)
        CCFLAGS += -D freebsd
    endif
endif

