#pragma readonly_strings on
#include "weapon.h"
#include "zoid.h"
#include "game_part_data.h"
#include "missile.h"

extern HSD_JObj *searchArcJoint2(ModelArchive *archive, s32 model, char *name);
extern s32 sprintf(char *buffer, const char *format, ...);
extern JointPose *makeJobj(void);
extern void stCopyObj(HSD_JObj *joint, JointPose *pose);
extern void stCopyMatMobj(HSD_JObj *joint, JointPose *pose);
extern void sWeaponSetAnim(s32 weapon, s32 animation);

s32 sWeaponSetN(ModelArchive *archive, s32 type, s32 model, ZoidState *zoid, s32 slot, s32 ammo)
{
    u8 top_padding[4];
    char name[256];
    HSD_JObj *joint;
    WeaponState *weapon;
    s32 i;
    s32 k;
    s32 j;
    PartData *part;
    u8 frame_padding[12];

    if (zoid == 0)
        return -1;
    if (archive == 0)
        return -1;
    joint = zoid->weapon_slots[slot].joint;
    if (joint == 0)
        return -1;
    if (slot >= 30)
        return -1;
    if (zoid->weapon_slots[slot].weapon != -1)
        return -2;
    for (k = 0; k < 100; k++) {
        weapon = &sWeapon[k];
        if (weapon->active == 0)
            break;
    }
    if (k == 100)
        return -1;
    i = k;
    if (weapon->active != 0)
        return -1;
    weapon->archive = archive;
    weapon->model = model;
    weapon->owner = zoid;
    weapon->type = type;
    weapon->mount_joint = joint;
    weapon->target_joint = searchArcJoint2(weapon->archive, model, "target_joint");
    if (weapon->target_joint == 0)
        weapon->target_joint = searchArcJoint2(weapon->archive, model, "target1_joint");
    for (j = 0; j < 12; j++) {
        sprintf(name, "pa_%02d_joint", j);
        weapon->barrels[j] = searchArcJoint2(weapon->archive, model, name);
    }
    for (j = 0; j < 13; j++) {
        sprintf(name, "te_%02d_joint", j);
        weapon->trace_joints[j] = searchArcJoint2(weapon->archive, model, name);
        weapon->trace_positions[j].x = zoid->position[0];
        weapon->trace_positions[j].y = zoid->position[1];
        weapon->trace_positions[j].z = zoid->position[2];
    }
    for (k = 0; k < 12; k++) {
        sprintf(name, "a_%x_joint", k);
        weapon->inverses[k].joint = searchArcJoint2(weapon->archive, model, name);
    }
    weapon->pose = makeJobj();
    stCopyObj(archive->models[model], weapon->pose);
    stCopyMatMobj(archive->models[model], weapon->pose);
    weapon->active = 1;
    weapon->ammo = ammo;
    weapon->animation = 0;
    weapon->marker_count = Tea_partsdat[type].marker_count;
    if (weapon->marker_count > 20)
        weapon->marker_count = 20;
    weapon->bullet_kind = 0;
    if ((Tea_partsdat + type)->bullets[0] > 0)
        weapon->bullet_kind = Tea_bulletdat[(Tea_partsdat + type)->bullets[0]].kind;
    part = &Tea_partsdat[type];
    weapon->range = part->range;
    weapon->rate = 0.01 * part->rate;
    weapon->drain = part->flags & 0x37;
    zoid->weapon_slots[slot].weapon = i;
    sWeaponSetAnim(i, 4);
    return i;
}
