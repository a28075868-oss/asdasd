# Онлайн сборка Entrada OS (без установки)

Если у вас нет возможности установить инструменты локально, используйте онлайн-сервисы:

## Вариант 1: GitHub Codespaces

1. Создайте репозиторий на GitHub
2. Загрузите все файлы проекта
3. Откройте в Codespaces
4. В терминале:
```bash
sudo apt update
sudo apt install -y nasm gcc-multilib binutils grub-pc-bin xorriso
make
```

## Вариант 2: Replit

1. Создайте новый Repl (C/C++)
2. Загрузите файлы
3. В Shell:
```bash
nix-env -iA nixpkgs.nasm nixpkgs.gcc nixpkgs.binutils
make
```

## Вариант 3: Google Cloud Shell

1. Откройте https://shell.cloud.google.com/
2. Загрузите файлы
3. Установите зависимости и соберите:
```bash
sudo apt-get install -y nasm gcc-multilib binutils grub-pc-bin xorriso
make
```

## Вариант 4: Gitpod

1. Создайте репозиторий на GitHub/GitLab
2. Откройте через https://gitpod.io/#ВАШ_РЕПОЗИТОРИЙ
3. Соберите проект

## Скачать готовый ISO

После сборки в любом из сервисов, скачайте файл `entrada.iso` и запустите локально в VirtualBox или VMware.
