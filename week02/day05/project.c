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

typedef struct craft_target_t craft_target_t;
typedef struct craft_partition_t craft_partition_t;
typedef struct craft_extension_t craft_extension_t;
typedef struct craft_extension_info_t craft_extension_info_t;

struct craft_extension_info_t
{
    char *name; // PDF
    char *author;
    char *description;
};

struct craft_extension_t
{
    craft_extension_info_t info;
    bool (*execute)(craft_target_t *);
};

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
    unsigned int loaded_extensions;
    void *block;
    craft_partition_t *partitions;
    craft_extension_t **extensions;
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
    fclose(handler);

    target->version = CRAFT_VERSION;
    target->partitions = craft_partitionize(target);

    target->loaded_extensions = 0;
    target->extensions = NULL;

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

        if (target->loaded_extensions > 0)
            free(target->extensions);

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
    printf("loaded-extensions: %u\n", target->loaded_extensions);
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

bool craft_load_extension(craft_target_t *target, craft_extension_t *extension)
{
    if (extension == NULL)
        return false;
    target->extensions[target->loaded_extensions++] = extension;
    return true;
}

int main()
{
    craft_target_t *target = craft_open("project.c",
                                        CRAFT_DEFAULT_PARTITION_COUNT);
    if (target == NULL)
        return 1;

    craft_print(target);
    craft_close(target);

    return 0;
}
