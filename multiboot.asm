; Entrada OS - Multiboot Header
[BITS 32]

section .multiboot
align 4

MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_FLAGS equ 0x00000003
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global kernel_entry
extern kernel_main

kernel_entry:
    mov esp, stack_top
    
    push ebx
    push eax
    
    call kernel_main
    
    cli
.hang:
    hlt
    jmp .hang
