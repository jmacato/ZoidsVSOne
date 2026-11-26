/* Based on https://github.com/doldecomp/melee/blob/master/src/sysdolphin/baselib/id.c.
 */
#include "id.h"

struct HSD_ObjAllocData *HSD_IDGetAllocData(void)
{
    return &alloc_data;
}
