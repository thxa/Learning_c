/* Mojibake 1.0.0a */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define CRAFT_VERSION 1

#define CRAFT_DEFAULT_PARTITION_COUNT 8
#define CRAFT_MAX_FILE_SIZE 1024 * 1024 * 4
#define RETURN_NULL_IF(con) \
    if ((con))              \
    {                       \
        return NULL;        \
    }

#define CRAFT_BASE_OFFSET(b, i, sf) (b) + ((i) * (sf))
#define CRAFT_BLOCK_OFFSET(t, i) CRAFT_BASE_OFFSET(((t)->block), (i), ((t)->partition_size))

typedef struct craft_target_t craft_target_t;
typedef struct craft_partition_t craft_partition_t;

typedef bool (*partition_callback_t)(craft_target_t *, unsigned int index, void *arg);

struct craft_partition_t
{
    unsigned int index;
};

struct craft_target_t
{
    unsigned int version;
    unsigned int partition_size;
    unsigned int partition_count;
    unsigned int extra;
    unsigned int size;
    void *block;
    craft_partition_t *partitions;
};

#define CRAFT_PARTITION_TYPE_X 0
#define CRAFT_PARTITION_TYPE_Y 1
#define CRAFT_PARTITION_TYPE_Z 2

craft_partition_t *craft_partitionize(craft_target_t *target)
{
    assert(target != NULL);
    assert(target->partition_size > 0);
    assert(target->partition_count > 0);

    craft_partition_t *partitions = (craft_partition_t *)
        malloc(sizeof(craft_partition_t) * target->partition_count);
    RETURN_NULL_IF(partitions == NULL);

    for (int i = 0; i < target->partition_count; i++)
        partitions[i].index = i;

    return partitions;
}

void craft_departitionize(craft_partition_t *partitions)
{
    if (partitions)
        free(partitions);
}

craft_target_t *craft_open(char *file_path, unsigned int partition_count)
{
    craft_target_t *target = NULL;

    struct stat info;
    unsigned int tmp_partition_count = partition_count;
    unsigned int read;
    FILE *handler = NULL;

    RETURN_NULL_IF(file_path == NULL)

    if (partition_count == 0)
        tmp_partition_count = CRAFT_DEFAULT_PARTITION_COUNT;

    RETURN_NULL_IF(stat(file_path, &info) != 0)
    RETURN_NULL_IF((info.st_size == 0) || (info.st_size > CRAFT_MAX_FILE_SIZE))

    handler = fopen(file_path, "rb");
    RETURN_NULL_IF(handler == NULL)

    target = (craft_target_t *)malloc(sizeof(craft_target_t));
    if (target == NULL)
    {
        fclose(handler);
        return NULL;
    }

    target->size = info.st_size;
    target->partition_count = tmp_partition_count;
    target->extra = target->size % target->partition_count;

    if (target->extra > 0)
        target->partition_size = (target->size - target->extra) / target->partition_count;
    else
        target->partition_size = (target->size / target->partition_count);

    target->block = malloc(target->size);
    if (target->block == NULL)
    {
        free(target);
        fclose(handler);
        return NULL;
    }

    read = fread(target->block,
                 target->size, 1, handler);
    // TODO: read condition
    fclose(handler);

    target->version = CRAFT_VERSION;
    target->partitions = craft_partitionize(target);

    return target;
}

void craft_close(craft_target_t *target)
{
    if (target)
    {
        target->size = 0;
        target->extra = 0;
        target->partition_count = 0;
        target->partition_size = 0;
        target->version = 0;

        craft_departitionize(target->partitions);

        if (target->block)
            free(target->block);

        free(target);
    }
}

