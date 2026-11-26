#include "zoid.h"
#include "game_zoid_data.h"
#include "game_zoid_entry.h"

extern s32 ZoidInit(ZoidState *zoid, s32 type);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);
extern void zdLoadSuperAtackWp(ZoidState *zoid);
extern void zdLoadOption(ZoidState *zoid, s32 option);

void ZoidInit1(ZoidState *zoid, s32 index, s32 slot)
{
    s32 i;
    s32 type;
    s32 mount;
    s32 color;
    s32 frame_padding[2];

    if (zoid == 0) {
        return;
    }
    type = GameZoid[index].type;
    if (type == -1) {
        return;
    }
    ZoidInit(zoid, type);
    zoid->slot = slot;
    zoid->person = GameZoid[index].person;
    color = GameZoid[index].color;
    if (color != 0) {
        ZoidColor(zoid, color, 0);
    }
    for (i = 0; i < 28; i++) {
        if (zoid->weapon_slots[i].joint != 0) {
            s32 part = GameZoid[index].weapons[i];

            if (part >= 0) {
                for (mount = 0; mount < 10; mount++) {
                    if (part == Tea_zoiddat[type].mount_parts[mount]) {
                        break;
                    }
                }
                if (mount == 10) {
                    mount = 9;
                }
                sWeaponMount(part, zoid, i, mount);
            }
        }
    }
    zdLoadSuperAtackWp(zoid);
    zdLoadOption(zoid, GameZoid[index].option);
    zoid->additional_parts[0] = GameZoid[index].additional_parts[0];
    zoid->additional_parts[1] = GameZoid[index].additional_parts[1];
    zoid->additional_parts[2] = GameZoid[index].additional_parts[2];
}
