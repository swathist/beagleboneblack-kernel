obj-m := hello.o

modules:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C `pwd`/../.. M=`pwd` modules

install:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C `pwd`/../.. M=`pwd` modules_install

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C `pwd`/../.. M=`pwd` clean

dtbs:
	dtc -@ -I dts -O dtb -o sample_device_tree.dtb sample_device_tree.dts
