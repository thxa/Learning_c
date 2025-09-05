#include<stdio.h>
#include <stdlib.h>
int
main(int argc, char ** args)
{
    if(argc != 3) {
        printf("usage: %s [file] [key]\n", args[0]);
        return 0;
    }

    FILE* fp = fopen(args[1], "r");
    if(fp) {

        unsigned int key = atoi(args[2]);
        int x = 0;
        while((x = fgetc(fp)) != EOF) {
            printf("%c", ((unsigned char)x ^ key));
        }
    } else {
        fprintf(stderr, "ERROR: Invalid file path\n");
        return 1;
    }

   return 0;
}
