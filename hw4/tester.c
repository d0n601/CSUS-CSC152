#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes);


int main() {

    unsigned char res1[5];
    unsigned char buf1[] = {0x0a, 0xc3, 0x19, 0x34};

    P52_hash(buf1, sizeof(buf1), res1, sizeof(res1));
  
    for(int c = 0; c < sizeof(res1); c++){
        printf("%x", res1[c]);
    }
    printf("\n");

}


