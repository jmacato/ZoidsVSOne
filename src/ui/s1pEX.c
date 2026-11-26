#include "zoid.h"
#include "game_camera.h"

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 selected);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern ModelArchive *dsp1p;
extern HSD_JObj *dspJobjEx3[2];
extern s32 dspAnmEx3[2];
extern s32 dspAnmEx3n[2];
extern s32 pause;

void s1pEX(CameraState *camera, ZoidState *zoid, HSD_JObj *parent)
{
    HSD_JObj *child;
    HSD_JObj *joint;
    s32 selected;

    if (parent != 0 && zoid != 0 && zoid->joint != 0 && zoid->super_attack_enabled != 0) {
        child = GetChild(parent, 0, 2, -1, -1, -1);
        if (child != 0) {
            joint = dspJobjEx3[camera->half];
            if (joint != 0) {
                jobjCopyPos(child, joint);
                selected = 0;
                if (zoid->super_attack_cooldown != 0) {
                    selected = 1;
                }
                if (selected != dspAnmEx3n[camera->half]) {
                    LoadArcAnimModel2(dsp1p, joint, dspAnmEx3[camera->half], selected);
                    dspAnmEx3n[camera->half] = selected;
                }
                if (pause == 0) {
                    jobjAnim(joint);
                }
                jobjDispAll(joint);
            }
        }
    }
}
