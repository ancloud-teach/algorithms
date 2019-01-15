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

HEAP=Heap
HEAPMIN=HeapMin
MAX_PORITIY_QUEUE=MaxPorityQueue
MIN_PORITIY_QUEUE=MinPorityQueue


# check the object
ifeq ($(MAKECMDGOALS), $(HEAP))
TARGET = $(OUT_PATH)/$(HEAP)	
objY  = BUILD-MAX-HEAPIFY.o
objY += MAX-HEAPIFY.o
objY += HEAPSORT.o
objY  += test$(HEAP).o	

# check the object
else ifeq ($(MAKECMDGOALS), $(HEAPMIN))
TARGET = $(OUT_PATH)/$(HEAPMIN)	
objY  = MIN-PROITIY-QUEUE.o
objY  += test$(HEAPMIN).o	

else ifeq ($(MAKECMDGOALS), $(MAX_PORITIY_QUEUE))
TARGET = $(OUT_PATH)/$(MAX_PORITIY_QUEUE)
objY  = BUILD-MAX-HEAPIFY.o
objY += MAX-HEAPIFY.o
objY += HEAPSORT.o
objY  += MAX-PROITIY-QUEUE.o	
objY  += test$(MAX_PORITIY_QUEUE).o	

else ifeq ($(MAKECMDGOALS), $(MIN_PORITIY_QUEUE))
TARGET = $(OUT_PATH)/$(MIN_PORITIY_QUEUE)
objY  = MIN-PROITIY-QUEUE.o	
objY  += test$(MIN_PORITIY_QUEUE).o	

else ifeq ($(MAKECMDGOALS), install*)

else
$(warning "The target <$(MAKECMDGOALS)> is wrong!!!")
1 ::		
endif

obj-y = $(objY)

all : 
$(HEAP): mk_dir 
	make -C ./ -f $(TOPDIR)/Makefile.build	TARGET=$(TARGET) objY="$(objY)"
	$(CC)  -o $(TARGET) built-in.o $(CFLAGS) $(LDFLAGS) 
	
	make clean
	@echo
	@echo "install...."
	make install PLATFORM=$(PLATFORM)
	
$(HEAPMIN): mk_dir 
	make -C ./ -f $(TOPDIR)/Makefile.build	TARGET=$(TARGET) objY="$(objY)"
	$(CC)  -o $(TARGET) built-in.o $(CFLAGS) $(LDFLAGS) 
	
	make clean
	@echo
	@echo "install...."
	make install PLATFORM=$(PLATFORM)	
	
$(MAX_PORITIY_QUEUE): mk_dir 
	make -C ./ -f $(TOPDIR)/Makefile.build	TARGET=$(TARGET) objY="$(objY)"
	$(CC)  -o $(TARGET) built-in.o $(CFLAGS) $(LDFLAGS) 
	
	make clean
	@echo
	@echo "install...."
	make install PLATFORM=$(PLATFORM)
	
$(MIN_PORITIY_QUEUE): mk_dir 
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
	
