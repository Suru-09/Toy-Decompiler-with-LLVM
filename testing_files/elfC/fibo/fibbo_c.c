//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ------------------- Function Prototypes --------------------

int64_t __do_global_dtors_aux(void);
int64_t _fini(void);
int64_t _init(void);
int64_t _start(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6);
int64_t deregister_tm_clones(void);
int32_t fibo(uint32_t n);
int64_t frame_dummy(void);
void function_1040(int64_t * d);
int32_t function_1050(char * format, ...);
int64_t register_tm_clones(void);

// --------------------- Global Variables ---------------------

int64_t g1 = 0; // 0x4010
int32_t g2;

// ------- Dynamically Linked Functions Without Header --------

void __cxa_finalize(int64_t * a1);
void __gmon_start__(void);
int32_t __libc_start_main(int64_t a1, int32_t a2, char ** a3, void (*a4)(), void (*a5)(), void (*a6)());

// ------------------------ Functions -------------------------

// Address range: 0x1000 - 0x101b
int64_t _init(void) {
    int64_t result = 0; // 0x1012
    if (*(int64_t *)0x3fe8 != 0) {
        // 0x1014
        __gmon_start__();
        result = &g2;
    }
    // 0x1016
    return result;
}

// Address range: 0x1040 - 0x104b
void function_1040(int64_t * d) {
    // 0x1040
    __cxa_finalize(d);
}

// Address range: 0x1050 - 0x105b
int32_t function_1050(char * format, ...) {
    // 0x1050
    return printf(format);
}

// Address range: 0x1060 - 0x1086
int64_t _start(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6) {
    // 0x1060
    int64_t v1; // 0x1060
    __libc_start_main(0x118a, (int32_t)a6, (char **)&v1, NULL, NULL, (void (*)())a3);
    __asm_hlt();
    // UNREACHABLE
}

// Address range: 0x1090 - 0x10b9
int64_t deregister_tm_clones(void) {
    // 0x1090
    return &g1;
}

// Address range: 0x10c0 - 0x10f9
int64_t register_tm_clones(void) {
    // 0x10c0
    return 0;
}

// Address range: 0x1100 - 0x1139
int64_t __do_global_dtors_aux(void) {
    // 0x1100
    if (*(char *)&g1 != 0) {
        // 0x1138
        int64_t result; // 0x1100
        return result;
    }
    // 0x110d
    if (*(int64_t *)0x3ff8 != 0) {
        // 0x111b
        __cxa_finalize((int64_t *)*(int64_t *)0x4008);
    }
    int64_t result2 = deregister_tm_clones(); // 0x1127
    *(char *)&g1 = 1;
    return result2;
}

// Address range: 0x1140 - 0x1149
int64_t frame_dummy(void) {
    // 0x1140
    return register_tm_clones();
}

// From module:   /home/users/dragoss/Documents/licenta/Reverse-Engineering-Tool/testing_files/source/fibonacci.c
// Address range: 0x1149 - 0x118a
// Line range:    4 - 6
int32_t fibo(uint32_t n) {
    int32_t result = 1; // 0x115d
    if (n >= 2) {
        int32_t v1 = fibo(n - 1); // 0x1167
        result = fibo(n - 2) + v1;
    }
    // 0x1184
    return result;
}

// From module:   /home/users/dragoss/Documents/licenta/Reverse-Engineering-Tool/testing_files/source/fibonacci.c
// Address range: 0x118a - 0x11cc
// Line range:    8 - 13
int main() {
    // 0x118a
    printf("Fibonacci of <%d> is : [%d]\n", 15, (int64_t)(uint32_t)fibo(14));
    return 0;
}

// Address range: 0x11cc - 0x11d9
int64_t _fini(void) {
    // 0x11cc
    int64_t result; // 0x11cc
    return result;
}

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (11.2.0)
// Detected functions: 11

