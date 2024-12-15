ifneq ($(KERNELRELEASE),)
	obj-m := hello1.o hello2.o
	ccflags-y := -I$(PWD)/inc
else
	KDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
	KCFLAGS += -Wno-error



default:
	$(MAKE) -C $(KDIR) M=$(PWD) KCFLAGS="$(KCFLAGS)" modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif

	
