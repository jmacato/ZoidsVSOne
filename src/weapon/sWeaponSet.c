#pragma readonly_strings on
#include "zoid.h"
#include "model_archive.h"
#include "game_part_data.h"

extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 sWeaponSetN(ModelArchive *archive, s32 type, s32 model, ZoidState *zoid, s32 slot, s32 ammo);
extern void sWeaponPurge(s32 weapon);

s32 sWeaponSet(s32 part, ZoidState *zoid, s32 slot, WeaponMount *mount)
{
    char name[100];
    PartData *data;
    ModelArchive *archive;
    s32 model;
    s32 i;
    s32 current;
    s32 ammo;
    s32 entry;
    s32 result;

    if (zoid == 0)
        return -1;
    if (zoid->joint == 0)
        return -1;
    if (zoid->weapon_slots[slot].joint == 0)
        return -1;
    if (zoid->weapon_slots[slot].weapon != -1)
        return -1;
    if (part <= 0)
        return -1;
    if (part >= 450)
        return -1;
    sprintf(name, "weapon/%s.dat", (data = &Tea_partsdat[part])->model_name);
    archive = LoadArc2(name);
    if (archive == 0)
        return -1;
    if (archive->model_data == 0)
        return -1;
    ammo = data->ammo;
    current = slot;
    result = 0;
    entry = 0;
    for (model = 0; model < archive->model_count; model++, current++) {
        for (; entry < 4; entry++) {
            if (mount->entries[entry].active == 0)
                break;
        }
        if (entry == 4)
            break;
        if (current >= 27)
            break;
        result = sWeaponSetN(archive, part, model, zoid, current, ammo);
        if (result == -1)
            break;
        if (result != -2) {
            mount->active = 1;
            mount->entries[entry].active = 1;
            mount->entries[entry].slot = current;
            mount->entries[entry].field_08 = 0;
        }
    }
    if (result == -1) {
        for (i = 0; i < model; i++)
            sWeaponPurge(zoid->weapon_slots[slot + i].weapon);
        return -1;
    }
    return archive->model_count;
}
