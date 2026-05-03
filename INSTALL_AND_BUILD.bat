@echo off
echo ========================================
echo   Entrada OS - Автоматическая установка
echo ========================================
echo.

echo Этот скрипт установит WSL2 и соберет Entrada OS
echo.
echo ВНИМАНИЕ: Требуются права администратора!
echo.
pause

echo.
echo [1/3] Установка WSL2...
echo.
wsl --install -d Ubuntu
if errorlevel 1 (
    echo.
    echo ОШИБКА: Не удалось установить WSL2
    echo.
    echo Пожалуйста, установите WSL2 вручную:
    echo 1. Откройте PowerShell от имени администратора
    echo 2. Выполните: wsl --install
    echo 3. Перезагрузите компьютер
    echo 4. Запустите этот скрипт снова
    echo.
    pause
    exit /b 1
)

echo.
echo WSL2 установлен! Необходима перезагрузка.
echo.
echo После перезагрузки:
echo 1. Откройте Ubuntu из меню Пуск
echo 2. Создайте имя пользователя и пароль
echo 3. Выполните команды:
echo.
echo    cd /mnt/c/Users/a2807/Desktop/legacyclicker2
echo    sudo apt update
echo    sudo apt install -y nasm gcc-multilib binutils grub-pc-bin xorriso
echo    make
echo.
echo Файл entrada.iso будет создан в этой папке.
echo.
pause

echo Перезагрузите компьютер сейчас? (Y/N)
set /p choice=
if /i "%choice%"=="Y" shutdown /r /t 10
