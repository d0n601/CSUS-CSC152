#include <stdio.h>
#include <stdlib.h>

// Prof. Krovetz's P52_hash function
void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes);

// My P52_hash function
void myP52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes);


// Prints buffers for comparison
void printBuffer(unsigned char b[], unsigned bbytes) { 
   for(int c = 0; c < bbytes; c++) {
        printf("%02x", b[c]);
    }
    printf("\n");
}


// Compare our hash function outputs.
int main() {

    unsigned char buf1[] = {0x12, 0x17, 0xf3}; // Short
    unsigned char buf2[] = {0x0a, 0xc3, 0x19, 0x34}; // Shorter
    unsigned char buf3[] = {0x12, 0x17, 0xf3, 0x55, 0x71,0x12, 0x17, 0xf3, 0x55, 0x71,0x12, 0x17, 0xf3, 0x55}; // 14 bytes
    unsigned char buf4[] = {0x12, 0x17, 0xf3, 0x55, 0x71,0x12, 0x17, 0xf3, 0x55, 0x71,0x12, 0x17, 0xf3, 0x55, 0x71}; // 15 bytes
    unsigned char buf5[] = {0x12, 0x17, 0xf3, 0x55, 0x71,0x12, 0x17, 0xf3, 0x55, 0x71,0x12, 0x17, 0xf3, 0x55, 0x71, 0xff}; // 16 bytes
    unsigned char buf6[51] = {0xff}; // 51 bytes
    unsigned char res1[31], res2[31], res3[31], res4[31], res5[31], res6[31], res7[31], res8[31], res9[31], res10[31], res11[31], res12[31];

    P52_hash(buf1, sizeof(buf1), res1, sizeof(res1));
    P52_hash(buf2, sizeof(buf2), res2, sizeof(res2));
    P52_hash(buf3, sizeof(buf3), res5, sizeof(res5));
    P52_hash(buf4, sizeof(buf4), res7, sizeof(res7));
    P52_hash(buf5, sizeof(buf5), res9, sizeof(res9));
    P52_hash(buf6, sizeof(buf6), res11, sizeof(res11));

    myP52_hash(buf1, sizeof(buf1), res3, sizeof(res3));
    myP52_hash(buf2, sizeof(buf2), res4, sizeof(res4));
    myP52_hash(buf3, sizeof(buf3), res6, sizeof(res6));
    myP52_hash(buf4, sizeof(buf4), res8, sizeof(res8));
    myP52_hash(buf5, sizeof(buf5), res10, sizeof(res10));
    myP52_hash(buf6, sizeof(buf6), res12, sizeof(res12));


    printf("\n");

    printBuffer(&res1[0], sizeof(res1));
    printBuffer(&res3[0], sizeof(res3));
    
    printf("\n");
   
    printBuffer(&res2[0], sizeof(res2));
    printBuffer(&res4[0], sizeof(res4));
 
    printf("\n"); 
   
    printBuffer(&res5[0], sizeof(res5));
    printBuffer(&res6[0], sizeof(res6));

    printf("\n");

    printBuffer(&res7[0], sizeof(res7));
    printBuffer(&res8[0], sizeof(res8));
  
    printf("\n");

    printBuffer(&res9[0], sizeof(res9));
    printBuffer(&res10[0], sizeof(res10));

    printf("\n");

    printBuffer(&res11[0], sizeof(res11));
    printBuffer(&res12[0], sizeof(res12));



}
