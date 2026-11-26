#include "zoid.h"

extern void ZoidTrans(ZoidState *zoid, f32 transformation);

void zdStelON(ZoidState *zoid)
{
    f32 t;

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (zoid->stel_state == ZOID_STEL_OFF) {
        ZoidTrans(zoid, 1.0f);
        zoid->stel_state = ZOID_STEL_FADING;
    } else if (zoid->stel_state == ZOID_STEL_FADING) {
        t = zoid->transformation;
        t -= 0.04;
        if (t < 0.0f) {
            zoid->stel_state = ZOID_STEL_ON;
            t = 0.0f;
        }
        ZoidTrans(zoid, t);
    }
}

void zdStelOFF(ZoidState *zoid)
{
    f32 t;

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (zoid->stel_state == ZOID_STEL_ON) {
        ZoidTrans(zoid, 0.0f);
        zoid->stel_state = ZOID_STEL_FADING;
    } else if (zoid->stel_state == ZOID_STEL_FADING) {
        t = zoid->transformation;
        t += 0.02;
        if (t > 1.0) {
            t = 1.0f;
            zoid->stel_state = ZOID_STEL_OFF;
        }
        ZoidTrans(zoid, t);
    }
}
