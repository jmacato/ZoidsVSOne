#include "zoid.h"
#include "zoid_collision.h"
#include "ground_collision.h"

#define JOBJ_HIDDEN 0x10

extern void HSD_JObjClearFlags(HSD_JObj *jobj, u32 flags);
extern void HSD_JObjSetFlags(HSD_JObj *jobj, u32 flags);
extern void HSD_ShadowAddObject(void *shadow, HSD_JObj *jobj);

s32 zdShadowLo(void *shadow, CoObj *co)
{
    s32 visible;
    f64 minimum_normal_y = 0.5;

    if (co == 0) {
        return 1;
    }
    if (co->joint == 0) {
        return 1;
    }
    visible = 1;
    if (co->ground_polygon_index != GROUND_POLYGON_NONE) {
        /* normal y of the polygon under the part; the member form changes the code */
        if (((f32 *)&grdcNormal[((u16 *)&grdcPolygon[co->ground_polygon_index])[2]])[1] < minimum_normal_y) {
            visible = 0;
        }
    }
    if (visible == 0) {
        HSD_JObjSetFlags(co->joint, JOBJ_HIDDEN);
        return 0;
    }
    HSD_JObjClearFlags(co->joint, JOBJ_HIDDEN);
    HSD_ShadowAddObject(shadow, co->joint);
    return 1;
}
