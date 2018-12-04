/**
 * @file hw5_siv.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 4 December 2018
 * 
 * @section DESCRIPTION
 * 
 * PCM-SIV (Poly-CTR-Mode-SIV).
 *   
 * @brief CSC 152 HW5 P1.
 *  
 * Compile via ECA Apollo: gcc hw5_siv.c hw5_lib.o -std=c99 -W -Wall -c
 *             
 */               


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Macros
#define VAL_1X     0xff
#define VAL_2X     VAL_1X,  VAL_1X
#define VAL_4X     VAL_2X,  VAL_2X
#define VAL_8X     VAL_4X,  VAL_4X
#define VAL_16X    VAL_8X,  VAL_8X
#define VAL_32X    VAL_16X, VAL_16X
#define VAL_64X    VAL_32X, VAL_32X


// Computes (key||0*) xor P52(in xor (key||0*)).
void P52_BC(unsigned kbytes, unsigned char key[kbytes],     // 16 or 32 only
            unsigned char in[48], unsigned char out[48]);   // in == out okay

// Encrypt p into c. Copy of iv gets 0* padded and big-endian incremented
void P52_CTR(unsigned kbytes, unsigned char key[kbytes],  // Upto 48 bytes
             unsigned ivbytes, unsigned char iv[ivbytes], // Upto 48 bytes
             unsigned inbytes, unsigned char in[inbytes], // in == out is okay
             unsigned char out[inbytes]);

// k and result are less than 2^61-1 and read and written as numbers.
// Result is approx (mbytes/2^63)-AU when k is random in [0,2^61-1)
__uint64_t poly61(unsigned char m[], unsigned mbytes, __uint64_t k);

// decrypt c into p. Return non-zero iff t authenticates p
int pcm_siv_decrypt(unsigned kbytes, unsigned char k[kbytes],  // 16 or 32
                    unsigned nbytes, unsigned char n[nbytes],  // 0 to 16
                    unsigned cbytes, unsigned char c[cbytes],
                    unsigned char p[cbytes], unsigned char t[16]);




// Encrypt p into c and write authentication tag to t.
void pcm_siv_encrypt( unsigned kbytes, unsigned char k[kbytes],
	              unsigned nbytes, unsigned char n[nbytes],
	              unsigned pbytes, unsigned char p[pbytes],
		      unsigned char c[pbytes], unsigned char t[16]) {

    __uint64_t hash1, hash2, hashKey1, hashKey2;
    unsigned char siv[48] = {0};
    unsigned char mask[48] = {VAL_32X,VAL_16X};
    unsigned char keys[48] = {VAL_32X,VAL_16X};

    P52_BC(kbytes, k, mask, keys);

    // Makes high 4 bits zero
    memcpy(&hashKey1, keys, 8);
    hashKey1 = hashKey1 >> 4;

    // Makes high 4 bits zero
    memcpy(&hashKey2, keys + 8, 8);
    hashKey2 = hashKey2 >> 4;

    // Hash twice to reduce collision probability
    hash1 = poly61(p,pbytes, hashKey1);
    // Hash twice to reduce collision probability
    hash2 = poly61(p,pbytes, hashKey2);

    // siv = P52-BC(k, hash1 || hash2 || nonce || 10*)
    memcpy(siv, &hash1, 8);
    memcpy(siv + 8, &hash2, 8);
    memcpy(siv + 16, n, nbytes);
    siv[16 + nbytes] = 0x80;
    P52_BC(kbytes, k, siv, siv);

    // SIV serves as auth tag
    memcpy(t, siv, 16);

    P52_CTR(kbytes, k, 16, t, pbytes, p, c);
    // Receiver needs (c, n, t) to decrypt
}
