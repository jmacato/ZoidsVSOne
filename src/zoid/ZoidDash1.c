#include "zoid.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void ZoidWalkSusumu(ZoidState *zoid);

void ZoidDash1(ZoidState *zoid)
{
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, 7);
        zoid->action_phase = 1;
        break;
    default:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action = ZOID_ACTION_WALK;
            zoid->requested_action = 0;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
        } else {
            zoid->action_phase++;
            ZoidWalkSusumu(zoid);
            if (zoid->action_phase < 30) {
                zoid->field_1A74 *= 1.1;
                zoid->field_1A74 += 0.01;
                zoid->forward_speed *= 1.1;
                zoid->forward_speed += 0.01;
            } else if (zoid->requested_action == ZOID_ACTION_JUMP_2) {
                zoid->action = zoid->requested_action;
                zoid->requested_action = 0;
            } else {
                zoid->field_1A74 *= 1.7;
                zoid->forward_speed *= 1.7;
            }
        }
        break;
    }
}
