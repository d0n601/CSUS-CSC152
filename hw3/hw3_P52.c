/**
 * @file hw3_P52.c
 * @author  Ryan Kozak <ryankozak@csus.edu>
 * @author #6016
 * @date 12 Oct 2018
 *
 * @section DESCRIPTION
 *
 * Rewrite of hw2's P52 code to use SSE intrinsics processing all four columns at once.
 *
 * @brief CSC 152 HW3 P52.
 *
 * Compile: gcc hw3_P52.c -std=c99 -W -Wall -pedantic -c -msse2
 *
 */

#include <stdio.h>
#include <string.h>
#include <emmintrin.h>

void P52(unsigned s[12]) {

    __m128i r0, r1, r2, x, y, z;

    for(int i = 0; i < 24; i++) {

        /* Load rows into registers */
        r0 = _mm_loadu_si128 ((__m128i *)&s[0]);
        r1 = _mm_loadu_si128 ((__m128i *)&s[4]);
        r2 = _mm_loadu_si128 ((__m128i *)&s[8]);

        /* Execute operations and save into x, y and z */
        x =  _mm_or_si128 ( _mm_slli_epi32 (r0, 24), _mm_srli_epi32 (r0, 8));
        y =  _mm_or_si128 ( _mm_slli_epi32 (r1, 9), _mm_srli_epi32 (r1, 23));
        z =  r2;

        /* More operations saving back into the rows */
        r2 = _mm_xor_si128 (_mm_xor_si128 (x, _mm_slli_epi32 (z, 1)), _mm_slli_epi32 (_mm_and_si128 (y, z), 2));
        r1 = _mm_xor_si128(_mm_xor_si128(y,x),  _mm_slli_epi32( _mm_or_si128(x,z), 1));
        r0 = _mm_xor_si128( _mm_xor_si128(z,y) , _mm_slli_epi32(_mm_and_si128(x,y), 3));

        /* Store bottom two rows */
        _mm_storeu_si128 ((__m128i *)&s[8], r2);
        _mm_storeu_si128 ((__m128i *)&s[4], r1);

        /*  Mix columns.
         * 2D representation (s[0,0], s[0,1], s[0,2], s[0,3]) = (s[0,1], s[0,0], s[0,3], s[0,2])
         */
        if ( (i % 4) == 0) {
            _mm_storeu_si128 ((__m128i *)&s[0],  _mm_shuffle_epi32 (r0, 177));
            s[0] = s[0] ^ 0x9e377900 ^ (24 - i); // s[0,0] = s[0,0] xor 0x9e377900 xor (24-i)
        }

        /* Mix columns differently.
         * 2D representation (s[0,0], s[0,1], s[0,2], s[0,3]) = (s[0,2], s[0,3], s[0,0], s[0,1])
         */
        else if ( (i % 4) == 2) {
            _mm_storeu_si128 ((__m128i *)&s[0],  _mm_shuffle_epi32 (r0, 78));
        }
        else {
            _mm_storeu_si128 ((__m128i *)&s[0], r0);
        }
    }

}
