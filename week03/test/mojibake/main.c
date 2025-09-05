#include "mojibake.h"
#include "modules/default/mbx_default.h"
#include "modules/mbx_load/mbx_load.h"

int main()
{
    mojibake_target_t *target = mojibake_open("target",
                                              MOJIBAKE_DEFAULT_PARTITION_COUNT);
    if (target == NULL)
        return 1;

    // if (!mojibake_execute(target, mbx_default, NULL))
    //     printf("Execution error\n");


    if (!mojibake_execute(target, mbx_load, NULL))
        printf("Execution error\n");

    // mojibake_print(target);

    printf("\n");
    mojibake_close(target);
    return 0;
}
