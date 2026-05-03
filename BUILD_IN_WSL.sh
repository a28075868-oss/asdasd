#!/bin/bash

echo "========================================"
echo "  Entrada OS - Сборка в WSL"
echo "========================================"
echo

# Проверка что мы в WSL
if ! grep -qi microsoft /proc/version; then
    echo "ОШИБКА: Этот скрипт должен запускаться в WSL!"
    exit 1
fi

echo "[1/4] Обновление пакетов..."
sudo apt update

echo
echo "[2/4] Установка инструментов..."
sudo apt install -y nasm gcc-multilib g++-multilib binutils grub-pc-bin xorriso make

if [ $? -ne 0 ]; then
    echo
    echo "ОШИБКА: Не удалось установить инструменты"
    exit 1
fi

echo
echo "[3/4] Компиляция..."

# Компиляция assembly файлов
echo "  - Компиляция assembly файлов..."
nasm -f elf32 multiboot.asm -o multiboot.o || exit 1
nasm -f elf32 gdt.asm -o gdt.o || exit 1
nasm -f elf32 interrupt.asm -o interrupt.o || exit 1

# Компиляция C файлов
echo "  - Компиляция C файлов..."
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c kernel.c -o kernel.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c screen.c -o screen.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c string.c -o string.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c idt.c -o idt.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c gdt.c -o gdt_c.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c keyboard.c -o keyboard.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c timer.c -o timer.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c memory.c -o memory.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c process.c -o process.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c syscall.c -o syscall.o || exit 1
gcc -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Wall -Wextra -O2 -c shell.c -o shell.o || exit 1

# Линковка
echo "  - Линковка ядра..."
ld -m elf_i386 -T linker.ld -nostdlib -o kernel.bin \
   multiboot.o gdt.o interrupt.o kernel.o screen.o string.o \
   idt.o gdt_c.o keyboard.o timer.o memory.o process.o \
   syscall.o shell.o || exit 1

echo
echo "[4/4] Создание ISO образа..."
mkdir -p isodir/boot/grub
cp kernel.bin isodir/boot/kernel.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o entrada.iso isodir || exit 1

echo
echo "========================================"
echo "  ✓ Сборка завершена успешно!"
echo "========================================"
echo
echo "Файл создан: entrada.iso"
echo "Размер: $(du -h entrada.iso | cut -f1)"
echo
echo "Для запуска:"
echo "  qemu-system-i386 -cdrom entrada.iso"
echo
echo "Или скопируйте entrada.iso в Windows и запустите в VirtualBox"
echo
