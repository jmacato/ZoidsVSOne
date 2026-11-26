#include "zoid.h"
#include "missile.h"

extern void misProcStraight(Missile *missile);
extern void misProcParabola(Missile *missile);
extern void misProcFloat(Missile *missile);
extern void misProcGround(Missile *missile);
extern void misProc00(Missile *missile, Vec3 *target_position);
extern void misProc01(Missile *missile, Vec3 *target_position);
extern void misProc02(Missile *missile, Vec3 *target_position);
extern void misProc03(Missile *missile, Vec3 *target_position);
extern void misProcAT50(Missile *missile, Vec3 *target_position);
extern void misProcAT20(Missile *missile, Vec3 *target_position);

void misProc(Missile *missile)
{
    Vec3 target_position;
    f32 (*mtx)[4];
    s32 i;


    switch (missile->proc) {
    case MISSILE_PROC_STRAIGHT:
        misProcStraight(missile);
        break;
    case MISSILE_PROC_PARABOLA:
        misProcParabola(missile);
        break;
    case MISSILE_PROC_FLOAT:
        misProcFloat(missile);
        break;
    case MISSILE_PROC_GROUND:
        misProcGround(missile);
        break;
    default:
        if (missile->target_zoid != 0 && missile->target_zoid->camera_joint != 0) {
            mtx = missile->target_zoid->camera_joint->matrix;
            for (i = 0; i < 3; i++) {
                (&target_position.x)[i] = mtx[i][3];
            }

            switch (missile->proc) {
            case MISSILE_PROC_00:
                misProc00(missile, &target_position);
                break;
            case MISSILE_PROC_01:
                misProc01(missile, &target_position);
                break;
            case MISSILE_PROC_02:
                misProc02(missile, &target_position);
                break;
            case MISSILE_PROC_03:
                misProc03(missile, &target_position);
                break;
            case MISSILE_PROC_AT50:
                misProcAT50(missile, &target_position);
                break;
            case MISSILE_PROC_AT20:
                misProcAT20(missile, &target_position);
                break;
            }
        }
        break;
    }
}
