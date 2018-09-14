#include<stdio.h>
#include<stdlib.h>


/**
 * Note: int's and char's are stored with 32 bits.
 * when tpplying the shift, 32 - 1 = 31 (lines 15 & 25). 
 *
 */


unsigned perm(unsigned x) {

	x = x^7; // XOR with 7 (XOR is invertable).
	x = (x << 1) | (x >> (31) ); // Rotate bits left.	
	x = x+1; // Add 1

	return x;
}


unsigned unperm(unsigned y ) {

	y = y-1; // Subtract 1
	y = (y >> 1) | (y << (31) ); // Rotate bits right.
	y = y ^7; //XOR with 7	

	return y;
}


int main(void) {

	unsigned i = 19; // Initially set our unsigned integer

	unsigned y = perm(i); // Permutation call
	unsigned x = unperm(y); // Should == i;

	printf("Permutation of %i: %i \n", i, y);	
	printf("UnPermutation of %i: %i \n", y, x);

	return EXIT_SUCCESS;

}
