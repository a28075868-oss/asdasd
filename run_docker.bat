@echo off
echo Building Entrada OS with Docker...
echo.

docker build -t entrada-builder .
if errorlevel 1 (
    echo Docker build failed!
    pause
    exit /b 1
)

docker run --rm -v %cd%:/workspace entrada-builder
if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo Build complete! entrada.iso created.
echo.
echo To run in QEMU:
echo   qemu-system-i386 -cdrom entrada.iso
echo.
pause
