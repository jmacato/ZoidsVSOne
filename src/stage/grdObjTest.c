#include "joint.h"
#include "zoid.h"
#include "missile.h"
#include "ground_object.h"

extern GroundObject obj[50];
extern s32 objNow;
extern s32 grdObjIn(GroundObject *object, Missile *missile);

void grdObjTest(void)
{
    GroundObject *object;
    s32 i;
    s32 j;
    Missile *missile;

    for (i = 0; i < objNow; i++) {
        object = &obj[i];
        if (object->joint != 0) {
            for (j = 0, missile = missileStart; j < 200; j++, missile++) {
                if (missile->joint != 0 && missile->owner != 0 && missile->owner->ai_active == 0) {
                    grdObjIn(object, missile);
                }
            }
        }
    }
}
