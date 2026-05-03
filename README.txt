================================================================================
                            ENTRADA OS v1.0
                    Минимальная 32-битная операционная система
================================================================================

ОПИСАНИЕ:
---------
Entrada OS - это полнофункциональная операционная система, написанная на C и 
Assembly с нуля. Система включает загрузчик, ядро, драйверы устройств, 
управление памятью, процессами и командную оболочку.

ВОЗМОЖНОСТИ:
------------
✓ Multiboot загрузка через GRUB
✓ Защищенный режим x86 (32-bit)
✓ GDT (Global Descriptor Table)
✓ IDT (Interrupt Descriptor Table) 
✓ Драйвер клавиатуры PS/2
✓ Системный таймер (PIT)
✓ VGA текстовый режим 80x25
✓ Динамическое выделение памяти (kmalloc/kfree)
✓ Базовое управление процессами
✓ Системные вызовы
✓ Интерактивная командная оболочка

СТРУКТУРА ПРОЕКТА:
------------------
multiboot.asm      - Multiboot заголовок и точка входа
kernel.c           - Главное ядро системы
screen.c/h         - VGA драйвер
keyboard.c/h       - Драйвер клавиатуры
memory.c/h         - Управление памятью
process.c/h        - Управление процессами
idt.c/h            - Таблица прерываний
gdt.c/h            - Таблица дескрипторов
timer.c/h          - Системный таймер
syscall.c/h        - Системные вызовы
shell.c/h          - Командная оболочка
string.c           - Строковые функции
types.h            - Базовые типы
kernel.h           - Общие определения
linker.ld          - Скрипт линкера
grub.cfg           - Конфигурация GRUB
Makefile           - Автоматическая сборка

БЫСТРЫЙ СТАРТ:
--------------

1. УСТАНОВКА ИНСТРУМЕНТОВ:

   Windows (WSL2):
   ---------------
   wsl --install
   sudo apt install nasm gcc-multilib binutils grub-pc-bin xorriso qemu-system-x86

   Linux (Ubuntu/Debian):
   ----------------------
   sudo apt install nasm gcc-multilib binutils grub-pc-bin xorriso qemu-system-x86

   Docker (любая ОС):
   ------------------
   docker build -t entrada-builder .
   docker run --rm -v ${PWD}:/workspace entrada-builder

2. СБОРКА:

   make

3. ЗАПУСК:

   make run

   Или вручную:
   qemu-system-i386 -cdrom entrada.iso

КОМАНДЫ SHELL:
--------------
help     - Показать справку
clear    - Очистить экран
about    - Информация о системе
meminfo  - Информация о памяти

ТРЕБОВАНИЯ:
-----------
Для сборки:
- NASM (ассемблер)
- GCC с поддержкой 32-bit (gcc-multilib)
- GNU LD (линкер)
- GRUB tools (grub-mkrescue)
- xorriso

Для запуска:
- QEMU / VirtualBox / VMware
- Процессор: x86 (32-bit)
- RAM: 64 MB минимум

ДОКУМЕНТАЦИЯ:
-------------
SETUP_GUIDE.md       - Подробное руководство по установке
QUICK_START.md       - Быстрый старт
COMMANDS.md          - Справочник команд
PROJECT_STRUCTURE.md - Архитектура системы
online_build.md      - Онлайн сборка без установки

ФАЙЛЫ СБОРКИ:
-------------
После успешной сборки будут созданы:
- kernel.bin    - Скомпилированное ядро
- entrada.iso   - Загрузочный ISO образ (запускайте этот файл!)
- *.o           - Объектные файлы
- isodir/       - Временная папка для ISO

ЗАПУСК В VIRTUALBOX:
--------------------
1. Создать новую ВМ:
   - Тип: Other
   - Версия: Other/Unknown (32-bit)
   - RAM: 128 MB
   - Без жесткого диска

2. Настройки → Носители → Добавить оптический привод
3. Выбрать entrada.iso
4. Запустить

ЗАПУСК В VMWARE:
----------------
1. Create a New Virtual Machine
2. Installer disc image file (iso): entrada.iso
3. Guest OS: Other → Other (32-bit)
4. Memory: 128 MB
5. Finish и запустить

ОТЛАДКА:
--------
# Запуск с отладкой
qemu-system-i386 -cdrom entrada.iso -serial stdio

# Дизассемблирование
objdump -d kernel.bin > kernel.asm

# Просмотр символов
nm kernel.bin

# GDB отладка
qemu-system-i386 -cdrom entrada.iso -s -S
gdb kernel.bin
(gdb) target remote localhost:1234

РАСШИРЕНИЕ:
-----------
Система спроектирована для легкого расширения:
- Добавление новых драйверов
- Новые системные вызовы
- Дополнительные команды shell
- Файловая система
- Сетевая поддержка

См. PROJECT_STRUCTURE.md для деталей.

ТЕХНИЧЕСКИЕ ДЕТАЛИ:
-------------------
Язык: C (C99), Assembly (NASM)
Архитектура: x86 (32-bit, Protected Mode)
Загрузчик: GRUB (Multiboot)
Компилятор: GCC -m32 -ffreestanding
Без стандартной библиотеки (freestanding)
Прямая работа с железом (bare metal)

ЛИЦЕНЗИЯ:
---------
Свободное использование в образовательных целях.

АВТОР:
------
Entrada OS - учебная операционная система

ВЕРСИЯ:
-------
1.0 (2024)

================================================================================
                    Спасибо за использование Entrada OS!
================================================================================
