/**
 * @file hw3_ctr.c
 * @author Ryan Kozak
 * @author #6016
 * @date 13 October 2018
 * @brief Encrypts or decrypts stdin to stdout
 *
 * Compile on Athena: gcc -std=c99 hw3_ctr.c ../hw2/hw2_P52.c
 *
 * Encrypt: ./a.out < plain.txt e password >> encrypt.txt
 * Decrypt ./a.out < encrypt.txt d password >> plain.txt
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONCE_LEN 12
#define BLK_LEN 48
#define KEY_LEN 48
#define CTR_LEN 36

void P52(unsigned s[12]);

unsigned int bI(unsigned int x) {
	return (((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) | ((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000));
}

int main(int argc, const char* argv[]) {
    size_t bytes_read;
    unsigned char key[KEY_LEN] = {0};  /* Auto init to all zeros */
    unsigned char nonce[NONCE_LEN];
    unsigned char blk[BLK_LEN];
    unsigned char ctr[CTR_LEN] = {0}; /* I put this here, not included in template */    
    unsigned char xblk[BLK_LEN] = {0}; /* I put this here, not included in template */

    /* Setup key and nonce. Report command line errors */
    if ((argc == 3) && (strlen(argv[1]) == 1) && (strlen(argv[2]) <= KEY_LEN) &&
        ((argv[1][0] == 'e') || (argv[1][0] == 'd'))) {
        if (argv[1][0] == 'e') {
            FILE *rand = fopen("/dev/urandom", "rb");
            fread(nonce, 1, NONCE_LEN, rand);
            fclose(rand);
            fwrite(nonce, 1, NONCE_LEN, stdout);
        } else {
            fread(nonce, 1, NONCE_LEN, stdin);
        }
        memcpy(key, argv[2], strlen(argv[2]));
    } else {
        fprintf(stderr, "usage: %s d|e <pwd up to 48 chars>\n", argv[0]);
        return EXIT_FAILURE;
    }

    do {

        bytes_read = fread(blk, 1, BLK_LEN, stdin);

        if (bytes_read > 0) {
            
           // (P52((Nonce + CTR) ^ key) ^ key) ^ blk;     	    
            memcpy(&xblk[0], &nonce[0], NONCE_LEN);
            memcpy(&xblk[12], &ctr[0], CTR_LEN);

            for(int c = 0; c < BLK_LEN; c++) {
                xblk[c] = xblk[c] ^ key[c];    // XOR (nonce+ctr) with key.
            }
            
            P52((unsigned *)xblk);
            
            for(int c = 0; c < BLK_LEN; c++) {
                xblk[c] = xblk[c] ^ key[c];  
            }
           
            for(int c = 0; c < BLK_LEN; c++) {
                blk[c] = xblk[c] ^ blk[c];
            }               
           
            //for(int c = 0; c < CTR_LEN; c++) {
            //    printf("%i", (int)ctr[c]);
            //}

            printf("\n");
            
            for(int c = CTR_LEN-1; c >= 0; c--) {
                if((int)ctr[c] < 255) {
                    ctr[c] = (unsigned char) ((int)ctr[c] + 1);
                    break;
                }
            }            

            fwrite(blk, 1, bytes_read, stdout); // Write block to file
            
        }

    } while (bytes_read == BLK_LEN);

    return EXIT_SUCCESS;

} 
