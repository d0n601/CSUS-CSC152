/**
 * @file hw1.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 27 Sep 2018
 *
 * @section DESCRIPTION
 *
 * @brief CSC 152 HW1 P1.
 * 
 * Compile: gcc hw1.c -std=c99 -W -Wall -Wpedantic -c 
 *
 * This program was written for homework 1. Using a Feistel 
 * construction, we create a simple invertable function, 
 * along with its inverse.
 *
 */

#include<stdio.h>
#include<stdlib.h>


/**
 * Uses a Feistel construction to invert an unsigned int.
 * For lack of a better term, this is the "encryption" function.
 *
 * @param  integer to invert
 * @return inverted input
 */
unsigned perm(unsigned x) {

        unsigned hi = x >> 16; // High 16 bits.
	unsigned lo = x & 0xFFFF; // Low  16 bits.

        hi = hi ^ (lo * lo);
        lo = lo ^ (hi * hi);
 
        x = ( hi << 16) | (lo & 0xFFFF); // Fixed on resubmission
 
        return x;

}



/**
 * Uses a Feistel construction to invert an unsigned int.
 * For lack of a better term, this is the "decryption" function.
 *
 * @param  integer previously inverted
 * @return inverted input (original int)
 */
unsigned inverse_perm(unsigned y) {

        unsigned hi = y >> 16; // High 16 bits.
        unsigned lo = y & 0xFFFF; // Low 16 bits.
 
        lo = lo ^ (hi * hi); // Inverted order from perm()
        hi = hi ^ (lo * lo); // ""   

        y = (hi << 16) | (lo & 0xFFFF); // Fixed on resubmission

        return y; // Return original integer.

}

