#include "id.h"
void _HSD_IDForgetMemory(void)
{
    memset(&default_table, 0, sizeof(default_table));
}
