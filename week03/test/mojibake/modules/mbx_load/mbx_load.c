#include "mbx_load.h"
#define BYTE 8

bool mbx_load(mojibake_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;

    // void *table[TYPES_COUNT][ITEM_COUNT] = {
    //     {&magic[TYPE_ELF],NULL},
    // };



    void *partition = MOJIBAKE_BLOCK_OFFSET(target, index);
    unsigned int *magic_bytes = (unsigned int *)partition;
    // for (int i = 0 ; i < TYPES_COUNT; i++) {
    //     if(*magic_bytes == *(unsigned int *)table[i][MAGIC])
    //         printf("it's elf file");


    // printf("%02x\n", *magic_bytes);
    int reverse_magic_number = ((ELF_MAGIC & 0xFF) << (BYTE * 3) ) |
                               ((ELF_MAGIC & (0xFF << BYTE*3)) >> BYTE*3) |
                               ((ELF_MAGIC & (0xFF << BYTE*1)) << BYTE*1) | 
                               ((ELF_MAGIC & (0xFF << BYTE*2)) >> 8*1) ;
    // printf("%02x\n", x | y);
    // printf("%02x\n", y);

    // if(*magic_bytes == ELF_MAGIC)
    //     printf("it's elf file");

    // printf("%02x\n", *magic_bytes);
    // printf("%02x %02x\n", ELF_MAGIC, reverse_magic_number);
    if(*magic_bytes == ELF_MAGIC || *magic_bytes ==  reverse_magic_number )
        printf("it's elf file");


    // }
    return true;
}
