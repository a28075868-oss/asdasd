AS = nasm
CC = gcc
LD = ld

CFLAGS = -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

KERNEL_ASM_OBJ = multiboot.o gdt.o interrupt.o
KERNEL_C_OBJ = kernel.o screen.o string.o idt.o gdt_c.o keyboard.o timer.o memory.o process.o syscall.o shell.o

all: entrada.iso

%.o: %.asm
	$(AS) -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

gdt_c.o: gdt.c
	$(CC) $(CFLAGS) -c gdt.c -o gdt_c.o

kernel.bin: $(KERNEL_ASM_OBJ) $(KERNEL_C_OBJ)
	$(LD) $(LDFLAGS) -o kernel.bin $(KERNEL_ASM_OBJ) $(KERNEL_C_OBJ)

entrada.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o entrada.iso isodir

clean:
	rm -rf *.o kernel.bin isodir entrada.iso

run: entrada.iso
	qemu-system-i386 -cdrom entrada.iso

.PHONY: all clean run
