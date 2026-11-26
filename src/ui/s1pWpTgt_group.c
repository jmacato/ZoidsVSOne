#include "zoid.h"
#include "weapon.h"
#include "missile.h"
#include "game_camera.h"

/* the definition takes no distance parameter; the original call passes one */
extern void s1pWp1TgtStraight(CameraState *disp, WeaponState *weapon, f32 distance);
extern void s1pWp1TgtHome(CameraState *disp, WeaponState *weapon);
extern void s1pWp1TgtParabola(CameraState *disp, WeaponState *weapon, f32 distance);

void s1pWpTgt_(CameraState *disp, ZoidState *zoid, s32 mount)
{
    WeaponMount *wm;
    s32 i;
    WeaponState *weapon;
    f32 distance;
    s32 slot;

    wm = &zoid->weapon_mounts[mount];
    if (wm->active == 0)
        return;
    distance = 0.0f;
    if (zoid->target_slot == -1)
        zoid->target_pending = 0;
    if (zoid->target_pending != 0)
        distance = zoid->distances[zoid->target_slot];
    for (i = 0; i < 4; i++) {
        if (wm->entries[i].active == 0)
            continue;
        if (wm->entries[i].slot == -1)
            continue;
        slot = zoid->weapon_slots[wm->entries[i].slot].weapon;
        if (slot == -1)
            continue;
        weapon = &sWeapon[slot];
        if (weapon->bullet_kind == BULLET_KIND_STRAIGHT && zoid->target_pending != 0)
            s1pWp1TgtStraight(disp, weapon, distance);
        if (weapon->bullet_kind == BULLET_KIND_AT20)
            s1pWp1TgtHome(disp, weapon);
        if (weapon->bullet_kind == BULLET_KIND_PARABOLA && zoid->target_pending != 0)
            s1pWp1TgtParabola(disp, weapon, distance);
    }
}

void s1pWpTgt(CameraState *disp, ZoidState *zoid)
{
    s32 i;

    disp->target_marker_count = 0;
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    if (zoid->death_started != 0)
        return;
    if (zoid->weapon_mount == -1)
        return;
    if (zoid->selected_weapon_mount == -1)
        return;
    if (zoid->selected_weapon_mount != zoid->weapon_mount)
        return;
    if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
        for (i = 0; i < 10; i++)
            s1pWpTgt_(disp, zoid, i);
    } else {
        s1pWpTgt_(disp, zoid, zoid->selected_weapon_mount);
    }
}
