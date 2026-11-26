#include "zoid.h"
#include "game_zoid_data.h"
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);
extern void OSReport(const char *format, ...);

void zdLoadSuperAtackWp(ZoidState *zoid)
{
    s64 frame_padding;
    s32 part = Tea_zoiddat[zoid->type].super_attack_part;
    s32 slot = Tea_zoiddat[zoid->type].super_attack_slot;

    if (part > 0 && slot >= 0) {
        sWeaponMount(part, zoid, slot, WEAPON_MOUNT_SUPER_ATTACK);
        OSReport("mount [%s] -- ", zoid);
    }
}
