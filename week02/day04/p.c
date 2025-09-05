#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int character_counts(char *value, char c) {
    int cnt=0;
    for(;*value != '\0'; value++) {
        if(c == *value) {
            cnt++;
        }
    }
    return cnt;
}


    int
main(int argc, char ** args)
{
    char source[] = "Hello, world!";
    // char *p = source;
    // for (char *p = source + 7;;) {
    //     if(*(p+1) == '\0') break;
    //     *p = *p - 32;
    //     p++;
    // }

    char *l = source, *r = source + 4;
    while(l <= r) {
        char tmp = *l;
        tmp = *l;
        *l = *r;
        *r =  tmp;

        // *l = *l ^ *r;
        // *l = *r ^ *l;
        // *r = *r ^ *l;
        // *r ^= *l ^ *r;
        r--, l++;
    }

    l = source+7; 
    r = source + 11;
    while(l <= r) {
        char tmp = *l;
        tmp = *l;
        *l = *r;
        *r =  tmp;
        r--, l++;
    }
    printf("%s\n", source);

    printf("%d\n", character_counts("Welcome to C Language", 'a'));


   return 0;
}
