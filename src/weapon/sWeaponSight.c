#include "weapon.h"
#include "zoid.h"
#include "missile.h"

extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern f32 sLenPoint3dR(f32 *point);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);

void sWeaponSight(WeaponState *weapon)
{
    WeaponMarker *marker;
    s32 i;
    s32 k;
    Missile *source;
    ZoidState *target;
    f32 delta[3];
    f32 goal;


    if (weapon == 0)
        return;
    if (weapon->active == 0)
        return;
    if (weapon->bullet_kind != BULLET_KIND_AT20)
        return;
    for (i = 0; i < 20; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == 0)
            continue;
        source = marker->source;
        if (source != 0 && (source->joint == 0 || source->purge_timer != 0 || source->hit != 0)) {
            marker->joint = 0;
            marker->source = 0;
            marker->target = 0;
            continue;
        }
        target = marker->target;
        if (target != 0 && (target->death_started != 0 || target->stel_state == ZOID_STEL_ON)) {
            marker->joint = 0;
            marker->target = 0;
            marker->source = 0;
            continue;
        }
        for (k = 0; k < 3; k++) {
            goal = marker->joint->matrix[k][3];
            (&marker->position.x)[k] = sLiner(goal, (&marker->position.x)[k], weapon->rate);
            delta[k] = goal - (&marker->position.x)[k];
        }
        if (sLenPoint3dR(delta) < 0.5)
            marker->locked = 1;
        if (marker->locked != 0) {
            for (k = 0; k < 3; k++) {
                (&marker->position.x)[k] = marker->joint->matrix[k][3];
            }

            if (sLenJobj(marker->joint, weapon->owner->joint) > weapon->range)
                marker->joint = 0;
        }
    }
}
