#include "weapon.h"
#include "joint_matrix.h"

#define NULL 0

extern void sLsr1Set(Lsr *lsr);
extern void sLsr1Purge(Lsr1 *beam);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern s32 getEndF(HSD_JObj *joint);
extern void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !matrix_is_dirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjCopyMtx(HSD_JObj *jobj, f32 mtx[3][4])
{
    if (!jobj)
        __assert("jobj.h", 1173, "jobj");
    if (!mtx)
        __assert("jobj.h", 1174, "mtx");
    PSMTXCopy(mtx, jobj->matrix);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

void sLsrMove(void)
{
    s32 i;
    s32 r;
    s32 c;
    Lsr *lsr;
    Lsr1 *beam;

    for (i = 0; i < 11; i++) {
        lsr = &sLsr[i];
        if (lsr->archive != NULL) {
            for (r = 0; r < 3; r++) {
                for (c = 0; c < 4; c++) {
                    lsr->end[r][c] = lsr->start[r][c];
                    lsr->start[r][c] = lsr->source->matrix[r][c];
                }
            }
            sLsr1Set(lsr);
        }
    }
    for (i = 0; i < 400; i++) {
        beam = &sLsr1[i];
        if (beam->joint != NULL) {
            HSD_JObjAnimAll(beam->joint);
            if (getEndF(beam->joint) != 0) {
                sLsr1Purge(beam);
            } else {
                HSD_JObjCopyMtx(beam->joint, beam->start);
                HSD_JObjCopyMtx(beam->start_joint, beam->start);
                HSD_JObjCopyMtx(beam->end_joint, beam->end);
            }
        }
    }
}
