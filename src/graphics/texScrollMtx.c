#include "tobj.h"

void texScrollMtx(HSD_TObj *texture, f32 matrix[3][4])
{
    if (texture != 0) {
        texture->wrap_s = GX_REPEAT;
        texture->wrap_t = GX_REPEAT;
        texture->mtx[0][0] = matrix[0][0];
        texture->mtx[0][1] = matrix[0][1];
        texture->mtx[0][2] = matrix[0][2];
        texture->mtx[0][3] = matrix[0][3];
        texture->mtx[1][0] = matrix[1][0];
        texture->mtx[1][1] = matrix[1][1];
        texture->mtx[1][2] = matrix[1][2];
        texture->mtx[1][3] = matrix[1][3];
        texture->mtx[2][0] = matrix[2][0];
        texture->mtx[2][1] = matrix[2][1];
        texture->mtx[2][2] = matrix[2][2];
        texture->mtx[2][3] = matrix[2][3];
    }
}
