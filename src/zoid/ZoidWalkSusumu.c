#include "zoid.h"
#include "ground_collision.h"

extern f64 __frsqrte(f64);
extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern f64 cos(f64 angle);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void ZoidSisei(ZoidState *zoid);

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

static inline f32 fabsf(f32 *v)
{
    return (*(u32 *)v &= 0x7FFFFFFF, *v);
}

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

static inline f32 lenXZ(Vec3 *v, volatile f32 *y)
{
    return sqrtf(v->x * v->x + v->z * v->z, y);
}

void ZoidWalkSusumu(ZoidState *zoid)
{
    ZoidControlData *control;
    f32 speed;
    f32 target;
    f32 limit;
    Vec3 next;
    u8 pad0[4];
    u16 selector;
    u8 pad1[4];
    Vec3 delta;
    Vec3 camera;
    u16 camera_selector;
    u8 pad2[20];
    f32 adjust[3];
    u8 pad3[12];
    f32 abs0;
    f32 abs1;
    volatile f32 root;
    u8 pad4[36];
    f32 slope;
    f32 b;
    f32 dx;
    f32 v;
    f32 dz;
    f32 angle;
    f32 diff;
    f32 length;
    f32 unused;
    u16 normal;
    s32 blocked;
    s32 i;

    if (zoid != 0 && zoid->joint != 0) {
        control = zoid->control;
        target = zoid->steer;
        if (zoid->f_base_joint != 0) {
            abs0 = zoid->f_base_ry - target;
            if (fabsf(&abs0) < DEG(5)) {
                zoid->f_base_ry = target;
            }
            if (zoid->f_base_ry < target) {
                zoid->f_base_ry += DEG(3);
                if (zoid->f_base_ry > target) {
                    zoid->f_base_ry = target;
                }
            }
            if (zoid->f_base_ry > target) {
                zoid->f_base_ry -= DEG(3);
                if (zoid->f_base_ry < target) {
                    zoid->f_base_ry = target;
                }
            }
            if (zoid->f_base_ry > DEG((f32)control->max_f_base_ry)) {
                zoid->f_base_ry = DEG((f32)control->max_f_base_ry);
            }
            if (zoid->f_base_ry < -DEG((f32)control->max_f_base_ry)) {
                zoid->f_base_ry = DEG((f32)-control->max_f_base_ry);
            }
        }
        if (zoid->senter_joint != 0) {
            angle = zoid->senter_roll;
            if (zoid->current_animation == 5 || zoid->current_animation == 4) {
                limit = 10.0f * (zoid->steer * zoid->forward_speed);
            } else {
                limit = 0.0f;
            }
            if (limit < DEG((f32)-control->max_senter_roll)) {
                limit = DEG((f32)-control->max_senter_roll);
            }
            if (limit > DEG((f32)control->max_senter_roll)) {
                limit = DEG((f32)control->max_senter_roll);
            }
            if (angle > limit) {
                angle -= DEG(1);
                if (angle < limit) {
                    angle = limit;
                }
            }
            if (angle < limit) {
                angle += DEG(1);
                if (angle > limit) {
                    angle = limit;
                }
            }
            zoid->senter_roll = angle;
        }
        ZoidSisei(zoid);
        if (zoid->b_base_joint != 0) {
            angle = zoid->ground_rz + zoid->senter_roll;
            zoid->field_1AAC = angle;
            abs1 = angle;
            limit = fabsf(&abs1) - DEG(45);
            if (limit > 0.0f) {
                if (angle > 0.0f) {
                    v = limit;
                } else {
                    v = -limit;
                }
                zoid->slide_speed = v;
            } else {
                zoid->slide_speed = 0.0f;
            }
        }
        if (zoid->field_1AB8 != 0) {
            zoid->field_1AB8--;
            zoid->field_1A74 *= 0.9;
            zoid->forward_speed *= 0.9;
            zoid->ramped_speed *= 0.9;
        }
        next.x = zoid->forward_speed * sinf(zoid->heading) + zoid->position[0];
        next.y = zoid->position[1];
        next.z = zoid->forward_speed * cosf(zoid->heading) + zoid->position[2];
        next.y = zdColPosY(&next.x, &selector);
        if (selector == GROUND_POLYGON_NONE) {
            zoid->heading += 3.0f;
            zoid->position[0] = zoid->previous_position[0];
            zoid->position[1] = zoid->previous_position[1];
            zoid->position[2] = zoid->previous_position[2];
            return;
        }
        delta.x = next.x - zoid->position[0];
        camera.x = zoid->camera_joint->matrix[0][3];
        delta.y = next.y - zoid->position[1];
        camera.y = zoid->camera_joint->matrix[1][3];
        delta.z = next.z - zoid->position[2];
        camera.z = zoid->camera_joint->matrix[2][3];
        zdColPosY(&camera.x, &camera_selector);
        delta.y = next.y - zoid->ground_height;
        (void)&delta;
        length = lenXZ(&delta, &root);
        slope = delta.y;
        if (length != 0.0f) {
            blocked = 0;
            if (camera_selector != GROUND_POLYGON_NONE) {
                normal = grdcPolygon[camera_selector].normal_index;
                if (slope / length > 0.0f && grdcNormal[normal].y < cos(DEG(60))) {
                    blocked = 1;
                }
            }
            if (slope / length > 1.6) {
                blocked = 1;
            }
            if (blocked != 0) {
                zoid->forward_speed = 0.0f;
                zoid->ramped_speed = 0.0f;
                zoid->position[0] = zoid->previous_position[0];
                zoid->position[1] = zoid->previous_position[1];
                zoid->position[2] = zoid->previous_position[2];
                return;
            }
        }
        v = next.y - zoid->ground_height;
        angle = next.x - zoid->position[0];
        dz = next.z - zoid->position[2];
        b = zoid->forward_speed;
        length = zoid->ramped_speed * zoid->ramped_speed;
        diff = length - (angle * angle + v * v + dz * dz);
        if (zoid->ramped_speed >= 0.0f && b >= 0.0f) {
            if (diff > 0.0f) {
                zoid->forward_speed += 0.05;
                if (zoid->forward_speed > zoid->ramped_speed) {
                    zoid->forward_speed = zoid->ramped_speed;
                }
            }
            if (diff < 0.0f) {
                zoid->forward_speed -= 0.05;
                if (zoid->forward_speed < 0.0f) {
                    zoid->forward_speed = 0.0f;
                }
                if (zoid->forward_speed < zoid->ramped_speed) {
                    zoid->forward_speed = zoid->ramped_speed;
                }
            }
        } else if (zoid->ramped_speed >= 0.0f && b < 0.0f) {
            zoid->forward_speed += 0.05;
        } else if (zoid->ramped_speed < 0.0f && b >= 0.0f) {
            zoid->forward_speed -= 0.05;
        } else if (zoid->ramped_speed < 0.0f && b < 0.0f) {
            if (diff > 0.0f) {
                zoid->forward_speed -= 0.05;
                if (zoid->forward_speed < zoid->ramped_speed) {
                    zoid->forward_speed = zoid->ramped_speed;
                }
            }
            if (diff < 0.0f) {
                zoid->forward_speed += 0.05;
                if (zoid->forward_speed > 0.0f) {
                    zoid->forward_speed = 0.0f;
                }
                if (zoid->forward_speed > zoid->ramped_speed) {
                    zoid->forward_speed = zoid->ramped_speed;
                }
            }
        }
        speed = zoid->forward_speed;
        if (zoid->current_animation == 2 || zoid->current_animation == 1) {
            speed = 0.0f;
        }
        dx = speed * sinf(zoid->heading);
        angle = zoid->heading;
        dz = speed * cosf(angle);
        if (zoid->ground_normal_count != 0) {
            for (i = 0; i < 3; i++) {
                v = zoid->ground_normal_sum[i] /= (f32)zoid->ground_normal_count;
                if (v > 0.0f) {
                    v -= 0.3f;
                    if (v < 0.0f) {
                        v = 0.0f;
                    }
                }
                if (v < 0.0f) {
                    v += 0.3f;
                    if (v > 0.0f) {
                        v = 0.0f;
                    }
                }
                adjust[i] = 0.1 * v;
            }
            dx += adjust[0];
            dz += adjust[2];
        }
        zoid->position[0] += dx;
        zoid->position[2] += dz;
    }
}
