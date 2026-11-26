#include "zoid.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void ZoidTurnL(ZoidState *zoid, s32 mode)
{
    f32 speed = absf(zoid->stick_length);

    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, 10);
        zoid->action_phase = 1;
        break;
    case 1:
        if (mode == 0 && speed < 0.01) {
            zoid->animation_stopped = 1;
        }
        if (mode == 2 && zoid->target_pending != 0 && zoid->target_slot < 16 &&
            absf(zoid->target_angles[zoid->target_slot + 0LL]) < DEG(5)) {
            zoid->animation_stopped = 1;
        }
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action = ZOID_ACTION_WALK;
            zoid->heading += zoid->pose->child->rotation[1];
            zoid->pose->child->rotation[1] = 0.0f;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
        } else {
            zoid->heading += DEG(4);
        }
        break;
    }
}
