#include "zoid.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);

void ZoidTurn(ZoidState *zoid)
{
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, 9);
        zoid->action_phase = 1;
        break;
    case 1:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action = ZOID_ACTION_WALK;
            zoid->heading += zoid->pose->child->rotation[1];
            zoid->pose->child->rotation[1] = 0.0f;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
            zoid->forward_speed = 0.0f;
            zoid->field_1A74 = 0.0f;
            zoid->ramped_speed = 0.0f;
            zoid->field_1A80 = 0.0f;
        } else {
            zoid->heading += DEG(3);
            zoid->field_1A74 = 0.0f;
            zoid->field_1A80 = 0.0f;
        }
        break;
    }
}
