# Установка инструментов для сборки Entrada OS

## Windows

### 1. NASM (Ассемблер)
- Скачать: https://www.nasm.us/pub/nasm/releasebuilds/
- Установить и добавить в PATH

### 2. MinGW-w64 (GCC, LD)
- Скачать: https://www.mingw-w64.org/downloads/
- Или через MSYS2: https://www.msys2.org/
```bash
pacman -S mingw-w64-i686-gcc
pacman -S mingw-w64-i686-binutils
```

### 3. GRUB для Windows
```bash
pacman -S grub
pacman -S xorriso
```

### 4. QEMU (Эмулятор)
- Скачать: https://qemu.weilnetz.de/w64/

## Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install nasm gcc-multilib binutils grub-pc-bin xorriso qemu-system-x86
```

## Сборка

### Linux/MSYS2:
```bash
chmod +x build.sh
./build.sh
```

### Или через Make:
```bash
make
make run
```

## Запуск

```bash
qemu-system-i386 -cdrom entrada.iso
```

Или двойной клик на entrada.iso в VirtualBox/VMware
