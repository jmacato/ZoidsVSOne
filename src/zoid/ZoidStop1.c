#include "zoid.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void ZoidWalkSusumu(ZoidState *zoid);

void ZoidStop1(ZoidState *zoid)
{
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, 8);
        zoid->action_phase = 1;
        break;
    default:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action = ZOID_ACTION_WALK;
            zoid->requested_action = 0;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
            zoid->forward_speed = 0.0f;
            zoid->field_1A74 = 0.0f;
            zoid->ramped_speed = 0.0f;
            zoid->step_heading = zoid->heading;
        } else {
            zoid->action_phase++;
            ZoidWalkSusumu(zoid);
            if (zoid->action_phase < 30) {
                zoid->field_1A74 *= 0.9;
                zoid->field_1A74 -= 0.01;
                if (zoid->field_1A74 < 0.0f) {
                    zoid->field_1A74 = 0.0f;
                }
                zoid->forward_speed *= 0.9;
                zoid->forward_speed -= 0.01;
                if (zoid->forward_speed < 0.0f) {
                    zoid->forward_speed = 0.0f;
                }
            } else if (zoid->requested_action == ZOID_ACTION_JUMP_2) {
                zoid->action = zoid->requested_action;
                zoid->requested_action = 0;
                break;
            } else {
                zoid->field_1A74 *= 0.7;
                zoid->field_1A74 -= 0.02;
                if (zoid->field_1A74 < 0.0f) {
                    zoid->field_1A74 = 0.0f;
                }
                zoid->forward_speed *= 0.7;
                zoid->forward_speed -= 0.02;
                if (zoid->forward_speed < 0.0f) {
                    zoid->forward_speed = 0.0f;
                }
            }
            if (zoid->action_phase > 57) {
                zoid->forward_speed = 0.0f;
                zoid->field_1A74 = 0.0f;
                zoid->ramped_speed = 0.0f;
            }
        }
        break;
    }
}
