#include "fobj.h"

extern struct HSD_ObjAllocData alloc_data;
struct HSD_ObjAllocData *HSD_FObjGetAllocData(void)
{
    return &alloc_data;
}
