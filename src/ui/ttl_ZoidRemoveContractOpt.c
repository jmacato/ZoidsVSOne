#include "game_save.h"

s16 ttl_ZoidRemoveContractOpt(s16 zoid, s16 slot)
{
    s16 option = IveSave[zoid].contract_options[slot];
    IveSave[zoid].contract_options[slot] = -1;
    if (option > 0)
        return option;
    return -1;
}
