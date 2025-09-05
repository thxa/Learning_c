#ifndef MBX_LOAD_H
#define MBX_LOAD_H
#include <stdbool.h>

#include "../../mojibake.h"
bool mbx_load(mojibake_target_t *target, unsigned int index, void *arg);

#define ELF_MAGIC 0x7F454C46
// #define ELF_MAGIC 0x464c457f

 
// static unsigned int magic[] = {
 //    0x7f454d46, // elf
 //    // 0x464c457f

// };

// static void *table[TYPES_COUNT][ITEM_COUNT] = {
 //    {&magic[TYPE_ELF],NULL},
// };
#endif
