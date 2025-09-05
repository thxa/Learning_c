#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int
main(int argc, char ** args)
{
    unsigned short values[5];
    printf("%p\n", values);
    printf("%p\n", &values);

    // printf("%d\n", sizeof values / sizeof(short));
     // for (int i =-1; i < sizeof values; i++) {
     //     printf("5: %p\n", &values[i]);
     // }
    

    printf("1: %p\n", &values[0]);
    printf("2: %p\n", &values[1]);
    printf("3: %p\n", &values[2]);
    printf("4: %p\n", &values[3]);
    // printf("4: %p\n", values + 3);
    // printf("4: %p\n", &values + 3 );
    printf("5: %p\n", &values[4]);

    return 0;
}
