# Entrada OS - Справочник команд

## Сборка проекта

### Linux / WSL / Mac

```bash
# Полная сборка
make

# Только компиляция (без ISO)
make kernel.bin

# Очистка
make clean

# Сборка и запуск
make run
```

### Docker

```bash
# Windows
run_docker.bat

# Linux/Mac
./run_docker.sh
```

### Ручная сборка

```bash
# 1. Компиляция assembly файлов
nasm -f elf32 multiboot.asm -o multiboot.o
nasm -f elf32 gdt.asm -o gdt.o
nasm -f elf32 interrupt.asm -o interrupt.o

# 2. Компиляция C файлов
gcc -m32 -ffreestanding -nostdlib -fno-pie -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c screen.c -o screen.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c string.c -o string.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c idt.c -o idt.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c gdt.c -o gdt_c.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c timer.c -o timer.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c memory.c -o memory.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c process.c -o process.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c syscall.c -o syscall.o
gcc -m32 -ffreestanding -nostdlib -fno-pie -c shell.c -o shell.o

# 3. Линковка
ld -m elf_i386 -T linker.ld -nostdlib -o kernel.bin \
   multiboot.o gdt.o interrupt.o kernel.o screen.o string.o \
   idt.o gdt_c.o keyboard.o timer.o memory.o process.o \
   syscall.o shell.o

# 4. Создание ISO
mkdir -p isodir/boot/grub
cp kernel.bin isodir/boot/kernel.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o entrada.iso isodir
```

## Запуск

### QEMU

```bash
# Базовый запуск
qemu-system-i386 -cdrom entrada.iso

# С отладочной информацией
qemu-system-i386 -cdrom entrada.iso -serial stdio

# С большей памятью
qemu-system-i386 -cdrom entrada.iso -m 256M

# С отладкой GDB
qemu-system-i386 -cdrom entrada.iso -s -S
```

### VirtualBox

```bash
# Создать ВМ через CLI
VBoxManage createvm --name "Entrada OS" --ostype Other --register
VBoxManage modifyvm "Entrada OS" --memory 128 --boot1 dvd
VBoxManage storagectl "Entrada OS" --name "IDE" --add ide
VBoxManage storageattach "Entrada OS" --storagectl "IDE" \
           --port 0 --device 0 --type dvddrive --medium entrada.iso
VBoxManage startvm "Entrada OS"
```

## Команды Shell в Entrada OS

После загрузки системы доступны следующие команды:

### help
Показывает список доступных команд
```
entrada> help
```

### clear
Очищает экран
```
entrada> clear
```

### about
Показывает информацию о системе
```
entrada> about
```
Вывод:
```
Entrada OS v1.0
A minimal 32-bit operating system
Features: GDT, IDT, Memory, Keyboard, Timer
```

### meminfo
Показывает информацию о памяти
```
entrada> meminfo
```
Вывод:
```
Heap Start: 0x100000
Heap Size: 1MB
```

## Отладка

### Просмотр дизассемблированного кода

```bash
objdump -d kernel.bin > kernel.asm
```

### Просмотр символов

```bash
nm kernel.bin
```

### Просмотр секций

```bash
readelf -S kernel.bin
```

### Отладка с GDB

```bash
# Терминал 1: запустить QEMU с ожиданием GDB
qemu-system-i386 -cdrom entrada.iso -s -S

# Терминал 2: подключить GDB
gdb kernel.bin
(gdb) target remote localhost:1234
(gdb) break kernel_main
(gdb) continue
```

## Тестирование

### Проверка Multiboot заголовка

```bash
grub-file --is-x86-multiboot kernel.bin
echo $?  # Должно быть 0
```

### Проверка размера

```bash
ls -lh kernel.bin entrada.iso
```

### Проверка зависимостей

```bash
ldd kernel.bin  # Не должно быть зависимостей
```

## Полезные команды

### Создание загрузочной USB флешки

```bash
# ВНИМАНИЕ: Это удалит все данные на /dev/sdX!
sudo dd if=entrada.iso of=/dev/sdX bs=4M status=progress
sudo sync
```

### Монтирование ISO

```bash
mkdir -p /tmp/entrada
sudo mount -o loop entrada.iso /tmp/entrada
ls -la /tmp/entrada
sudo umount /tmp/entrada
```

### Извлечение kernel.bin из ISO

```bash
7z x entrada.iso boot/kernel.bin
```

## Переменные окружения

```bash
# Для кросс-компиляции
export CC=i686-elf-gcc
export LD=i686-elf-ld
export AS=nasm

# Для 32-bit на 64-bit системе
export CFLAGS="-m32"
export LDFLAGS="-m elf_i386"
```

## Устранение проблем

### Ошибка: "multiboot header not found"

```bash
# Проверить наличие multiboot заголовка
hexdump -C kernel.bin | head -20
# Должны увидеть: 02 b0 ad 1b (magic number)
```

### Ошибка: "undefined reference"

```bash
# Проверить порядок объектных файлов при линковке
# multiboot.o должен быть первым!
```

### Ошибка: "cannot find -lgcc"

```bash
# Установить 32-bit библиотеки
sudo apt install gcc-multilib
```

### QEMU не запускается

```bash
# Проверить установку
which qemu-system-i386

# Установить если нужно
sudo apt install qemu-system-x86
```
