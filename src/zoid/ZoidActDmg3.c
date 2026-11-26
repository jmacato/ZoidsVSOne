#include "zoid.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void ZoidSusumuV(ZoidState *zoid);
extern void HSD_JObjAnimAll(HSD_JObj *joint);

/* unused; 2..8 repeat the ZoidActAtack, ZoidActStep and ZoidActDmg2 animation tables; keeps the unit's .rodata layout */
static const char dmg3Filler0[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static const u32 dmg3Filler1[41] = {0x00000000, 0x3E99999A, 0x3EAE147B, 0x3ECCCCCD, 0x3EF0A3D7, 0x3F000000, 0x3F11EB85, 0x3F19999A, 0x3F28F5C3, 0x3F30A3D7, 0x3F333333, 0x3F428F5C, 0x3F4A3D71, 0x3F4CCCCD, 0x3F54BC6A, 0x3F5D70A4, 0x3F666666, 0x3F6E147B, 0x3F75C28F, 0x3F7C28F6, 0x3F800000, 0x3F83D70A, 0x3F87AE14, 0x3F8A3D71, 0x3F8CCCCD, 0x3F8F5C29, 0x3F91EB85, 0x3F947AE1, 0x3F970A3D, 0x3F99999A, 0x3F9C28F6, 0x3F9EB852, 0x3FA147AE, 0x3FA3D70A, 0x3FA66666, 0x3FA8F5C3, 0x3FAB851F, 0x3FAE147B, 0x3FB0A3D7, 0x3FB33333, 0x00000000};
static const u32 dmg3Filler2[5] = {0x00000058, 0x0000005A, 0x0000005C, 0x0000005E, 0x00000060};
static const u32 dmg3Filler3[5] = {0x00000059, 0x0000005B, 0x0000005D, 0x0000005F, 0x00000061};
static const u32 dmg3Filler4[4] = {0x00000018, 0x0000001C, 0x00000020, 0x00000024};
static const u32 dmg3Filler5[4] = {0x00000019, 0x0000001D, 0x00000021, 0x00000025};
static const u32 dmg3Filler6[4] = {0x0000001A, 0x0000001E, 0x00000022, 0x00000026};
static const u32 dmg3Filler7[4] = {0x0000001B, 0x0000001F, 0x00000023, 0x00000027};
static const u32 dmg3Filler8[6] = {0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F, 0x00000030};

void ZoidActDmg3(ZoidState *zoid)
{
    s32 hit[6] = {49, 54, 59, 64, 74, 69};
    s32 fly[6] = {50, 55, 60, 65, 75, 70};
    s32 fall[6] = {51, 56, 61, 66, 76, 71};
    s32 down[6] = {52, 57, 62, 67, 77, 72};
    s32 rise[6] = {53, 58, 63, 68, 78, 73};
    ZoidControlData *control;
    s32 frame_padding[6];

    (void)dmg3Filler0;
    (void)dmg3Filler1;
    (void)dmg3Filler2;
    (void)dmg3Filler3;
    (void)dmg3Filler4;
    (void)dmg3Filler5;
    (void)dmg3Filler6;
    (void)dmg3Filler7;
    (void)dmg3Filler8;
    control = zoid->control;
    zoid->displacement[0] = 0.0f;
    zoid->displacement[1] = 0.0f;
    zoid->displacement[2] = 0.0f;
    if (zoid->requested_action == ZOID_ACTION_DMG2_0) {
        zoid->requested_action = 0;
    }
    if (zoid->requested_action == ZOID_ACTION_DMG3_0) {
        zoid->requested_action = 0;
    }
    zoid->death_pending = 0;
    if (zoid->action_phase > 16 && zoid->action_phase <= 48) {
        ZoidSusumuV(zoid);
        zoid->unsupported_frames = 0;
    }
    if (zoid->invulnerable_timer < 2) {
        zoid->invulnerable_timer = 2;
    }
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, hit[zoid->action - ZOID_ACTION_DMG3_1]);
        zoid->interpolation_remaining = 2;
        zoid->interpolation_duration = 2;
        zoid->action_phase = 1;
        zoid->invulnerable_timer = 120;
    case 1:
        zoid->death_pending = 0;
        zoid->field_1A34 = 0;
        if (zoid->animation_looped == 0 && zoid->animation_stopped == 0) {
            break;
        }
    case 16:
        ZoidSetAnim(zoid, fly[zoid->action - ZOID_ACTION_DMG3_1]);
        zoid->interpolation_remaining = 2;
        zoid->interpolation_duration = 2;
        zoid->action_phase = 17;
        break;
    case 17:
        if (zoid->action == ZOID_ACTION_DMG3_5) {
            if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
                break;
            }
        } else if (zoid->grounded == 0) {
            break;
        }
    case 32:
        zoid->launch_velocity.x *= 0.7;
        zoid->launch_velocity.y *= 0.7;
        zoid->launch_velocity.z *= 0.7;
        zoid->launch_velocity.y *= 0.3;
        ZoidSetAnim(zoid, fall[zoid->action - ZOID_ACTION_DMG3_1]);
        zoid->action_phase = 33;
    case 33:
        zoid->launch_velocity.y *= 0.3;
        zoid->field_1A34 = 0;
        zoid->launch_velocity.x *= 0.9;
        zoid->launch_velocity.y *= 0.9;
        zoid->launch_velocity.z *= 0.9;
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
        zoid->launch_velocity.y *= 0.3;
    case 48:
        zoid->field_1A34 = 0;
        ZoidSetAnim(zoid, down[zoid->action - ZOID_ACTION_DMG3_1]);
        zoid->action_phase = 49;
        zoid->down_frames = 0;
        zoid->launch_velocity.y *= 0.3;
    case 49:
        zoid->launch_velocity.y *= 0.3;
        zoid->death_pending = 1;
        if (zoid->health <= 0) {
            zoid->health = 0;
            zoid->action = ZOID_ACTION_DEAD;
            zoid->action_phase = 0;
            zoid->requested_action = ZOID_ACTION_DEAD;
            break;
        }
        if (zoid->down_frames >= control->down_input_frames) {
            if (zoid->requested_action == ZOID_ACTION_ATTACK_0) {
                zoid->action_phase = 80;
                break;
            }
            if (zoid->requested_action == ZOID_ACTION_JUMP_2) {
                zoid->action_phase = 96;
                break;
            }
        }
        zoid->down_frames++;
        if (zoid->down_frames > control->max_down_frames) {
            zoid->action_phase = 64;
        }
        break;
    case 64:
        ZoidSetAnim(zoid, rise[zoid->action - ZOID_ACTION_DMG3_1]);
        zoid->action_phase = 65;
    case 65:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    default:
    case 153:
        zoid->launch_velocity.x = 0.0f;
        zoid->launch_velocity.y = 0.0f;
        zoid->launch_velocity.z = 0.0f;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        zoid->action = ZOID_ACTION_WALK;
        zoid->requested_action = 0;
        ZoidSetAnim(zoid, 1);
        HSD_JObjAnimAll(zoid->joint);
        break;
    case 80:
        zoid->requested_action = 0;
        ZoidSetAnim(zoid, 83);
        zoid->action_phase = 81;
    case 81:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action_phase = 153;
        }
        break;
    case 96:
        zoid->requested_action = 0;
        ZoidSetAnim(zoid, 79);
        zoid->action_phase = 97;
    case 97:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
        ZoidSetAnim(zoid, 80);
        zoid->launch_velocity.y = 0.55f;
        zoid->launch_velocity.x = 0.0f;
        zoid->launch_velocity.z = 0.0f;
        zoid->action_phase = 98;
    case 98:
        ZoidSusumuV(zoid);
        if (zoid->launch_velocity.y > 0.0f) {
            break;
        }
        ZoidSetAnim(zoid, 81);
        zoid->action_phase = 99;
    case 99:
        ZoidSusumuV(zoid);
        if (zoid->grounded == 0 && zoid->ground_normal_count == 0) {
            break;
        }
    case 100:
        zoid->launch_velocity.x = 0.0f;
        zoid->launch_velocity.y = 0.0f;
        zoid->launch_velocity.z = 0.0f;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        ZoidSetAnim(zoid, 82);
        zoid->action_phase = 101;
    case 101:
        zoid->launch_velocity.x = 0.0f;
        zoid->launch_velocity.y = 0.0f;
        zoid->launch_velocity.z = 0.0f;
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action_phase = 153;
        }
        break;
    }
}
