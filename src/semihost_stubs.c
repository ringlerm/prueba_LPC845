#include <stdint.h>
#include <stddef.h>

// Si la macro DEBUG está definida, habilitamos el semihosting real
#if defined (DEBUG)

uint8_t __Ciob[80];

static inline int __semihost(int command, void *message) {
    register int reg_command __asm("r0") = command;
    register void *reg_message __asm("r1") = message;
    __asm volatile (
        "bkpt 0xAB"
        : "=r"(reg_command)
        : "r"(reg_command), "r"(reg_message)
        : "memory"
    );
    return reg_command;
}

int __sys_write(int handle, char *buffer, int len) {
    uint32_t m[] = { (uint32_t)handle, (uint32_t)buffer, (uint32_t)len };
    int ret = __semihost(0x05, m);
    return len - ret;
}

int __sys_istty(int handle) {
    uint32_t m[] = { (uint32_t)handle };
    return __semihost(0x09, m);
}

int __sys_seek(int handle, int pos) { return -1; }
int __sys_flen(int handle) { return 0; }

void __sys_appexit(void) {
    uint32_t m[] = { 0x20026 };
    __semihost(0x18, m);
    while(1);
}

#else
// Opciones para cuando NO estamos en Debug (Producción / Release)

// Dejamos stubs vacíos para que el compilador no tire error de linkeo,
// pero que no hagan absolutamente nada ni cuelguen al microcontrolador.
int __sys_write(int handle, char *buffer, int len) { return len; }
int __sys_istty(int handle) { return 0; }
int __sys_seek(int handle, int pos) { return -1; }
int __sys_flen(int handle) { return 0; }
void __sys_appexit(void) { while(1); }

#endif
