#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/**
 * This is the solution to question 5.
 */
int * createRandomPermutation(int n) {
    
    srand(time(NULL));

    int *randomArray = malloc(n); // Allocate memory pointer for array	

    // Fill the array initially
    for(int c = 0; c < n; c++) {
        randomArray[c] = c;
    }

    // Swap random elements in the array
    for(int c = 0; c < n; c++) {
        int x = rand() % n;  // First position
        int y = rand() % n; // Second position
        int temp = randomArray[x]; // save first position
        randomArray[x] = randomArray[y]; // put second in first
        randomArray[y] = temp; // put first in second   
    }
    
    return randomArray;
}


/**
 * Caller function to test createRandomPermutation
 */
int main(void) {

    int *a = createRandomPermutation(10);

    for(int c = 0; c < 10; c++) {
        printf("a[%i]=%i\n",c , a[c]);
    }

    return EXIT_SUCCESS;
}
