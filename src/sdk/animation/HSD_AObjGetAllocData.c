#include "aobj.h"

extern struct HSD_ObjAllocData alloc_data;
struct HSD_ObjAllocData *HSD_AObjGetAllocData(void)
{
    return &alloc_data;
}
