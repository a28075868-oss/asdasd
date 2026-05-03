#!/bin/bash

echo "Building Entrada OS with Docker..."
echo

docker build -t entrada-builder .
if [ $? -ne 0 ]; then
    echo "Docker build failed!"
    exit 1
fi

docker run --rm -v $(pwd):/workspace entrada-builder
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo
echo "Build complete! entrada.iso created."
echo
echo "To run in QEMU:"
echo "  qemu-system-i386 -cdrom entrada.iso"
echo
