/**
 * @file hw2_mult.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 30 Sep 2018
 *
 * @section DESCRIPTION
 *
 * @brief CSC 152 HW2 P1.
 *
 * Compile: gcc hw2_mult.c -std=c99 -W -Wall -pedantic -c
 *
 * This program was written for homework 2. It implements
 * the psudocode given in class for for GF multiplication.
 *
 */

#include <stdio.h>


unsigned mult(unsigned a, unsigned b, unsigned modulus, unsigned degree) {

    unsigned extra = 0; // Result of multiplication

    while( a > 0 ) {

        if( a % 2 ) { // p1 has x^0 term
            a = a ^ 1;  // p1 = p1 - x^0
            extra = extra ^ b; // extra = extra + p2
        }

        a = a >> 1; // p1 = p1 * x^-1
        b = b << 1; // p2 = p2 * x

        if(b & (1 << degree)) { // p2 has x^n term
            b = (b ^ (1 << degree)) ^ (modulus ^ (1 << degree)); // p2 = p2 - x^n + (modulus' lower terms)
        }

    }

    return extra; // result of multiplication
}
