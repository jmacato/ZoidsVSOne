#include "zoid.h"

extern u32 zdsMotTBL[];
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void zdGetBodyPt(ZoidState *zoid, Vec3 *point);
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern f32 zdColPosY(Vec3 *point, u16 *selector);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ik3dOn(ZoidState *zoid, FootJoint *foot);
extern void zdLinierReset(ZoidState *zoid, HSD_JObj *joint);

void zdChgNormal(ZoidState *zoid)
{
    ZoidControlData *control;
    Vec3 body;
    s32 frame_padding[3];
    f32 ground;
    f32 depth;
    f32 top;

    if (zoid != 0 && zoid->joint != 0) {
        control = zoid->control;
        if ((zdsMotTBL[zoid->current_animation] & 0xF0) != 0) {
            ZoidSetAnim(zoid, 1);
            zoid->action = ZOID_ACTION_WALK;
            zoid->requested_action = 0;
            HSD_JObjAnimAll(zoid->joint);
            return;
        }
        zdGetBodyPt(zoid, &body);
        ZoidSetAnim(zoid, 1);
        zdLinierTm(zoid, 0);
        zoid->height_offset_speed = 0.0f;
        zoid->displacement[1] = 0.0f;
        ground = zdColPosY((Vec3 *)zoid->position, 0);
        depth = ground - zoid->position[1];
        if (depth > 0.0f) {
            zoid->previous_position[1] = ground;
            zoid->position[1] = ground;
            zoid->height_offset -= depth;
        }
        zoid->height_offset = 0.0f;
        zdSetXYZ(zoid);
        HSD_JObjAnimAll(zoid->joint);
        zdSetXYZ(zoid);
        top = zoid->buckle_height + (zoid->position[1] + zoid->height_offset);
        zoid->field_1A34 = 0;
        depth = top - body.y;
        if (depth > 0.0f) {
            zoid->height_offset -= depth;
        }
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
        ik3dOn(zoid, &zoid->feet[2]);
        ik3dOn(zoid, &zoid->feet[3]);
        if (control->field_00F4 != 2) {
            ik3dOn(zoid, &zoid->feet[0]);
            ik3dOn(zoid, &zoid->feet[1]);
        }
        zdLinierReset(zoid, zoid->feet[2].joint);
        zdLinierReset(zoid, zoid->feet[3].joint);
        if (control->field_00F4 != 2) {
            zdLinierReset(zoid, zoid->feet[0].joint);
            zdLinierReset(zoid, zoid->feet[1].joint);
        }
        zoid->action = ZOID_ACTION_WALK;
        zoid->requested_action = 0;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[2] = 0.0f;
    }
}
