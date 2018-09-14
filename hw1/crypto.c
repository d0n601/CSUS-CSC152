
/**
 * @file hw1.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 14 Sep 2018
 *
 * @section DESCRIPTION
 *
 * @brief CSC 152 HW1 P1.
 * 
 * Compile: s -std=c99 -W -Wall -Wpedantic -c 
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

	// Split 32bits into lower and upper halves.
	unsigned lo = x & 0xffff; // Low 16 bits.
	unsigned hi = x >> 16; // High 16 bits.

	lo = lo ^ (hi*hi); // XOR low bits with high bits squared.
	hi = hi ^ (lo*lo); // XOR high bits with low bits squared.
	x = (hi << 16) | lo; // Rotate bits left.

	return x; // Return resultant integer. 
}


/**
 * Uses a Feistel construction to invert an unsigned int.
 * For lack of a better term, this is the "decryption" function.
 *
 * @param  integer previously inverted
 * @return inverted input (original int)
 */
unsigned inverse_perm(unsigned y) {

	// Split 32bits into lower and upper halves.
	unsigned lo = y & 0xfff; // Low 16 bits.
	unsigned hi = y >> 16; // High 16 bits.

	y = (hi >> 16) | lo; // Rotate bits right.
	hi = hi ^ (lo*lo); // XOR high bits with low bits squared.
	lo = lo ^ (hi*hi); // XOR low bits with high bits squared.

	return y; // Return original integer.

}


int main(void) {

	unsigned i = 1776; // Initially set our unsigned integer
	
	unsigned y = perm(i); // Permutation call
	unsigned x = inverse_perm(y); // We should get i back.

	if(x != i ) {
		printf("WARNING: Broken stuff...\n");
	}


	printf("Permutation %i: %i \n", i, y);	
	printf("UnPermutation %i: %i \n", y, x);

	return EXIT_SUCCESS;

}
