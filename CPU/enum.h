#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

const char* signature = "VERSION_2.3";

enum commands
{
    PUSH = 1,
    OUT = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    PUSHR = 7,
    POPR = 8,
    JUMP = 9,
    JE = 10,
    JNE = 11,
    JA = 12,
    JAE = 13,
    SQRT = 14,
    JB = 15,
    JBE = 16,
    CAT = 17,
    CALL = 18,
    RET = 19,
    DOG = 20,
    PARET = 21,
    PUSHP = 22,
    POPP = 23,
    END = 0
};

enum Register
{
    AX = 1,
    BX = 2,
    CX = 3,
    DX = 4,
};
