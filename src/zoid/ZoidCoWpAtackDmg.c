#include "zoid.h"
#include "weapon.h"
#include "game_part_data.h"

extern f32 sLenPoint3dR(Vec3 *point);
extern s32 hitCalc(ZoidState *attacker, s32 damage, ZoidState *zoid);
extern void OSReport(const char *format, ...);

void ZoidCoWpAtackDmg(WeaponState *weapon, CoObj *co, ZoidState *zoid)
{
    ZoidState *owner;
    s32 frame_padding[1];
    Vec3 delta;
    s32 pad1[4];
    f32 length;
    s32 damage;
    s32 health;

    if (weapon != 0 && zoid->invulnerable_timer == 0) {
        owner = weapon->owner;
        zoid->rumble_timer = 15;
        delta.x = zoid->position[0] - co->joint->matrix[0][3];
        delta.y = zoid->position[1] - co->joint->matrix[1][3];
        delta.z = zoid->position[2] - co->joint->matrix[2][3];
        length = sLenPoint3dR(&delta);
        if (0.0f != length) {
            {
                f32 *v = zoid->knockback;
                v[0] += delta.x / length;
                v[1] += delta.y / length;
                v[2] += delta.z / length;
            }
            damage = hitCalc(owner, Tea_partsdat[weapon->type].contact_damage, zoid);
            OSReport("wp dmg %d \n", damage);
            if (damage > 0) {
                zoid->health_bar_timer = 60;
            }
            health = zoid->health;
            zoid->health = health - damage;
            if (zoid->health < 0) {
                zoid->health = 0;
            }
            if (health != 0 && zoid->health == 0 && owner != 0 && owner->slot != zoid->slot) {
                owner->kills++;
                owner->field_1BDC += zoid->max_health;
                if (owner->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
                    owner->field_1BE0 += zoid->max_health;
                }
            }
            if (owner != 0 && weapon->drain != 0 && owner->option_type == ZOID_OPTION_SHIELD) {
                owner->option_energy -= 900;
                if (owner->option_energy < 0) {
                    owner->option_energy = 0;
                }
            }
        }
    }
}
