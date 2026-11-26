#include "zoid.h"
#include "ground_collision.h"

extern s32 zdGroundCoPoly(ZoidState *zoid, CoObj *object, s32 index, GroundPolygon *polygon, s32 mode);
extern void angLimit(f32 *angle);

s32 zdGroundPoly(ZoidState *zoid, s32 index, GroundPolygon *polygon)
{
    s32 *ground_modes = zoid->control->ground_modes;
    s32 part;
    f32 angle;
    f32 heading;
    const f64 turn_limit = 2.0 * 3.1415926 * 0.5 / 360.0;

    zoid->ground_turn = 0.0f;
    if (zdGroundCoPoly(zoid, &zoid->body_coobj, index, polygon, 0) == 0)
        return 0;
    zdGroundCoPoly(zoid, &zoid->bust_coobj, index, polygon, ground_modes[2]);
    zdGroundCoPoly(zoid, &zoid->neck_coobj, index, polygon, ground_modes[1]);
    zdGroundCoPoly(zoid, &zoid->head_coobj, index, polygon, ground_modes[0]);
    for (part = 0; part < 8; part++)
        zdGroundCoPoly(zoid, &zoid->tail_coobjs[part], index, polygon, ground_modes[part + 4]);
    zdGroundCoPoly(zoid, &zoid->hip_coobj, index, polygon, ground_modes[3]);
    zdGroundCoPoly(zoid, &zoid->l_arm1_coobj, index, polygon, ground_modes[14]);
    zdGroundCoPoly(zoid, &zoid->r_arm1_coobj, index, polygon, ground_modes[16]);
    zdGroundCoPoly(zoid, &zoid->l_leg1_coobj, index, polygon, ground_modes[18]);
    zdGroundCoPoly(zoid, &zoid->r_leg1_coobj, index, polygon, ground_modes[20]);
    zdGroundCoPoly(zoid, &zoid->l_arm2_coobj, index, polygon, ground_modes[15]);
    zdGroundCoPoly(zoid, &zoid->r_arm2_coobj, index, polygon, ground_modes[17]);
    zdGroundCoPoly(zoid, &zoid->l_leg2_coobj, index, polygon, ground_modes[19]);
    zdGroundCoPoly(zoid, &zoid->r_leg2_coobj, index, polygon, ground_modes[21]);
    angle = zoid->ground_turn;
    angLimit(&angle);
    if (angle < -turn_limit)
        angle = -turn_limit;
    if (angle > turn_limit)
        angle = turn_limit;
    zoid->ground_turn = angle;
    heading = zoid->heading;
    zoid->heading = heading + angle;
    return 1;
}

