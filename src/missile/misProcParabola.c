#include "missile.h"
#include "matrix.h"
#include "joint_matrix.h"
#include "math_support.h"

extern void PSMTXRotRad(Mtx m, char axis, f32 rad);
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 atan2f(f32 y, f32 x);

static inline f32 sqrt4(f32 x, volatile f32 *y)
{
    f64 guess;
    if (x > 0.0f) {
        guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = x * guess;
        return *y;
    }
    return x;
}

void misProcParabola(Missile *missile)
{
    Mtx rot;
    f32 half;
    Vec3 velocity;
    volatile f32 root;
    s32 pad_stack[2];
    f32 angle;
    f32 previous;
    f32 current;
    f32 length;

    if (missile->matrix[1][1] < 0.0f) {
        PSMTXRotRad(rot, 'X', 3.1415925f);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    } else if (missile->matrix[1][2] != 0.0f) {
        angle = DEG2RAD_F(30.0f);
        if (missile->matrix[1][2] < 0.0f)
            angle = -angle;
        half = 0.5f;
        while (angle && missile->matrix[1][2]) {
            if (missile->matrix[1][2] < 0.0f) {
                while (missile->matrix[1][2] < 0.0f) {
                    PSMTXRotRad(rot, 'X', angle);
                    PSMTXConcat(missile->matrix, rot, missile->matrix);
                }
                if (missile->matrix[1][2] > 0.0f)
                    angle = -(angle * half);
            } else if (missile->matrix[1][2] > 0.0f) {
                while (missile->matrix[1][2] > 0.0f) {
                    PSMTXRotRad(rot, 'X', angle);
                    PSMTXConcat(missile->matrix, rot, missile->matrix);
                }
                if (missile->matrix[1][2] < 0.0f)
                    angle = -(angle * half);
            }
        }
    }
    velocity.x = missile->matrix[0][0] * missile->speed;
    velocity.y = missile->matrix[1][0] * missile->speed;
    velocity.z = missile->matrix[2][0] * missile->speed;
    previous = velocity.y;
    velocity.y = velocity.y - 0.025;
    current = velocity.y;
    missile->speed = sLenPoint3dR(&velocity);
    if (missile->speed > 0.1) {
        length = sqrt4(velocity.x * velocity.x + velocity.z * velocity.z, &root);
        if (length > 0.1) {
            current = atan2f(length, current);
            angle = atan2f(length, previous) - current;
            if (angle) {
                PSMTXRotRad(rot, 'Z', angle);
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            }
        } else {
            PSMTXRotRad(rot, 'Z', DEG2RAD_F(2.0f));
            PSMTXConcat(missile->matrix, rot, missile->matrix);
        }
    }
}
