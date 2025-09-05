#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int
main(int argc, char ** args)
{
    unsigned char block[1024];

    // *(block + 1) = 'C';
    // *(block + 1) = 'C';

    // one
    // 29

    *(block + 29) = 'C';
    printf("[%p] -> %c\n", (block + 29), *(block + 29));
    // two
    // 35 and 35+1
    
    *(block + 35) = 'A';
    *(block + 35+1) = 'X';

    printf("[%p] -> %c\n", (block + 35), *(block + 35));
    printf("[%p] -> %c\n", (block + 35 + 1), *(block + 35 + 1));

    // three
    // 60 and 60-1
    *(block + 60) = 'F';
    *(block + 60-1) = 'B';
    printf("[%p] -> %c\n", (block + 60), *(block + 60));
    printf("[%p] -> %c\n", (block + 60 + 1), *(block + 60 - 1));



    // four
    // 70 -1 and 70 and 70 + 1
    *(block + 70) = 'J';
    *(block + 70-1) = 'K';
    *(block + 70+1) = 'H';
    printf("[%p] -> %c\n", (block + 70),*(block + 70));
    printf("[%p] -> %c\n", (block + 70 -1) ,*(block + 70-1));
    printf("[%p] -> %c\n", (block + 70 +1) ,*(block + 70+1));



    unsigned char *base_ptr = block;

    printf("[%p] -> %c\n", base_ptr, *base_ptr);
    



   return 0;
}
