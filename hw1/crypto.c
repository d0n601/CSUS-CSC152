#include<stdio.h>
#include<stdlib.h>



unsigned perm(unsigned x) {

	unsigned lo = x & 0xffff;
	unsigned hi = x >> 16;

	lo = lo ^ (hi*hi); // bit-wise squared?
	hi = hi ^ (lo*lo); // and again...
	x = (hi << 16) | lo; // or statement...

	return x;
}

unsigned unperm(unsigned y) {

	unsigned lo = y & 0xfff;
	unsigned hi = y >> 16;

	y = (hi >> 16) | lo;
	hi = hi ^ (lo*lo);
	lo = lo ^ (hi*hi);

	return y;

}


int main(void) {

	unsigned i = 1776; // Initially set our unsigned integer
	
	unsigned y = perm(i); // Permutation call
	unsigned x = unperm(y); // We should get i back.

	if(x != i ) {
		printf("WARNING: Broken stuff...\n");
	}


	printf("Permutation %i: %i \n", i, y);	
	printf("UnPermutation %i: %i \n", y, x);

	return EXIT_SUCCESS;

}
