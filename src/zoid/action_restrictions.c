#include "zoid.h"

void flyZoid(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0 && zoid->control->field_00F8 == 1) {
        switch (zoid->requested_action) {
        case ZOID_ACTION_JUMP_1:
        case ZOID_ACTION_JUMP_2:
        case ZOID_ACTION_STOP:
        case ZOID_ACTION_STEP_0:
        case ZOID_ACTION_STEP_1:
        case ZOID_ACTION_STEP_2:
        case ZOID_ACTION_STEP_3:
        case ZOID_ACTION_DASH:
        case ZOID_ACTION_STEP_REQUEST_0:
        case ZOID_ACTION_STEP_REQUEST_1:
        case ZOID_ACTION_STEP_REQUEST_2:
        case ZOID_ACTION_STEP_REQUEST_3:
            zoid->requested_action = 0;
            break;
        }
    }
}

void dmgZoid(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        if (zoid->requested_action >= ZOID_ACTION_DMG3_0 && zoid->requested_action <= ZOID_ACTION_DMG3_6 && zoid->action != ZOID_ACTION_WALK) {
            zoid->jump_phase = 0;
            switch (zoid->action) {
            case ZOID_ACTION_JUMP_1:
            case ZOID_ACTION_JUMP_2:
            case ZOID_ACTION_STOP:
            case ZOID_ACTION_ATTACK_0:
            case ZOID_ACTION_ATTACK_1:
            case ZOID_ACTION_ATTACK_2:
            case ZOID_ACTION_ATTACK_3:
            case ZOID_ACTION_ATTACK_4:
            case ZOID_ACTION_ATTACK_5:
            case ZOID_ACTION_ATTACK_6:
            case ZOID_ACTION_ATTACK_7:
            case ZOID_ACTION_ATTACK_8:
            case ZOID_ACTION_ATTACK_9:
            case ZOID_ACTION_STEP_0:
            case ZOID_ACTION_STEP_1:
            case ZOID_ACTION_STEP_2:
            case ZOID_ACTION_STEP_3:
            case ZOID_ACTION_DASH:
            case ZOID_ACTION_STEP_REQUEST_0:
            case ZOID_ACTION_STEP_REQUEST_1:
            case ZOID_ACTION_STEP_REQUEST_2:
            case ZOID_ACTION_STEP_REQUEST_3:
                zoid->action = ZOID_ACTION_WALK;
                break;
            }
        }
    }
}
