ARMGNU = aarch64-none-elf
# アーキテクチャをターゲットとする場合は -march を、プロセッサをターゲットとする場合は -mcpu を指定する必要がある。
A35CPU = -mcpu=cortex-a35 
CFLAGS = -I include -Wall -O2 -nostartfiles -ffreestanding 


vpath %.c   source
vpath %.s   source
vpath %.h   include

all : main.bin

main.o : main.c
	$(ARMGNU)-gcc $(A35CPU) $(CFLAGS) -c $^ -o $@

start.o : start.s
	$(ARMGNU)-as $(A35CPU) -c $^ -o $@

main.elf : main.o start.o
	$(ARMGNU)-ld -nostdlib -T link.lds $^ -o $@

main.bin : main.elf
	$(ARMGNU)-objcopy -O binary $^ $@


.PHONY: mkimg
mkimg : 
	cat resources/header.bin main.bin > bootable_main.img

.PHONY: clean
clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.bin

.PHONY: konmari
konmari :
	rm -f *.o
	rm -f *.elf


.PHONY: dump
dump :
	$(ARMGNU)-objdump -D -m aarch64 main.elf > dump.txt
