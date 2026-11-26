#include "game_text.h"

f32 putAscMtxLR_sp(f32 matrix[3][4], s32 font, char *text, s32 right_align, f32 spacing)
{
    Vec3 position;
    f32 x;
    f32 y;
    f32 z;

    x = matrix[0][3];
    position.x = x;
    y = matrix[1][3];
    position.y = y;
    z = matrix[2][3];
    position.z = z;
    return putAscLR_sp(&position, font, text, right_align, spacing);
}
