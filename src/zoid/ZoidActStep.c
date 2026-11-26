#include "zoid.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void ZoidSusumuStepV(ZoidState *zoid);
extern f32 zdGoYA3dOfstBy(ZoidState *zoid, Vec3 *offset, f32 by);
extern void zdChgNormal(ZoidState *zoid);

/* unused; 2 and 3 repeat the ZoidActAtack start and loop tables; keeps the unit's .rodata layout */
static const char actStepFiller0[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static const u32 actStepFiller1[41] = {0x00000000, 0x3E99999A, 0x3EAE147B, 0x3ECCCCCD, 0x3EF0A3D7, 0x3F000000, 0x3F11EB85, 0x3F19999A, 0x3F28F5C3, 0x3F30A3D7, 0x3F333333, 0x3F428F5C, 0x3F4A3D71, 0x3F4CCCCD, 0x3F54BC6A, 0x3F5D70A4, 0x3F666666, 0x3F6E147B, 0x3F75C28F, 0x3F7C28F6, 0x3F800000, 0x3F83D70A, 0x3F87AE14, 0x3F8A3D71, 0x3F8CCCCD, 0x3F8F5C29, 0x3F91EB85, 0x3F947AE1, 0x3F970A3D, 0x3F99999A, 0x3F9C28F6, 0x3F9EB852, 0x3FA147AE, 0x3FA3D70A, 0x3FA66666, 0x3FA8F5C3, 0x3FAB851F, 0x3FAE147B, 0x3FB0A3D7, 0x3FB33333, 0x00000000};
static const u32 actStepFiller2[5] = {0x00000058, 0x0000005A, 0x0000005C, 0x0000005E, 0x00000060};
static const u32 actStepFiller3[5] = {0x00000059, 0x0000005B, 0x0000005D, 0x0000005F, 0x00000061};

void ZoidActStep(ZoidState *zoid)
{
    s32 start[4] = {24, 28, 32, 36};
    s32 loop[4] = {25, 29, 33, 37};
    s32 land[4] = {26, 30, 34, 38};
    s32 end[4] = {27, 31, 35, 39};
    s32 busy;
    s32 hit;
    s32 request;
    ZoidControlData *control;

    (void)actStepFiller0;
    (void)actStepFiller1;
    (void)actStepFiller2;
    (void)actStepFiller3;
    busy = 0;
    request = zoid->requested_action;
    control = zoid->control;
    if (request == ZOID_ACTION_STEP_0) busy = 1;
    if (request == ZOID_ACTION_STEP_1) busy = 1;
    if (request == ZOID_ACTION_STEP_2) busy = 1;
    if (request == ZOID_ACTION_STEP_3) busy = 1;
    if (request == ZOID_ACTION_STEP_REQUEST_0) busy = 1;
    if (request == ZOID_ACTION_STEP_REQUEST_1) busy = 1;
    if (request == ZOID_ACTION_STEP_REQUEST_2) busy = 1;
    if (request == ZOID_ACTION_STEP_REQUEST_3) busy = 1;
    if (busy != 0) {
        zoid->requested_action = 0;
    }
    if (control->field_00F8 == 1) {
        zoid->action = ZOID_ACTION_WALK;
        return;
    }
    if (zoid->action_phase >= 16 && zoid->action_phase < 48) {
        ZoidSusumuStepV(zoid);
    }
    switch (zoid->action_phase) {
    case 0:
        hit = 0;
        if (zdGoYA3dOfstBy(zoid, &zoid->launch_velocity, 0.5f) > 1.0f) hit = 1;
        if (zdGoYA3dOfstBy(zoid, &zoid->launch_velocity, 1.0f) > 1.0f) hit = 1;
        if (zdGoYA3dOfstBy(zoid, &zoid->launch_velocity, 2.0f) > 1.0f) hit = 1;
        if (zdGoYA3dOfstBy(zoid, &zoid->launch_velocity, 5.0f) > 1.0f) hit = 1;
        if (zdGoYA3dOfstBy(zoid, &zoid->launch_velocity, 10.0f) > 1.0f) hit = 1;
        if (hit != 0) {
            zoid->action_phase = 153;
        } else {
            ZoidSetAnim(zoid, start[zoid->action - ZOID_ACTION_STEP_0]);
            zoid->action_phase = 1;
        }
        break;
    case 1:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    case 16:
        ZoidSetAnim(zoid, loop[zoid->action - ZOID_ACTION_STEP_0]);
        zoid->action_phase = 17;
        break;
    case 17:
        if ((u32)zoid->bust_coobj.ground_contact != 0) {
            zoid->launch_velocity.y = 0.0f;
        }
        if ((u32)zoid->hip_coobj.ground_contact != 0) {
            zoid->launch_velocity.y = 0.0f;
        }
        if ((u32)zoid->neck_coobj.ground_contact != 0) {
            zoid->launch_velocity.y = 0.0f;
        }
        if (zoid->launch_velocity.y > 0.0f) {
            break;
        }
    case 32:
        ZoidSetAnim(zoid, land[zoid->action - ZOID_ACTION_STEP_0]);
        zoid->action_phase = 33;
        break;
    case 33:
        if (zoid->ground_normal_count == 0 && zoid->grounded == 0) {
            break;
        }
        zoid->grounded_frames = 0;
        zoid->action_phase = 48;
    case 34:
        zoid->grounded_frames++;
        if (zoid->grounded_frames < 6) {
            break;
        }
    case 48:
        ZoidSetAnim(zoid, end[zoid->action - ZOID_ACTION_STEP_0]);
        zoid->action_phase = 49;
        break;
    case 49:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    default:
        zdChgNormal(zoid);
        break;
    }
}
