/**
 * @file hw4_collision.c
 * @author Ryan Kozak
 * @author #6016
 * @date 27 October 2018
 *
 */


#include <stdio.h>
#include <string.h>
#define SZ 2

void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes);

int main() {
    
    unsigned char buf1[] = {0x3F};
    unsigned char buf2[] = {0x65};
    unsigned char res1[SZ], res2[SZ];
    
    P52_hash(buf1, sizeof(buf1), res1, sizeof(res1));
    P52_hash(buf2, sizeof(buf2), res2, sizeof(res2));
  
    if (memcmp(res1,res2,SZ)==0) {
        printf("%d-byte Collision\n", SZ);
    }
}
