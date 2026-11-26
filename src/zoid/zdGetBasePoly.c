#include "zoid.h"
#include "ground_collision.h"

extern f32 zdColPosY(f32 *point, u16 *selector);

f32 zdGetBasePoly(ZoidState *zoid, f32 *point)
{
    GroundMask *mask = 0;
    Vec3 *normal = 0;
    u16 selector;
    u32 material;
    f32 y;

    y = zdColPosY(point, &selector);
    if (selector != GROUND_POLYGON_NONE) {
        material = grdcPolygon[selector].material;
        mask = &grdcMat[material];
        if (mask->bits[0] & 4) {
            if (zoid->ai_active == 0) {
                zoid->field_1B90 = 1;
                if (zoid->death_started == 0) {
                    zoid->death_started = 1;
                }
            }
        }
        normal = &grdcNormal[grdcPolygon[selector].normal_index];
    }
    zoid->ground_material = mask;
    zoid->ground_polygon = selector;
    zoid->ground_normal = normal;
    return y;
}
