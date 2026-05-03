FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    nasm \
    gcc-multilib \
    g++-multilib \
    binutils \
    grub-pc-bin \
    xorriso \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["make"]
