// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

// standard library
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>

// not part of the standard library
#include <ctype.h>

// version
#define VERSION "0.0.1"

// we use Int and Float instead of int and float because we need to use always the pointer size for any type that might share the fundamental union type;
// bruter use a union as universal type, and bruter is able to manipulate and use pointers direcly so we need to use the pointer size;
#if __SIZEOF_POINTER__ == 8
    #define Int long
    #define UInt uint64_t
    #define Float double
#else
    #define UInt uint32_t
    #define Int int32_t
    #define Float float
#endif

// Value
typedef union 
{
    // below types are not avaliable in bittype
    // these types depend on the size of the pointer
    Float f;
    Int i;
    UInt u;

    // these types are pointers
    char* s;
    void* p;
    
    // these types are arrays
    uint8_t u8[sizeof(Float)];
    uint16_t u16[sizeof(Float) / 2];
    uint32_t u32[sizeof(Float) / 4];

    int8_t i8[sizeof(Float)];
    int16_t i16[sizeof(Float) / 2];
    int32_t i32[sizeof(Float) / 4];

    float f32[sizeof(Float) / 4];
} Value;

#ifndef BIT_MATH
#define BIT_MATH 1

static inline uint8_t bit_get(uint8_t byte, uint8_t bit)
{
    return (byte >> bit) & 1;
}

static inline uint8_t bit_set(uint8_t byte, uint8_t bit)
{
    return byte | (1 << bit);
}

static inline uint8_t bit_clear(uint8_t byte, uint8_t bit)
{
    return byte & ~(1 << bit);
}

static inline uint8_t bit_toggle(uint8_t byte, uint8_t bit)
{
    return byte ^ (1 << bit);
}

#endif

typedef struct 
{
    unsigned int alloc: 1;
    unsigned int type: 7;
} Type;

typedef struct
{
    unsigned int bit0: 1;
    unsigned int bit1: 1;
    unsigned int bit2: 1;
    unsigned int bit3: 1;
    unsigned int bit4: 1;
    unsigned int bit5: 1;
    unsigned int bit6: 1;
    unsigned int bit7: 1;
} BitByte;

typedef Int (*Function)(void*, void*);
#define function(name) Int name(void *vm, void *args)

char* str_format(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Int size = vsnprintf(NULL, 0, format, args);
    va_end(args);
    char *str = (char*)malloc(size + 1);
    va_start(args, format);
    vsprintf(str, format, args);
    va_end(args);
    return str;
}


// file functions
char* readfile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char *code = (char*)malloc(1);
    code[0] = '\0';
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
    {
        code = (char*)realloc(code, strlen(code) + strlen(line) + 1);
        strcat(code, line);
    }
    free(line);
    fclose(file);
    return code;
};

void writefile(char *filename, char *code)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return;
    }
    fprintf(file, "%s", code);
    fclose(file);
}

bool file_exists(char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return false;
    }
    fclose(file);
    return true;
}

int main()
{
  
}
