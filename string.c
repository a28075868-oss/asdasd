#include "kernel.h"

int strlen(const char* str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void strcpy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

void memset(void* dest, uint8 val, uint32 len) {
    uint8* d = (uint8*)dest;
    for (uint32 i = 0; i < len; i++) {
        d[i] = val;
    }
}

void memcpy(void* dest, const void* src, uint32 len) {
    uint8* d = (uint8*)dest;
    const uint8* s = (const uint8*)src;
    for (uint32 i = 0; i < len; i++) {
        d[i] = s[i];
    }
}
