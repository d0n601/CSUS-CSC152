/**
 * @file hw4_P52_hash.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 27 Oct 2018
 * 
 * @section DESCRIPTION
 * 
 * A sponge-based cryptographic hash using P52. We’ll call it P52-Hash. Our sponge 
 * has capacity 32 bytes, rate 16 bytes, and a specifiable number of output bytes. Hash inputs use
 * 10*1 padding.
 *  
 * @brief CSC 152 HW4 P1.
 * 
 * Compile: gcc hw4_P52_hash.c -std=c99 -W -Wall -pedantic -c
 *
 */


#include<stdio.h>
#include <string.h>


void P52(unsigned s[12]);

void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes) {
    
    unsigned p; // Bytes left to process
    unsigned char m_block[16] = {0}; // Message block
    unsigned char spongy[48] = {0}; // 48 byte Sponge

    unsigned c = 0;  // Count bytes absorbed

    while( c <= mbytes) { // While we haven't absorbed all the bytes
     
        p = mbytes - c; // Bytes left to process.
        
        // Handle padding that we can fit in the same block
        if(p <= 14) {
            memcpy(&m_block[0], &m[c], p);  // Only copy size of input.
            m_block[p] = 0x80;
            for(int i = p+1; i < 15; i++) {
                m_block[i] = 0x00;
            }
            m_block[15] = 0x01;
            c++; // break out of loop.
        }
        // Handle padding of the same block with no zero.
        else if(p == 15 ) {
           memcpy(&m_block[0], &m[c], p);
           m_block[15] = 0x81;
           c++;
        }
        // Unpadded block, full 16 bytes are message.
        else {
            memcpy(&m_block[0], &m[c], 16); // 16 bytes of message
        }
        
        // Xor the block with the rate
        for(int i = 0; i < 16; i++) {
            spongy[i] = spongy[i] ^ m_block[i]; // Xor 16 bits of 
        }
    
        P52((unsigned *)spongy); // P52 permutation
    
        c+=16; // advance pointer 16 bytes.
    
    }

    // Sponge squeeze
    c = 0;
    while(c < rbytes) {
        int d = rbytes - c;
        if(d < 16) {
            memcpy(&res[c], &spongy[0], d);
            break;
        }
        else {
            memcpy(&res[c], &spongy[0], 16);
        }
        c+=16;
        P52((unsigned *)spongy);
    }
}
