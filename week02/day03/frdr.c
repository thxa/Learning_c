#include<stdio.h>
int
main(int argc, char ** args)
{
    /*
     * file -> [xor [any number]] -> 
     */

    if(argc != 2) {
        printf("usage: %s file path\n", args[0]);
        return 0;
    }

    FILE* fp = fopen(args[1], "r");
    if(fp) {

        printf("File Reader Tool\n");
        int x = 0;
        while((x = fgetc(fp)) != EOF) {
            printf("%c", ((unsigned char)x));

        }
        printf("\n");
        fclose(fp);
    } else {
        fprintf(stderr, "ERROR: Invalid file path\n");
        return 1;
    }

   return 0;
}
