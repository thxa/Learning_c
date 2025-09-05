/* Mojibake 1.0.0a */
#include "craft.h"

mojibake_partition_t *mojibake_partitionize(mojibake_target_t *target)
{
    assert(target != NULL);
    assert(target->partition_size > 0);
    assert(target->partition_count > 0);

    mojibake_partition_t *partitions = (mojibake_partition_t *)
        malloc(sizeof(mojibake_partition_t) * target->partition_count);
    RETURN_NULL_IF(partitions == NULL);

    for (int i = 0; i < target->partition_count; i++)
        partitions[i].index = i;

    return partitions;
}

void mojibake_departitionize(mojibake_partition_t *partitions)
{
    if (partitions)
        free(partitions);
}

mojibake_target_t *mojibake_open(char *file_path, unsigned int partition_count)
{
    mojibake_target_t *target = NULL;

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

    target = (mojibake_target_t *)malloc(sizeof(mojibake_target_t));
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

    target->version = MOJIBAKE_VERSION;
    target->partitions = mojibake_partitionize(target);

    return target;
}

void mojibake_close(mojibake_target_t *target)
{
    if (target)
    {
        target->size = 0;
        target->extra = 0;
        target->partition_count = 0;
        target->partition_size = 0;
        target->version = 0;

        mojibake_departitionize(target->partitions);

        if (target->block)
            free(target->block);

        free(target);
    }
}

void mojibake_print(mojibake_target_t *target)
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

bool mbx_default(mojibake_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;

    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);
    for (int i = 0; i < target->partition_size; i++)
        partition[i] = partition[i] << 1;
    return true;
}

struct se_data
{
    char start;
    char end;
};

bool xcraft_start_end(mojibake_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count || arg == NULL)
        return false;

    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);
    struct se_data *data = (struct se_data *)arg;

    for (int i = 0; i < target->partition_size; i++)
        printf("%c%c%c", data->start, partition[i], data->end);
    return true;
}

bool xcraft_digit_color(mojibake_target_t *target, unsigned int index, void *arg)
{
    if (target == NULL || target->block == NULL || index >= target->partition_count)
        return false;

    unsigned char *partition = CRAFT_BLOCK_OFFSET(target, index);

    for (int i = 0; i < target->partition_size; i++)
        if (isdigit(partition[i]))
        {
            printf("\033[1;31m%c\033[0m", partition[i]);
        }
        else
        {
            printf("%c", partition[i]);
        }
    return true;
}

bool mojibake_execute(mojibake_target_t *target, mojibake_partition_callback_t callback, void *arg)
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
    mojibake_target_t *target = mojibake_open("target.c",
                                              CRAFT_DEFAULT_PARTITION_COUNT);
    if (target == NULL)
        return 1;

    // craft_print(target);

    // struct se_data data;
    // data.start = '(';
    // data.end = ')';

    if (!mojibake_execute(target, xcraft_digit_color, NULL))
        printf("digit_color execution Failed\n");

    printf("\n");
    mojibake_close(target);
    return 0;
}
