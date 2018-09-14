#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/**
 * Solution to question 4.
 */
int * createRandomFunction(int n) {
	
    srand(time(NULL));

    int *randomArray = malloc(n); // Allocate memory pointer for array	

        for(int c = 0; c < n; c++) {
            randomArray[c] = rand() % n; // Random int between 0 and n
        }

    return randomArray;
}


/**
 * Caller function to test crateRandomFunction
 */
int main(void) {

    int *a = createRandomFunction(10);

    for(int c = 0; c < 10; c++) {
        printf("a[%i]=%i\n",c , a[c]);
    }

    return EXIT_SUCCESS;
}
