CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCPATH = aarch64-linux-gnu
GCCFLAGS = -Wall -Wextra -ffreestanding -O2



all: clean kernel8.img

boot.o: boot.S
	$(GCCPATH)-as -c boot.S -o boot.o

%.o: %.c
	$(GCCPATH)-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	$(GCCPATH)-gcc -T link.ld -o paddos.elf -ffreestanding -O2 -nostdlib boot.o $(OFILES) -lgcc
	$(GCCPATH)-objcopy -O binary paddos.elf kernel8.img

clean:
	/bin/rm -rf kernel8.elf *.o *.img > /dev/null 2> /dev/null || true
