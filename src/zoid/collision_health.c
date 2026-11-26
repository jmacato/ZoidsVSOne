#include "zoid_collision.h"

void setCoDmg2(CoObj *first, CoObj *second, CoDamage *damage)
{
    f32 first_ratio, second_ratio;
    damage->maximum_health = 0;
    damage->health = 0;
    if (first->maximum_health != 0) {
        first_ratio = first->health / first->maximum_health;
        damage->health = first->health;
        damage->maximum_health = first->maximum_health;
    } else {
        first_ratio = 1000.f;
    }
    if (second->maximum_health != 0) {
        second_ratio = second->health / second->maximum_health;
    } else {
        second_ratio = 1000.f;
    }
    if (first_ratio > second_ratio) {
        damage->health = second->health;
        damage->maximum_health = second->maximum_health;
    }
}
