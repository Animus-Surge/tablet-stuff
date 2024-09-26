CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCPATH = /home/surge/Downloads/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin
GCCFLAGS = -Wall -Wextra -ffreestanding -O2

all: clean kernel8.img

boot.o: boot.S
	$(GCCPATH)/aarch64-none-elf-as -c boot.S -o boot.o

%.o: %.c
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	$(GCCPATH)/aarch64-none-elf-gcc -T link.ld -o paddos.elf -ffreestanding -O2 -nostdlib boot.o $(OFILES) -lgcc
	$(GCCPATH)/aarch64-none-elf-objcopy -O binary paddos.elf kernel8.img

clean:
	/bin/rm -rf kernel8.elf *.o *.img > /dev/null 2> /dev/null || true
