PLATFORM_PC=PC
PLATFORM_GT6502=GT6502
PLATFORM_NanoPi=NanoPi
PLATFORM_GT6657=GT6657
PLATFORM_Widora=Widora
CROSS_PATH=
# check the platform
ifeq ($(PLATFORM), $(PLATFORM_PC))
CROSS_COMPILE = 

else ifeq ($(PLATFORM), $(PLATFORM_GT6502))
CROSS_COMPILE = arm-linux-

else ifeq ($(PLATFORM), $(PLATFORM_NanoPi))
#CROSS_PATH=/home/sl/tools/arm-linux-gcc/usr/local/arm/4.5.1/bin/
CROSS_COMPILE = arm-linux-

else ifeq ($(PLATFORM), $(PLATFORM_GT6657))
CROSS_COMPILE = arm-linux-gnueabihf-

else ifeq ($(PLATFORM), $(PLATFORM_Widora))
CROSS_COMPILE =  mipsel-openwrt-linux-

else
$(warning "the wrong platform !!!!!!!!!!!!!!!!!!!")
$(warning "you should make <PLATFORM> <target>")
$(warning "<PLATFORM>	$(PLATFORM_GT6502) ")
$(warning "<PLATFORM>	$(PLATFORM_PC)")
$(warning "<PLATFORM>	$(PLATFORM_NanoPi) ")
$(warning "<PLATFORM>	$(PLATFORM_GT6657)")
$(warning "<PLATFORM>	$(PLATFORM_Widora)")

1 ::	
endif

CFLAGS := -Wall -O2  
CFLAGS += -D $(PLATFORM) -ldl
CFLAGS += -I /mnt/hgfs/ShareHolder/code/

ifeq ($(PLATFORM), $(PLATFORM_Widora))
CFLAGS+= -ldl 
endif

LDFLAGS := -lrt -lpthread
export CFLAGS LDFLAGS	