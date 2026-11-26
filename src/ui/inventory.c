#include "game_save.h"
#include "game_zoid_data.h"

extern s32 ttl_ZoidChkWepPoint(s16 zoid, s16 point);
extern void ttl_IveSaveSetZoidDefParts(s16 record, s16 slot, s16 zoid);

s32 ttl_ZoidWepPointPermission(s16 zoid, s16 point)
{
    if (ttl_ZoidChkWepPoint(zoid, point) == 0)
        return 0;
    if (Tea_zoiddat[zoid].weapon_permissions[point] == 0)
        return 0;
    return 1;
}

s16 ttl_ZoidRemoveContractSub(s16 record, s16 slot, s16 subpart)
{
    s16 value;

    if (subpart < 0)
        return -1;
    if (subpart >= 3)
        return -1;
    value = IveSave[record].contract_subparts[slot][subpart];
    IveSave[record].contract_subparts[slot][subpart] = -1;
    if (value > 0)
        return value;
    return -1;
}

void ttl_HaveAddZoid(s16 record, s16 zoid)
{
    if (zoid != -1) {
        IveSave[record].owned_zoids[IveSave[record].owned_zoid_count] = zoid;
        ttl_IveSaveSetZoidDefParts(record, IveSave[record].owned_zoid_count, zoid);
        IveSave[record].owned_zoid_count++;
    }
}
