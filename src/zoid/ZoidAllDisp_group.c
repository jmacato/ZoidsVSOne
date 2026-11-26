#include "zoid.h"
#include "game_camera.h"

extern CameraState *camTmp;
extern s32 dbgZoidColi;
extern f32 (*HSD_CObjGetViewingMtxPtr(struct HSD_CObj *cobj))[4];
extern void PSMTXMultVec(f32 (*m)[4], Vec3 *src, Vec3 *dst);
extern void angLimit(f32 *angle);
extern void ZoidCoObjOFF(ZoidState *zoid);
extern void ZoidSmallDisp(ZoidState *zoid);
extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);
extern void zdDispCursor(void);
extern void zdSetXYZ(ZoidState *zoid);

void ZoidAllDisp(void)
{
    s32 i;
    f32 (*view)[4];
    Vec3 point;

    view = HSD_CObjGetViewingMtxPtr(camTmp->cobj);

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            ZoidControlData *control = Zoid[i].control;

            PSMTXMultVec(view, &Zoid[i].camera_joint_position, &point);
            if (point.z >= 0.0f || point.z < -500.0f) {
                continue;
            }
            if (sCamNN == 1) {
                if (point.x + point.z >= 7.0f || point.x - point.z <= -7.0f) {
                    continue;
                }
            }
            if (Zoid[i].stel_state != ZOID_STEL_OFF) {
                continue;
            }
            angLimit(&Zoid[i].heading);
            if (camTmp->zoid_distance[i] < control->detail_distance && dbgZoidColi == 0) {
                ZoidCoObjOFF(&Zoid[i]);
                HSD_JObjDispAll(Zoid[i].joint, 0, 7, 0);
            } else {
                ZoidSmallDisp(&Zoid[i]);
            }
        }
    }
    zdDispCursor();
}

void ZoidAllDispXLU(void)
{
    s32 i;
    f32 (*view)[4];
    Vec3 point;

    view = HSD_CObjGetViewingMtxPtr(camTmp->cobj);

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            ZoidControlData *control = Zoid[i].control;

            if (Zoid[i].stel_state != ZOID_STEL_FADING) {
                continue;
            }
            PSMTXMultVec(view, &Zoid[i].camera_joint_position, &point);
            if (point.z >= 0.0f || point.z < -500.0f) {
                continue;
            }
            if (sCamNN == 1) {
                if (point.x + point.z >= 7.0f || point.x - point.z <= -7.0f) {
                    continue;
                }
            }
            if (camTmp->zoid_distance[i] < control->detail_distance && dbgZoidColi == 0) {
                ZoidCoObjOFF(&Zoid[i]);
                HSD_JObjDispAll(Zoid[i].joint, 0, 7, 0);
            } else {
                ZoidSmallDisp(&Zoid[i]);
            }
        }
    }
}

void ZoidAllDisp3(void)
{
    s32 i;
    f32 (*view)[4];
    Vec3 point;
    s32 frame_padding[2];

    view = HSD_CObjGetViewingMtxPtr(camTmp->cobj);
    for (i = 0; i < 16; i++) {
        s32 stealth = 0;

        if (Zoid[i].joint != 0) {
            ZoidControlData *control = Zoid[i].control;

            Zoid[i].camera_joint_position.x = Zoid[i].camera_joint->matrix[0][3];
            Zoid[i].camera_joint_position.y = Zoid[i].camera_joint->matrix[1][3];
            Zoid[i].camera_joint_position.z = Zoid[i].camera_joint->matrix[2][3];
            if (Zoid[i].stel_state == ZOID_STEL_ON) {
                stealth = 1;
            }
            if (stealth == 0) {
                continue;
            }
            PSMTXMultVec(view, &Zoid[i].camera_joint_position, &point);
            if (point.z >= 0.0f || point.z < -500.0f) {
                continue;
            }
            if (sCamNN == 1) {
                if (point.x + point.z >= 7.0f || point.x - point.z <= -7.0f) {
                    continue;
                }
            }
            angLimit(&Zoid[i].heading);
            zdSetXYZ(&Zoid[i]);
            if (camTmp->zoid_distance[i] < control->detail_distance && dbgZoidColi == 0) {
                ZoidCoObjOFF(&Zoid[i]);
                HSD_JObjDispAll(Zoid[i].joint, 0, 7, 0);
            } else {
                ZoidSmallDisp(&Zoid[i]);
            }
        }
    }
}
