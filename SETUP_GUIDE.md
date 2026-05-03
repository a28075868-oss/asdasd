# Entrada OS - Полное руководство по установке

## Для Windows пользователей

### Вариант A: Docker Desktop (Самый простой)

1. **Установить Docker Desktop**
   - Скачать: https://www.docker.com/products/docker-desktop/
   - Установить и перезагрузить компьютер
   - Запустить Docker Desktop

2. **Собрать ОС**
   ```cmd
   run_docker.bat
   ```

3. **Результат**: файл `entrada.iso` будет создан

---

### Вариант B: WSL2 (Рекомендуется)

1. **Установить WSL2**
   ```powershell
   wsl --install
   ```
   Перезагрузить компьютер

2. **Открыть WSL терминал** (Ubuntu)

3. **Установить инструменты**
   ```bash
   sudo apt update
   sudo apt install -y nasm gcc-multilib g++-multilib binutils \
                       grub-pc-bin xorriso make qemu-system-x86
   ```

4. **Перейти в папку проекта**
   ```bash
   cd /mnt/c/Users/ВАШ_ПОЛЬЗОВАТЕЛЬ/Desktop/legacyclicker2
   ```

5. **Собрать**
   ```bash
   make
   ```

6. **Запустить**
   ```bash
   make run
   ```

---

### Вариант C: MSYS2 (Для продвинутых)

1. **Установить MSYS2**
   - Скачать: https://www.msys2.org/
   - Установить в C:\msys64

2. **Открыть MSYS2 MinGW 32-bit**

3. **Установить пакеты**
   ```bash
   pacman -Syu
   pacman -S mingw-w64-i686-gcc mingw-w64-i686-binutils nasm make
   ```

4. **Собрать проект**
   ```bash
   cd /c/Users/ВАШ_ПОЛЬЗОВАТЕЛЬ/Desktop/legacyclicker2
   make
   ```

---

## Для Linux пользователей

### Ubuntu/Debian

```bash
sudo apt update
sudo apt install -y nasm gcc-multilib g++-multilib binutils \
                    grub-pc-bin xorriso make qemu-system-x86

make
make run
```

### Arch Linux

```bash
sudo pacman -S nasm gcc-multilib binutils grub xorriso make qemu

make
make run
```

### Fedora

```bash
sudo dnf install nasm gcc binutils grub2-tools xorriso make qemu-system-x86

make
make run
```

---

## Запуск ISO образа

### В QEMU (эмулятор)

```bash
qemu-system-i386 -cdrom entrada.iso
```

### В VirtualBox

1. Создать новую ВМ:
   - Имя: Entrada OS
   - Тип: Other
   - Версия: Other/Unknown (32-bit)
   - RAM: 128 MB
   - Без жесткого диска

2. Настройки → Носители → Добавить оптический привод
3. Выбрать entrada.iso
4. Запустить

### В VMware

1. Create a New Virtual Machine
2. Installer disc image file (iso): entrada.iso
3. Guest OS: Other → Other (32-bit)
4. Memory: 128 MB
5. Finish и запустить

---

## Проверка сборки

После успешной сборки должны появиться файлы:
- `kernel.bin` - скомпилированное ядро
- `entrada.iso` - загрузочный ISO образ
- `isodir/` - временная папка для ISO

---

## Устранение проблем

### "command not found" ошибки
- Убедитесь, что все инструменты установлены
- Проверьте PATH переменную

### Ошибки компиляции
- Убедитесь, что используете 32-битные библиотеки (gcc-multilib)
- Проверьте версию GCC (должна поддерживать -m32)

### ISO не создается
- Установите xorriso: `sudo apt install xorriso`
- Проверьте наличие grub-mkrescue

### QEMU не запускается
- Установите: `sudo apt install qemu-system-x86`
- Или используйте VirtualBox/VMware

---

## Минимальные требования

- **Процессор**: x86 (32-bit)
- **RAM**: 64 MB
- **Место на диске**: 10 MB для ISO

---

## Что дальше?

После запуска вы увидите:
```
Entrada OS v1.0
Initializing kernel...
Kernel initialized successfully
Type 'help' for commands

entrada>
```

Доступные команды:
- `help` - список команд
- `clear` - очистить экран
- `about` - информация о системе
- `meminfo` - информация о памяти
