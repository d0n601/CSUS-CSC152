#include<stdio.h>
#include <string.h>


void P52(unsigned s[12]);

void P52_hash(unsigned char m[], unsigned mbytes, unsigned char res[], unsigned rbytes) {
    
    int p; // Bytes left to process
    unsigned char m_block[16] = {0}; // Message block
    unsigned char spongy[48] = {0}; // 48 byte Sponge

    int c = 0;  // Count bytes absorbed

    while( c < mbytes) { // While we haven't absorbed all the bytes

         if(sizeof(m) < 16) {
             memcpy(&m_block[0], &m[c], sizeof(m));  // Only copy size of input.
         }
         else {
             memcpy(&m_block[0], &m[c], 16); // 16 bytes of message
         }
        
         p = mbytes - c; // Bytes left to process 16 bytes

         if(p < 16) {  // If we have under 16 bytes left to process, pad the block.

             m_block[p] = 0x80; // First byte of 10*1 padding

             for(int i = p+1; i < 15; i++) {
                m_block[i] = 0x00; // Additional 0* bytes of 10*1 padding
             }

             m_block[15] = 0x01; // Last byte of 10*1 padding

         }

        // If it's exactly 16 bytes, also add another block !!!!

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
     
        if(d <= 16) {
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

int main() {

    unsigned char buf1[] = {0x12, 0x17, 0xf3};
    unsigned char buf2[] = {0x0a, 0xc3, 0x19, 0x34};
    unsigned char res1[5], res2[5];
   
    P52_hash(buf1, sizeof(buf1), res1, sizeof(res1));
    P52_hash(buf2, sizeof(buf2), res2, sizeof(res2));

    for(int c = 0; c < 5; c++) {
        printf("%02x", res1[c]);
    } 
 
    printf("\n");

    for(int c = 0; c < 5; c++) {
        printf("%02x", res2[c]);
    }

    printf("\n");
   
}
