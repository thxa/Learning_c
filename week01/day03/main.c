#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int
main(int argc, char ** args)
{
     int value = 0x3e2f57bc;
     // 0xFF
         // 0xbc2f573e
         // 0xbc572f3e 
     const int BYTE_LENGTH = 8;
     int mask_1 = ((value & 0xff) << BYTE_LENGTH * 3);
     int mask_2 = (value & (0xff << BYTE_LENGTH * 3)) >> BYTE_LENGTH * 3;
     int mask_3 = (value & (0xff << BYTE_LENGTH * 1)) << BYTE_LENGTH * 1;
     int mask_4 = (value & (0xff << BYTE_LENGTH * 2)) >> BYTE_LENGTH * 1;
     value =  mask_1 | mask_2 | mask_3 | mask_4;
     printf("0x%x\n", value);
    return 0;
}
