#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>

#define ENC_DEFAULT_CHUNK_FILE 8
/*
 * 1. read file
 */ 
typedef struct{
    unsigned int size;
    unsigned int extra;
    unsigned int partition_size;
    unsigned int partition_count;
    void* block;
} enc_file_t;

typedef struct{
    unsigned int size;
    void* block;
} enc_partition_file_t;


enc_file_t *enc_read_file(char *file_path, int num_chunk)
{
    
    if(file_path == NULL) {
        return NULL;
    }
    enc_file_t *file = NULL;
    struct stat info;

    if(stat(file_path, &info) != 0) {
        return NULL;
    }

    FILE *fp = fopen(file_path, "rb");
    if(fp == NULL) {
        return NULL;
    }

    file = (enc_file_t*)malloc(sizeof(enc_file_t));
    if(file == NULL) {
        fclose(fp);
        return NULL;
    }
    file -> size = info.st_size;

    if(file -> size % num_chunk > 0) {
        file -> extra = file -> size % num_chunk;
    }

    file -> block = malloc(sizeof(file -> size));
    if(file -> block == NULL) {
        free(file);
        fclose(fp);
        return NULL;
    }
    unsigned int read = fread(file -> block, file->size, 1, fp);
    // printf("%d\n", read);
    // if(read == 0) {
    //     fclose(fp);
    // }
    return file;
}

enc_partition_file_t *enc_chunk_file(enc_file_t* file) {
    return NULL;
}


int *enc_close_file(enc_file_t* file) {
    if(file == NULL) {
        return NULL;
    }
    if(file -> block == NULL) {
        file -> size = 0;
        free(file);
        file = NULL;
        return NULL;
    }

    free(file -> block);
    file -> size = 0;
    free(file);
    file = NULL;
    return NULL;
}


/*
 * 2. set pointers
 */ 


/*
 * 3. Define Equation
 */

/* 4. Define Keys
 * 5. Enc
 * 6. ReAringe
 */


int
main(int argc, char ** args)
{
    enc_file_t* file = enc_read_file("enc.c", ENC_DEFAULT_CHUNK_FILE);
    
    printf("%d\n", file -> size);
    char* ptr = (char*) file ->block;
    for (int i=0; i< file -> size; i++) {
        printf("%c", ptr[i]);
    }
    
    enc_close_file(file);

   return 0;
}
