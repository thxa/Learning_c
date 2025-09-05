#include<stdio.h>

typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned short c;
    unsigned int d;
} node;

int
main(int argc, char ** args)
{
    // fread(void *, unsigned long, unsigned long, FILE *)
    // block length 512
    unsigned char block[512];

    unsigned char *ptr_char = block;
    unsigned short *ptr_short = ((unsigned short*)block) + 16;
    unsigned int *ptr_int = (unsigned int*)block+8+8;
    node *ptr_node = (node*)block+8+4;


    printf("[%p] -> %x\n", ptr_char, *ptr_char);
    printf("[%p] -> %x\n", ptr_short, *ptr_short);
    printf("[%p] -> %x\n", ptr_int, *ptr_int);
    printf("[%p] -> %x\n", ptr_node, *ptr_node);
    // ptr_grid 
    // ptr_node -> size= 5;
    // ptr_node -> data = block - node -> size; 
    //
    // ptr_node -> a = 1;
    // ptr_node -> b = 2;
    // ptr_node -> c = 3;

    // printf("[%p] -> %x\n", &ptr_node -> a, ptr_node -> a);
    // printf("[%p] -> %x\n", &ptr_node -> b, ptr_node -> b);



    printf("[1 bytes buffer]\n");
    unsigned char c = 'A';
    for (unsigned char* i=ptr_char; i < (unsigned char*)ptr_short; i++) {
        if(c > 'Z') c = 'A';
        *i = c;
        c++;
    }

    for (unsigned char* i=ptr_char; i < (unsigned char*)ptr_short; i++) {
        printf("[%p] -> %c\n", i, *i);
    }

    printf("[2 bytes buffer]\n");
    unsigned short x = 1;
    for (unsigned short* i=ptr_short; i < (unsigned short*)ptr_int; i++) {
        *i = x;
        x++;
    }

    for (unsigned short* i=ptr_short; i < (unsigned short*)ptr_int; i++) {
        printf("[%p] -> %d\n", i, *i);
    }
    

    printf("[4 bytes buffer]\n");
    unsigned int y = 1;
    for (unsigned int* i=ptr_int; i < (unsigned int*)ptr_node; i++) {
        *i = x;
        x++;
    }

    for (unsigned int* i=ptr_int; i < (unsigned int*)ptr_node; i++) {
        printf("[%p] -> %d\n", i, *i);
    }
    

    printf("[8 bytes buffer]\n");
    unsigned char a = 'A';
    unsigned char b = 'a';
    unsigned short c_ = 0;
    unsigned int d = 0;

    for (node* i=ptr_node; i < ptr_node + 52 ; i++) {
        if(a > 'Z') a = 'A';
        if(b > 'z') b = 'a';
        i -> a = a;
        i -> b = b;
        i -> c = c_;
        i -> d= d;
        a++, b++, c_++, d+=2;
    }

    for (node* i=ptr_node; i < ptr_node + 52; i++) {
        printf("[%p]\n", i);
        // printf("[%p] -> %c\n", &(i -> a), i -> a);
        // printf("[%p] -> %c\n", &(i -> b), i -> b);
        // printf("[%p] -> %d\n", &(i -> c), i -> c);
        // printf("[%p] -> %d\n", &(i -> d), i -> d);
    }
    

    // printf("%d\n", (sizeof(block) / sizeof(char)));
    // printf("%p\n", base_block);
       // base_block
    // ptr char
    
    // const unsigned char CHAR_LENGTH = 28 * sizeof(unsigned char);
    // const unsigned char SHORT_LENGTH = 14 * sizeof(unsigned short);
    // const unsigned char INT_LENGTH =  6 * sizeof(unsigned int);

    // + (sizeof(unsigned char) * CHAR_LENGTH)
    // printf("%p\n", (block+(sizeof(block) / sizeof(char))));
    // printf("%p\n", (block+(sizeof(block) / sizeof(unsigned short))));

    // unsigned char c = 'A';
    // for (unsigned char* i=block; i< block+(sizeof(block) / sizeof(char)); i++) {
    // for (unsigned char* i=block; i< block+(sizeof(char) * CHAR_LENGTH); i++) {
    //     if(c > 'Z') c = 'A';
    //     *i = c;
    //     c++;
    // }

    // for( int i =0; i < sizeof(block)/sizeof(char); i++) 
    // {
    //     printf("[%p] -> %c\n", &block[i], block[i]);
    // }

    // for (unsigned char* i=block; i< block+ (sizeof(unsigned char) * CHAR_LENGTH); i+= sizeof(unsigned char)) {
    //     printf("[%p] -> %c\n", i, *i);
    // }


    // ptr short
     // unsigned short s = 0;
    // for (unsigned short* i = (unsigned short*) (block + CHAR_LENGTH) ; i < (block + SHORT_LENGTH) ; i+= sizeof(unsigned short)) {
     //    *i = s;
     //    s++;
    // }
    // printf("[%p] -> %x\n", block, *((unsigned char*)block));
    // printf("[%p] -> %x\n", block, *((unsigned short*)block));
    // printf("[%p] -> %x\n", block, *((unsigned int*)block));

    // printf("[%p] -> %d\n", );

    // for( int i =0; i < sizeof(block)/sizeof(char); i++) 
    // {
    //     printf("[%p] -> %c\n", &block[i], block[i]);
    // }

    // for (unsigned char* i=block; i< block+ (sizeof(char) * CHAR_LENGTH); i+= sizeof(char)) {
    //     printf("[%p] -> %c\n", i, *i);
    // }

   

    // ptr int
    // ptr struct any
 
    // move by char, short, int, struct 
    // move by struct, x,y 
   return 0;
}
