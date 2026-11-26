/* Based on
 * https://github.com/doldecomp/melee/blob/master/src/sysdolphin/baselib/objalloc.c. */
#include "objalloc.h"

void HSD_ObjGetHeap(u32 *size, void **heap)
{
    if (size != 0) {
        *size = obj_heap.size;
    }
    if (heap != 0) {
        *heap = (void *)obj_heap.top;
    }
}
