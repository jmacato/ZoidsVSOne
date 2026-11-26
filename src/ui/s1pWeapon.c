#include "jobj.h"
#include "model_archive.h"
#include "game_camera.h"
#include "zoid.h"
#include "game_part_data.h"
#include "game_text.h"

#define NULL 0

extern ModelArchive *dsp1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern s32 sWeaponGetNumber(ZoidState *zoid, s32 selected);
extern s32 sWeaponGetMountBullet(ZoidState *zoid, s32 index);

void s1pWeapon(CameraState *camera, ZoidState *zoid, HSD_JObj *joint)
{
    s32 idx;
    s32 num;
    s32 sel;
    HSD_JObj *frame;
    char *name;
    HSD_JObj *dst;
    s32 i;
    s32 digits[3];
    s16 icon;
    s32 count;
    HSD_JObj *pos;
    s32 k;
    s32 bullet;
    s32 icon2;

    if (dsp1p == NULL)
        return;
    if (zoid->weapon_mount_count <= 0)
        return;
    sel = zoid->selected_weapon_mount;
    if (sel != -1 && zoid->weapon_mounts[sel].active == 0)
        return;
    if (sel == WEAPON_MOUNT_SUPER_ATTACK)
        sel = -1;
    if (sel == -1) {
        for (i = 0, sel = 0; i < 10; i++, sel++) {
            if (zoid->weapon_mounts[i].active != 0)
                break;
        }
        if (i == 10)
            return;
    }
    if (joint == NULL)
        return;
    pos = GetChild(joint, 0, 3, -1, -1, -1);
    if (pos == NULL)
        return;
    frame = dsp1p->models[9];
    if (sCamNN == 2 && sCamNS == 1 && camera->half == 0)
        frame = dsp1p->models[10];
    if (frame == NULL)
        return;
    jobjCopyPos(pos, frame);
    sMakeMatrix(frame);
    HSD_JObjDisp(GetChild(frame, 0, -1, -1, -1, -1), 0, 7, 0);
    if (sel != -1) {
        num = sWeaponGetNumber(zoid, sel);
        count = camera->target_marker_count;
        pos = GetChild(frame, 0, 0, -1, -1, -1);
        HSD_JObjDisp(pos, 0, 7, 0);
        jobjDispAll(pos);
        pos = GetChild(frame, 0, 0, 0, -1, -1);
        dst = GetChild(dsp1p->models[12], 0, 0, count / 10 % 10, -1, -1);
        jobjCopyPos(pos, dst);
        HSD_JObjDisp(dst, 0, 7, 0);
        pos = GetChild(frame, 0, 0, 1, -1, -1);
        dst = GetChild(dsp1p->models[12], 0, 0, count % 10, -1, -1);
        jobjCopyPos(pos, dst);
        HSD_JObjDisp(dst, 0, 7, 0);
        pos = GetChild(frame, 0, 2, -1, -1, -1);
        icon = -1;
        if (num != -1)
            icon = Tea_partsdat[num].icon;
        if (icon >= 15 || icon < 0)
            icon = 0;
        if (icon >= 0) {
            dst = GetChild(dsp1p->models[11], 0, icon, -1, -1, -1);
            jobjCopyPos(pos, dst);
            HSD_JObjDisp(dst, 0, 7, 0);
        }
        bullet = sWeaponGetMountBullet(zoid, sel);
        if (bullet >= 999)
            bullet = 999;
        digits[0] = bullet / 100 % 10;
        digits[1] = bullet / 10 % 10;
        digits[2] = bullet % 10;
        for (i = 0; i < 3; i++) {
            pos = GetChild(frame, 0, 4, i, -1, -1);
            dst = GetChild(dsp1p->models[12], 0, 1, digits[i], -1, -1);
            jobjCopyPos(pos, dst);
            HSD_JObjDisp(dst, 0, 7, 0);
        }
        pos = GetChild(frame, 0, 3, -1, -1, -1);
        if (pos != NULL) {
            name = NULL;
            if (num != -1)
                name = Tea_partsdat[num].english_name;
            if (name != NULL) {
                if (sCamNN == 2 && sCamNS == 1 && camera->half == 0)
                    putAscJobjLR_sp(pos, 2, name, 0, 0.0f);
                else
                    putAscJobjLR_sp(pos, 2, name, 1, 0.0f);
            }
        }
    }
    if (zoid->weapon_mount_count > 1) {
        idx = sel + 1;
        k = 0;
        for (i = 0; i < 10; i++, idx++) {
            if (idx >= 10)
                idx -= 10;
            if (idx == sel)
                return;
            if (zoid->weapon_mounts[idx].active == 0)
                continue;
            num = sWeaponGetNumber(zoid, idx);
            if (num == -1)
                continue;
            icon2 = Tea_partsdat[num].icon;
            if (icon2 >= 15 || icon2 < 0)
                icon2 = 0;
            pos = GetChild(frame, 0, 2, k, -1, -1);
            dst = GetChild(dsp1p->models[11], 0, icon2, 0, -1, -1);
            jobjCopyPos(pos, dst);
            HSD_JObjDisp(dst, 0, 7, 0);
            k++;
        }
    }
}
