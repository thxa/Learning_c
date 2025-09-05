#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include <stdarg.h>

enum week{  
    SUN, 
    MON,
    TUS,
};

void printInt(int cnt, ...) {
    va_list args;
    va_start(args, cnt);
    for (int i=0;i<cnt;i++) {
        int val = va_arg(args, int);
        printf("%d", val);
    }
    va_end(args);
    printf("\n");
}


// void printIntX(int cnt, ...) {
//     // va_list args;
//     // va_start(args, cnt);
//     int* x = &cnt;
//     // x++;
//     for (int i=0;i<cnt;i++) {
//         // int val = va_arg(args, int);
//         printf("%d", *(x+i));
//     }
//     // va_end(args);
//     printf("\n");
// }




int
main(int argc, char ** args)
{

    printInt(3, SUN, 2, 3);
    printInt(3, SUN, MON, TUS);
    // printIntX(3, SUN, 2, 3);



   return 0;
}
