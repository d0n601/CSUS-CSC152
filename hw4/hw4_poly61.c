/**
 * @file hw4_poly61.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 7 Nov 2018
 * 
 * @section DESCRIPTION
 * 
 * Implement polynomial hashing using Horner’s method and divisionless mod.
 *   
 * @brief CSC 152 HW4 P3.
 *  
 * Compile via ECA Apollo: gcc hw4_poly61.c -std=c99 -W -Wall -c
 *             
 */               

#include <string.h>
#include <stdio.h>
#include <stdint.h>

uint64_t poly61(unsigned char *m, unsigned mbytes, uint64_t k) {

    unsigned __int128 res = 1;
    unsigned char tail[4] = {0};
    unsigned i = 0;

   /* Full blocks */ 
    while (mbytes >= i+4) {
        res = res * k + *(unsigned *) (m + i);
        res = (res >> 61) + (res & ((1ULL << 61) - 1));
        if (res >= (1ULL << 61) - 1) {
            res -= (1ULL << 61) - 1;
        }
        i += 4;
    }

    /* Handle additional bytes */
    memcpy(tail, m + i, mbytes - i);
    tail[mbytes-i] = 0x80;
    res = res * k + *(unsigned *)tail;
    res = (res >> 61) + (res & ((1ULL << 61) - 1));

    if (res >= (1ULL << 61) - 1) {
        res -= (1ULL << 61) - 1;
    }

    return (uint64_t)res;
}
