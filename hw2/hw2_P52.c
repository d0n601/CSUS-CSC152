/**
 * @file hw2_P52.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 28 Sep 2018
 *
 * @section DESCRIPTION
 *
 * @brief CSC 152 HW2 P2.
 *
 * Compile: gcc hw2_P52.c -std=c99 -W -Wall -Wpedantic -c
 *
 * This program was written for homework 2. It implements
 * the psudocode given in class for the 48-byte permutation
 * known as P52.
 *
 */

#include<stdio.h>

void P52(unsigned s[12]) {

    for(int i = 0; i < 24; i++) {

        for(int j = 0; j < 4; j++) {
            unsigned x = (s[j] << 24) | (s[j] >> (32 - 24));
            unsigned y = (s[4+j] << 9) | (s[4+j] >> (32 - 9));
            unsigned z = s[8+j]; // Just set z.

            s[8+j] = x ^ (z << 1) ^ ((y & z) << 2);
            s[4+j] = y ^ x ^ ((x | z) << 1);
            s[j] = z ^ y ^ ((x & y) << 3);
        }

        // Mix columns.
        if ( (i % 4) == 0) {
            /* 2D representation (s[0,0], s[0,1], s[0,2], s[0,3]) = (s[0,1], s[0,0], s[0,3], s[0,2]) */
            unsigned temp = s[0];
            s[0] = s[1];
            s[1] = temp;
            temp = s[2];
            s[2] = s[3];
            s[3] = temp;

            /* s[0,0] = s[0,0] xor 0x9e377900 xor (24-i) */
            s[0] = s[0] ^ 0x9e377900 ^ (24 - i);

        }

        // Mix columns differently.
        else if ( (i % 4) == 2) {
            /* 2D representation (s[0,0], s[0,1], s[0,2], s[0,3]) = (s[0,2], s[0,3], s[0,0], s[0,1]) */
            unsigned temp0 = s[0];
            unsigned temp1 = s[1];
            s[0] = s[2];
            s[1] = s[3];
            s[2] = temp0;
            s[3] = temp1;
        }

    }

}
