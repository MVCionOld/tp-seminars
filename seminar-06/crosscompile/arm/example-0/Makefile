BIN_PATH       = /home/mvcion/arm/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/bin
QEMU_LD_PREFIX = /home/mvcion/arm/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/arm-linux-gnueabi/libc
TOOLCHAIN      = arm-linux-gnueabi
QEMU           = qemu-arm
CC             = g++
GDB            = $(BIN_PATH)/$(TOOLCHAIN)-gdb
FLAGS          = -Wextra -std=c++11
DEV_FLAGS      = $(FLAGS) -g
COMPILER       = $(BIN_PATH)/$(TOOLCHAIN)-$(CC)


.PHONY: all clean


all: run

clean:
	rm -rf *.out

main.out:
	$(COMPILER) $(FLAGS) -o main.out main.cpp

run: main.out
	$(QEMU) -L $(QEMU_LD_PREFIX) ./main.out

main.dev.out:
	$(COMPILER) $(DEV_FLAGS) main.cpp -o main.dev.out

debug: main.dev.out
	$(GDB) ./main.dev.out