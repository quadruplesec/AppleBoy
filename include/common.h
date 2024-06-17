#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Returns the bit at a particular position
#define BIT(a, n) ( (a & (1 << n)) ? 1 : 0 )

// Study how this macro works better, its a bit confusing
#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n); }

// Checks if a number is between 2 other numbers
#define BETWEEN(a, b, c) ( (a >= b) && (a <= c) )

// Exists if something is not yet implemented
#define NO_IMPL { fprintf(stderr, "NOT YET IMPLEMENTED!\n"); exit(EXIT_FAILURE); }

void delay(u32 ms);

#endif