#include "ground_collision.h"
#include "missile.h"
#include "matrix.h"
#include "joint_matrix.h"

extern void PSMTXRotRad(Mtx m, char axis, f32 rad);
extern void misProcParabola(Missile *missile);

void misProcGround(Missile *missile)
{
    Vec3 position;
    Vec3 local;
    u16 polygon_index;
    u8 pad[8];
    Mtx rot;
    s32 i;
    Vec3 *normal;
    Vec3 *point;
    f32 angle;

    if (missile->hit_ground == 0) {
        misProcParabola(missile);
        return;
    }
    point = &position;
    missile->speed = 0.0f;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] = missile->matrix[i][3];
    }
    sColPosY(point, &polygon_index);
    if (polygon_index == GROUND_POLYGON_NONE)
        return;
    normal = &grdcNormal[grdcPolygon[polygon_index].normal_index];
    if (normal == 0)
        return;
    for (i = 0; i < 3; i++) {
        (&position.x)[i] -= (&normal->x)[i];
    }

    PSMTXMultVec(missile->inverse, point, &local);
    angle = 0.0f;
    if (local.z > 3.1415926 / 180.0) {
        angle = -DEG2RAD_F(1.0f);
    }
    if (local.z < -3.1415926 / 180.0) {
        angle = DEG2RAD_F(1.0f);
    }
    if (angle) {
        PSMTXRotRad(rot, 'Y', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    angle = 0.0f;
    if (local.y > 3.1415926 / 180.0) {
        angle = DEG2RAD_F(1.0f);
    }
    if (local.y < -3.1415926 / 180.0) {
        angle = -DEG2RAD_F(1.0f);
    }
    if (angle) {
        PSMTXRotRad(rot, 'Z', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
}
