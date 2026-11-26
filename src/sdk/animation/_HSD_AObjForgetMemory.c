#include "aobj.h"

extern AnimationEndCallback *endcallback_list;

void _HSD_AObjForgetMemory(void *low, void *high)
{
    endcallback_list = 0;
}
