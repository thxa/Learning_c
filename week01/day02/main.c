#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void example_1() {

    unsigned char value = 'T';
    value = value | (1 << 5) | (1 << 1);
    printf("%c\n", value);
   
}

void example_2() {
    unsigned char value = 'O';
    unsigned char mask_1 = ~(1);
    unsigned char mask_2 = ~(1 << 2);
    value = value & mask_1 & mask_2;
    printf("%c\n", value);
    printf("%d\n", value);
}


void example_3() {

    unsigned short value = 0;
    value = (0b1010);
    value <<= 4;
    value |=  (0b0100);
    value <<= 4;
    value |=  (0b0010);
    value <<= 4;
    printf("%032b\n", value);

}

void example_8() {
    unsigned int value = 0x3f2b6d4e;
    value &= ~(0xf << 24);  
    value |= (0xb << 24);  
    
    value &= ~(0x2 << 20);  
    value |= (0x5 << 20);  
    
    value &= ~(0xb << 16);  
    value |= (0x7 << 16);  
    
    value &= ~(0x6 << 12);
    value |= (0x8 << 12);  

    value &= ~(0xd << 8);
    value |= (0xa << 8);  

    value &= ~(0x4 << 4);
    value |= (0x6 << 4);  

    value &= ~(0xe << 0);
    value |= (0xc << 0);  

    printf("0x%x\n", value);

    value = 0x3f2b6d4e;
    value &= ~(0xf2b6d4e);
    value |= 0x3b578a6c;
    printf("0x%x\n", value);
    // 0x3b578a6c
}

void project() {

    unsigned char val0 = 'A';
    unsigned char val1 = 'B';
    unsigned char val2 = 'C';
    unsigned char val3 = 'D';
    unsigned int result = 0;
    result |= val0;
    result <<= 8;
    result |= val1;
    result <<= 8;
    result |= val2;
    result <<= 8;
    result |= val3;


//     while(result) {
//         printf("%c", result & 0xFF);
//         result >>= 8;
//     }
//     ptintf('\n');

    for(int i = 3; i >=0 ; i--) {
        printf("%c", (result & (0xFF << (8*i) )) >> (8*i) );
    }
    printf("\n");

    printf("%c", ((result & (0xFF << 24)) >> 24));
    printf("%c", ((result & (0xFF << 16)) >> 16));
    printf("%c", ((result & (0xFF << 8)) >> 8));
    printf("%c", ((result & (0xFF << 0)) >> 0));


}




#include<stdio.h>
int
main(int argc, char ** args)
{
    // example_1();                   
    // example_2();                   
    // example_3();                   
    // example_8();                   
    // project();
    //
    // printf("%d\n", result);
    
    return 0;
}
