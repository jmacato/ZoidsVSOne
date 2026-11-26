#include "zoid.h"
#include "game_zoid_data.h"

extern f32 sLenPoint3dR(Vec3 *point);
extern s32 hitCalc(ZoidState *attacker, s32 damage, ZoidState *zoid);

void ZoidCoAtackDmg(ZoidState *attacker, ZoidAttackObject *attack, ZoidState *zoid)
{
    s32 index;
    s32 damage;
    s32 health;
    f32 length;
    u8 frame_padding[8];
    Vec3 delta;
    u8 unused[32];
    Vec3 *pointer;
    s32 type = attacker->type;

    if (zoid->invulnerable_timer != 0) {
        return;
    }
    zoid->rumble_timer = 15;
    pointer = &delta;
    delta.x = zoid->position[0] - attack->joint->matrix[0][3];
    delta.y = zoid->position[1] - attack->joint->matrix[1][3];
    delta.z = zoid->position[2] - attack->joint->matrix[2][3];
    length = sLenPoint3dR(pointer);
    if (0.0f == length) {
        delta.x = zoid->position[0] - attacker->position[0];
        delta.y = zoid->position[1] - attacker->position[1];
        delta.z = zoid->position[2] - attacker->position[2];
        length = sLenPoint3dR(pointer);
    }
    if (0.0f == length) {
        delta.x = attacker->joint->matrix[0][0];
        delta.y = attacker->joint->matrix[1][0];
        delta.z = attacker->joint->matrix[2][0];
        length = sLenPoint3dR(&delta);
    }
    if (0.0f == length) {
        return;
    }
    zoid->knockback[0] += delta.x / length;
    zoid->knockback[1] += delta.y / length;
    zoid->knockback[2] += delta.z / length;
    index = attacker->action - ZOID_ACTION_ATTACK_0;
    if (attacker->current_animation == 86) {
        index = 5;
    }
    if (attacker->current_animation == 87) {
        index = 5;
    }
    if (index >= 0 && index <= 11) {
        damage = Tea_zoiddat[type].attack_damage[index];
    } else {
        damage = 10;
    }
    damage = hitCalc(attacker, damage, zoid);
    if (damage > 0) {
        zoid->health_bar_timer = 60;
    }
    health = zoid->health;
    zoid->health = health - damage;
    if (zoid->health < 0) {
        zoid->health = 0;
    }
    if (zoid->health == 0 && health != 0 && attacker->slot != zoid->slot) {
        attacker->kills++;
        attacker->field_1BDC += zoid->max_health;
        if (attacker->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
            attacker->field_1BE0 += zoid->max_health;
        }
    }
}
