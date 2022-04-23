#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_url[] = "https://leetcode.com/problems/design-tinyurl";

char key[] = {0x07, 0x02, 0x04, 0x04, 0x03, 0x07, 0x02};
#define KEY_LEN   sizeof(key)

/** Encodes a URL to a shortened URL. */
char *encode(char *longUrl) {
    for(int i=0;i<strlen(longUrl);i++) {
        longUrl[i] ^= key[i%KEY_LEN];
    }

    return longUrl;
}

/** Decodes a shortened URL to its original URL. */
char *decode(char *shortUrl) {
    for(int i=0;i<strlen(shortUrl);i++) {
        shortUrl[i] ^= key[i%KEY_LEN];
    }

    return shortUrl;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("URL    : %s\n", test_url);
    char *encode_url = encode(test_url);
    printf("Encode : %s\n", encode_url);
    char *decode_url = decode(encode_url);
    printf("Decode : %s\n", decode_url);


}

