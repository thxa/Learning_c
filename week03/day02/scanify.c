#include <string.h>
#include<stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <elf.h>

#define ELF_MAGIC 0x7F454C46
int reverse_magic_number = ((ELF_MAGIC & 0xFF) << (8 * 3) ) |  ((ELF_MAGIC & (0xFF << 8*3)) >> 8*3) | ((ELF_MAGIC & (0xFF << 8*1)) << 8*1) | ((ELF_MAGIC & (0xFF << 8*2)) >> 8*1) ;

typedef int (*func)(void*); 
typedef struct  {
    int depth;
    struct dirent* de;
} dedepth;

int scanify(char* path, unsigned int depth, func callback) {
    DIR *dr;
    struct dirent *de;
    dr = opendir(path); 
    while ((de = readdir(dr)) != NULL) {
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }
        char fullpath[1024], stylePath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, de->d_name);
        dedepth d = {depth, de};
        callback(&d);
        if(de->d_type == DT_DIR){
            scanify(fullpath, depth+1, callback);
        }
    }
    closedir(dr);
    return 0;
}


int print(void*x){
    dedepth* d = (dedepth*) x;

    FILE *fp = fopen(d ->de ->d_name, "rb");

    // fread(void *, unsigned long, 10, fp);

    if(d->depth == 0) {
        printf("\033[20m📁%s\033[0m\n", d->de->d_name);
        return 0;
    }

    if(d -> de -> d_type == DT_REG ) {
        printf("|");
        for(int i=0; i< d -> depth; i++) {
            printf("-");
        }
        printf("\033[36m🗎%s\033[0m\n", d -> de->d_name); 
    }

    if(d -> de -> d_type == DT_DIR){
        for(int i=0; i<d->depth; i++) {
            printf(" ");
        }
        printf("\033[32m📁%s\033[0m\n", d -> de->d_name); 
    }

    return 0;
}

int
main(int argc, char ** args)
{
    scanify("../", 0, print);
   return 0;
}
