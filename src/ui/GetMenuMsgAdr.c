#include "types.h"

extern u32 TXT_Menu[];
extern char TXT_Menu_dat[];

char *GetMenuMsgAdr(s16 message)
{
    u32 offset = TXT_Menu[message];
    if (message == -1)
        return 0;
    return TXT_Menu_dat + offset;
}
