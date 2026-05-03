#!/bin/bash

echo "=== Entrada OS Build System ==="
echo

# Compile assembly files
echo "[1/4] Compiling assembly files..."
nasm -f elf32 multiboot.asm -o multiboot.o
nasm -f elf32 gdt.asm -o gdt.o
nasm -f elf32 interrupt.asm -o interrupt.o

# Compile C files
echo "[2/4] Compiling C files..."
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c screen.c -o screen.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c string.c -o string.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c idt.c -o idt.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c gdt.c -o gdt_c.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c timer.c -o timer.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c memory.c -o memory.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c process.c -o process.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c syscall.c -o syscall.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c shell.c -o shell.o

# Link kernel
echo "[3/4] Linking kernel..."
ld -m elf_i386 -T linker.ld -nostdlib -o kernel.bin multiboot.o gdt.o interrupt.o kernel.o screen.o string.o idt.o gdt_c.o keyboard.o timer.o memory.o process.o syscall.o shell.o

# Create ISO
echo "[4/4] Creating ISO image..."
mkdir -p isodir/boot/grub
cp kernel.bin isodir/boot/kernel.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o entrada.iso isodir

echo
echo "=== Build Complete ==="
echo "ISO file: entrada.iso"
echo
echo "To run: qemu-system-i386 -cdrom entrada.iso"