void craft_print(craft_target_t *target)
{
    if (target == NULL)
        return;

    char *ptr = (char *)target->block;
    printf("block-size: %u\n", target->size);
    printf("block-address: %p\n", target->block);
    printf("partition-count: %u\n", target->partition_count);
    printf("partition-size: %u\n", target->partition_size);
    printf("partition-extra: %u\n", target->extra);
    printf("\n\n");

    for (int i = 0; i < target->size; i++)
        printf("%02x", ptr[i]);
    printf("\n\n");

    printf("partitions:\n");
    for (int i = 0; i < target->partition_count; i++)
    {
        printf("[%d] -> %p\n", target->partitions[i].index,
               target->block + (target->partitions[i].index * target->partition_size));
    }
}

bool xcraft_enc(craft_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;

    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);
    for (int i = 0; i < target->partition_size; i++)
        partition[i] = partition[i] << 1;
    return true;
}


bool xcraft_enc_xor(craft_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;

    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);
    for (int i = 0; i < target->partition_size; i++)
        partition[i] = partition[i] ^ 5;
    return true;
}


struct se_data {
    char start;
    char end;
};


bool xcraft_x(craft_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;
    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);
    // for (int i = 0; i < target->partition_size; i++)
    //     partition[i] = partition[i] ^ 5;
    printf("%02x", partition[0]);
    printf("%02x\n", partition[target->partition_size-1]);
    return true;
}




bool xcraft_enc_color(craft_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;

    struct se_data *data = (struct se_data*) arg;

    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);
    printf("%c\n", data ->start);

    printf("\033[3%dm", index % 7);
    printf("|");
    int size = 30;
    for(int i=0; i< size; i++) {
        printf("-");
    }

    int cnt = 0;
    for (int i = 0; i < target->partition_size/2; i++){
        cnt = i % size;
        if(cnt == 0){
            printf("|\n");
            printf("|");
        }
        printf(".");
    }
    // printf("%d", cnt);
    for(int i=cnt; i<size-1; i++) {
        printf(".");
    }
    printf("|\n");

    // printf("%-10s\n"," ");
    printf("|");
    for(int i=0; i<(size/2) - 5; i++) {
        printf(".");
    }

    printf("\033[4%dm%d\033[0m", ((index+1)%7), target->partition_size);
    for(int i=(size/2)+5; i< size; i++) {
        printf(".");
    }
    printf("\n");
    // printf("|");

    for (int i = target->partition_size/2; i < target->partition_size; i++){
        printf(".");
        if(i % size == 0){
            printf("|\n");
            printf("|");
        }
    }


    printf("\n|");
    for(int i=0; i< size; i++) {
        printf("-");
    }
    printf("|\033[0m\n");

    printf("%c\n", data ->end);
    return true;
}




bool craft_execute(craft_target_t *target, partition_callback_t callback, void *arg)
{
    if (target == NULL || callback == NULL)
        return false;

    bool result = true;
    for (int i = 0; i < target->partition_count; i++)
    {
        result = result && callback(target, i, arg);
        // TODO: check for failure
    }

    return result;
}

int main()
{
    // xcraft_enc
    // xcraft_json
    // xcraft_xml
    // xcraft_compress
    craft_target_t *target = craft_open("example_01.c",
                                        CRAFT_DEFAULT_PARTITION_COUNT);
    if (target == NULL)
        return 1;

    // craft_print(target);

    // if (craft_execute(target, xcraft_enc, NULL))
    // {
    //     printf("File encrypted successfully\n");
    //     craft_print(target);
    // }
    // else
    //     printf("Fail to encrypt\n");

    // if (craft_execute(target,  xcraft_enc_xor, NULL))
    // {
    //     printf("File encrypted successfully\n");
    //     craft_print(target);
    // }
    // else
    //     printf("Fail to encrypt\n");
    struct se_data data = {'[', ']'};
    craft_execute(target, xcraft_enc_color,  &data);
    // craft_execute(target, xcraft_x,  &data);
    // if (craft_execute(target, xcraft_enc_color, NULL))
    // {
        // craft_print(target);
    // }
    // else
        // printf("Fail to encrypt\n");


    
   
    craft_close(target);

    return 0;
}
