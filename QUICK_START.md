# Entrada OS - Быстрый старт

## Вариант 1: Docker (Рекомендуется для Windows)

```bash
# Создать Docker образ для сборки
docker build -t entrada-builder .

# Собрать ОС
docker run --rm -v ${PWD}:/workspace entrada-builder

# Запустить в QEMU
qemu-system-i386 -cdrom entrada.iso
```

## Вариант 2: WSL2 (Windows Subsystem for Linux)

```bash
# Установить WSL2
wsl --install

# В WSL установить инструменты
sudo apt update
sudo apt install nasm gcc-multilib binutils grub-pc-bin xorriso qemu-system-x86

# Собрать
make

# Запустить
make run
```

## Вариант 3: Linux

```bash
# Установить зависимости
sudo apt install nasm gcc-multilib binutils grub-pc-bin xorriso qemu-system-x86

# Собрать
make

# Запустить
make run
```

## Вариант 4: VirtualBox/VMware

1. Соберите ISO на Linux/WSL/Docker
2. Создайте новую виртуальную машину:
   - Тип: Other/Unknown
   - Версия: Other/Unknown (32-bit)
   - RAM: 128MB
   - Без жесткого диска
3. Подключите entrada.iso как CD-ROM
4. Запустите

## Структура проекта

```
entrada-os/
├── multiboot.asm      # Multiboot заголовок и точка входа
├── kernel.c           # Главное ядро
├── screen.c/h         # VGA драйвер
├── keyboard.c/h       # Драйвер клавиатуры
├── memory.c/h         # Управление памятью
├── process.c/h        # Управление процессами
├── idt.c/h            # Таблица прерываний
├── gdt.c/h            # Таблица дескрипторов
├── timer.c/h          # Системный таймер
├── syscall.c/h        # Системные вызовы
├── shell.c/h          # Командная оболочка
├── linker.ld          # Скрипт линкера
├── grub.cfg           # Конфигурация GRUB
└── Makefile           # Сборка
```

## Команды в Shell

- `help` - Справка
- `clear` - Очистить экран
- `about` - Информация о системе
- `meminfo` - Информация о памяти
