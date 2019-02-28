include ../Rules.make

CFLAGS += -Wall -O2  
LDFLAGS += -lrt -l pthread	

TOPDIR := $(shell pwd)
export TOPDIR

OUT_PATH=./out/$(PLATFORM)

AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)g++
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

TARGET=""
objY=""
obj-y :=
CFLAGS+= -D $(PLATFORM)

export LDFLAGS CFLAGS

LIFO_STACK=LIFOStack


# check the object
ifeq ($(MAKECMDGOALS), $(LIFO_STACK))
TARGET = $(OUT_PATH)/$(LIFO_STACK)
objY  = test$(LIFO_STACK).o

else ifeq ($(MAKECMDGOALS), install*)

else
$(warning "The target <$(MAKECMDGOALS)> is wrong!!!")
1 ::		
endif

obj-y = $(objY)

all : 
$(LIFO_STACK): mk_dir 
	make -C ./ -f $(TOPDIR)/Makefile.build	TARGET=$(TARGET) objY="$(objY)"
	$(CC)  -o $(TARGET) built-in.o $(CFLAGS) $(LDFLAGS) 
	
	make clean
	@echo
	@echo "install...."
	make install PLATFORM=$(PLATFORM)
	
mk_dir:
	mkdir -p $(OUT_PATH)
	
install:
	cp -rf $(OUT_PATH)/* /var/nfsshare/tmp/
install_rootfs:
	cp -rf $(OUT_PATH)/* /home/sl/Engineer/$(PLATFORM)/rootfs/home/BIN/

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	
	#$(shell cd $(LIB_PATH) && rm -f `find -name "*.o"`)
	#$(shell cd $(LIB_PATH) && rm -f `find -name "*.d"`)
	
.PHONY:all clean 
	
