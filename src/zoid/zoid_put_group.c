#pragma readonly_strings on
#include "zoid.h"
#include "ground_collision.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

/* no code in this file reads these statics; they keep the unit's .rodata layout */
static const char s393[] = "zoid/stels_mat.dat";
static const char s394[] = "debug/c_.dat";
static const char s430[] = "zoid purge! [%s] \n";
static const char s474[] = "joint error [%s] \n ============";
static const char s575[] = "zoid/%s.dat";
static const char s628[] = "mtp_0_joint";
static const char s629[] = "mtp_1_joint";
static const char s630[] = "mtp_2_joint";
static const char s631[] = "mtp_3_joint";
static const char s632[] = "mtp_4_joint";
static const char s633[] = "mtp_5_joint";
static const char s634[] = "mtp_6_joint";
static const char s635[] = "mtp_7_joint";
static const char s636[] = "mtp_8_joint";
static const char s637[] = "mtp_9_joint";
static const char s638[] = "BUST1_joint";
static const char s639[] = "HIP1_joint";
static const char s640[] = "L_ARM1_joint";
static const char s641[] = "R_ARM1_joint";
static const char s642[] = "L_ARM2_joint";
static const char s643[] = "R_ARM2_joint";
static const char s644[] = "L_HAND_joint";
static const char s645[] = "R_HAND_joint";
static const char s646[] = "NECK1_joint";
static const char s647[] = "HEAD1_joint";
static const char s648[] = "L_LEG1_joint";
static const char s649[] = "L_LEG2_joint";
static const char s650[] = "R_LEG1_joint";
static const char s651[] = "R_LEG2_joint";
static const char s652[] = "L_FOOT_joint";
static const char s653[] = "R_FOOT_joint";
static const char s654[] = "TEAL1_joint";
static const char *const sWeaponSlotJointNames[28] = {s628, s629, s630, s631, s632, s633, s634, s635, s636, s637, s638, s639, s640, s641, s642, s643, s644, s645, s646, s647, s648, s649, s650, s651, s652, s653, s654, 0};
static const s32 s704[20] = {180, 172, 171, 204, 180, 205, 153, 180, 180, 158, 214, 153, 221, 157, 221, 148, 220, 230, 140, 180};
static const s32 s705[20] = {32, 17, 14, 27, 34, 20, 15, 23, 1, 14, 32, 36, 21, 41, 68, 41, 91, 22, 25, 6};
static const s32 s706[20] = {39, 28, 27, 30, 41, 35, 30, 43, 35, 24, 38, 40, 46, 50, 65, 63, 85, 30, 30, 40};
static const char s879[] = "zoid/HG/%s.dat";
static const char s881[] = "scene_data";
static const char s882[] = "f_base_joint";
static const char s883[] = "b_base_joint";
static const char s884[] = "base_joint";
static const char s885[] = "R_glove_joint";
static const char s886[] = "L_glove_joint";
static const char s887[] = "R_shoe_joint";
static const char s888[] = "L_shoe_joint";
static const char s889[] = "senter_joint";
static const char s890[] = "berut1_joint";
static const char s891[] = "cap_joint";
static const char s892[] = "collar_joint";
static const char s893[] = "jacket_joint";
static const char s894[] = "fly_joint";
static const char s895[] = "to_fly_joint";
static const char s896[] = "to_to_fly_joint";
static const char s897[] = "to_to_to_fly_joint";
static const char s898[] = "to_to_to_to_fly_joint";
static const char s899[] = "to_to_to_to_to_fly_joint";
static const char s900[] = "to_to_to_to_to_to_fly_joint";
static const char s901[] = "to_to_to_to_to_to_to_fly_joint";
static const char s902[] = "buckle_joint";
static const char s903[] = "NAVEL_joint";
static const char s904[] = "STATE_joint";
static const char s905[] = "c_BODY_joint";
static const char s906[] = "c_head_joint";
static const char s907[] = "c_neck_joint";
static const char s908[] = "c_bust_joint";
static const char s909[] = "c_hip_joint";
static const char s910[] = "c_tail_joint";
static const char s911[] = "c_tail%d_joint";
static const char s912[] = "c_l_arm1_joint";
static const char s913[] = "c_l_arm2_joint";
static const char s914[] = "c_r_arm1_joint";
static const char s915[] = "c_r_arm2_joint";
static const char s916[] = "c_l_leg1_joint";
static const char s917[] = "c_l_leg2_joint";
static const char s918[] = "c_r_leg1_joint";
static const char s919[] = "c_r_leg2_joint";
static const char s920[] = "c_l_foot_joint";
static const char s921[] = "c_r_foot_joint";
static const char s922[] = "a_%1d_joint";
static const char sZoidPrmPathFormat[] = "zoid/%s.prm";
static const char s928[] = "jobjLook error \n";
static const char s929[] = "===================zoid OK============\n";
static const char s936[] = "zd color =%d \n";
static const char s944[] = "mount [%s] -- ";
static const char s983[] = "option set!------ [no.%d] ---------\n";
static const char s1249[] = "add power z%d \222e=%d , \212i\223\254=%d \n";

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
#define JOBJ_USE_QUATERNION 0x20000


extern void __assert(const char *file, s32 line, const char *expr);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ik3d(ZoidState *zoid, FootJoint *foot);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 x)
{
    if (jobj == NULL)
        __assert("jobj.h", 676, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[0] = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 z)
{
    if (jobj == NULL)
        __assert("jobj.h", 716, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

extern f32 zdGetBasePoly(ZoidState *zoid, f32 *point);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void sLinier3d(f32 *current, f32 *target, f32 fraction);
extern void chkDeep(FootJoint *foot, s32 *found, f32 *minimum);
extern f32 sLenPoint3dR(f32 *point);
extern void sSetRxRzF(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz);
extern void sSetRxRzB(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz);

void ZoidPutXZ(ZoidState *zoid)
{
    u8 unused0[4];
    f32 rx;
    f32 rz;
    u8 unused1[8];
    f32 deep;
    s32 found;
    f32 cur[3];
    f32 prev[3];
    f32 back[3];
    f32 top[3];
    f32 test[3];
    u8 unused2[4];
    f32 pos[3];
    u8 unused3[4];
    u16 selector;
    u8 unused4[92];
    f32 y;
    f32 low;
    f32 dx;
    f32 dz;
    f32 len;
    f32 add;
    HSD_JObj *jobj;
    u16 poly;
    s32 mode;
    s32 lifted;
    ZoidControlData *control;
    s32 landed;
    s32 count;
    s32 supported;
    s32 all_supported;
    s32 any;
    s32 i;
    s32 k;

    lifted = 0;
    landed = 0;
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    control = zoid->control;
    mode = zoid->current_animation;
    if (mode == 2)
        mode = 1;
    y = zdGetBasePoly(zoid, zoid->position);
    poly = zoid->ground_polygon;
    zoid->ground_height = y;
    jobj = zoid->sweep_joint;
    if (jobj != 0) {
        for (i = 0; i < 3; i++) {
            cur[i] = zoid->position[i];
            prev[i] = zoid->previous_position[i];
            top[i] = jobj->matrix[i][3];
        }
        for (k = 0; k < 10; k++) {
            len = 0.1 * (10 - k);
            for (i = 0; i < 3; i++) {
                back[i] = prev[i];
                test[i] = top[i];
            }
            sLinier3d(back, cur, len);
            for (i = 0; i < 3; i++)
                test[i] -= cur[i] - back[i];
            if (!(zdColPosY(test, NULL) > test[1]))
                break;
        }
        for (i = 0; i < 3; i++)
            zoid->position[i] = back[i];
        for (i = 0; i < 3; i++)
            pos[i] = jobj->matrix[i][3];
        rx = zdColPosY(pos, &selector) - jobj->matrix[1][3];
        if (rx > 1.0f)
            rx = 0.0f;
        if (rx > 0.0f) {
            if (zoid->death_pending != 0 && rx > 0.025)
                rx = 0.025f;
            zoid->position[1] += rx;
        }
    }
    if (y - zoid->position[1] < zoid->field_19FC - 0.2) {
        lifted = 1;
        y = zoid->position[1] + (f32)(zoid->field_19FC - 0.2);
    }
    low = y;
    if (control->field_00F8 != 0) {
        any = 0;
        if (control->field_00F8 == 2) {
            if (mode == 4 || mode == 5)
                any = 1;
        } else {
            any = 1;
        }
        if (any) {
            zoid->height_offset = 0.0f;
            landed = 1;
            if (zoid->position[1] < y)
                zoid->position[1] = y;
        }
    }
    if (zoid->field_1A34 == 0) {
        found = 0;
        deep = 100.0f;
        count = 0;
        supported = 0;
        all_supported = 1;
        if (landed == 0) {
            if (control->field_00F4 != 2) {
                if (zoid->feet[0].joint != 0) {
                    chkDeep(&zoid->feet[0], &found, &deep);
                    if (low > zoid->feet[0].ground)
                        low = zoid->feet[0].ground;
                    count++;
                    if (!(zoid->feet[0].flags & FOOT_FLAG_SUPPORTED))
                        all_supported = 0;
                    else
                        supported++;
                }
                if (zoid->feet[1].joint != 0) {
                    chkDeep(&zoid->feet[1], &found, &deep);
                    if (low > zoid->feet[1].ground)
                        low = zoid->feet[1].ground;
                    count++;
                    if (!(zoid->feet[1].flags & FOOT_FLAG_SUPPORTED))
                        all_supported = 0;
                    else
                        supported++;
                }
            }
            if (zoid->feet[2].joint != 0) {
                chkDeep(&zoid->feet[2], &found, &deep);
                if (low > zoid->feet[2].ground)
                    low = zoid->feet[2].ground;
                count++;
                if (!(zoid->feet[2].flags & FOOT_FLAG_SUPPORTED))
                    all_supported = 0;
                else
                    supported++;
            }
            if (zoid->feet[3].joint != 0) {
                chkDeep(&zoid->feet[3], &found, &deep);
                if (low > zoid->feet[3].ground)
                    low = zoid->feet[3].ground;
                count++;
                if (!(zoid->feet[3].flags & FOOT_FLAG_SUPPORTED))
                    all_supported = 0;
                else
                    supported++;
            }
            add = 0.0002f;
            any = 0;
            if (all_supported == 0) {
                if (found == 0 || !(deep > 0.2))
                    any = 1;
            }
            if (zoid->feet[3].joint != 0 && !(zoid->feet[3].flags & FOOT_FLAG_CONTACT))
                any = 1;
            if (zoid->feet[2].joint != 0 && !(zoid->feet[2].flags & FOOT_FLAG_CONTACT))
                any = 1;
            if (any) {
                if (zoid->height_offset_speed >= 0.0f)
                    zoid->height_offset_speed = 0.0f;
                if (mode == 4 || mode == 5)
                    add *= 0.1;
                zoid->height_offset_speed -= add;
                if (count - supported >= 2)
                    zoid->height_offset_speed -= add;
            }
            if (zoid->height_offset_speed > 0.01)
                zoid->height_offset_speed = 0.01f;
            if (zoid->height_offset_speed < -0.01)
                zoid->height_offset_speed = -0.01f;
            zoid->height_offset += zoid->height_offset_speed;
        }
        if (found != 0) {
            if (deep > 0.3)
                zoid->height_offset += 0.0001;
            if (deep > 0.7)
                zoid->height_offset += 0.005;
            if (deep > 1.0f)
                zoid->height_offset += 0.01;
            zoid->height_offset_speed = 0.0f;
        }
        if (zoid->field_1B24 != 0)
            zoid->field_1B24--;
        if (mode > 3 && landed != 0)
            supported = 1;
        if (supported == 0 || lifted != 0) {
            zoid->unsupported_frames++;
            if (zoid->unsupported_frames > control->max_unsupported_frames && zoid->field_19F0 == 0 && control->field_00F8 == 0) {
                zoid->action = ZOID_ACTION_JUMP_1;
                zoid->jump_phase = 32;
                zoid->velocity[0] = 0.0f;
                zoid->velocity[1] = -0.001f;
                zoid->velocity[2] = 0.0f;
                zoid->unsupported_frames = 0;
                zoid->action = ZOID_ACTION_JUMP_2;
                if (0.0f == zoid->displacement[1])
                    zoid->displacement[1] = -0.001f;
                len = sLenPoint3dR(zoid->displacement);
                if (len > 0.7) {
                    zoid->displacement[0] *= 0.7 / len;
                    zoid->displacement[1] *= 0.7 / len;
                    zoid->displacement[2] *= 0.7 / len;
                }
                return;
            }
        } else {
            zoid->unsupported_frames = 0;
        }
        if (zoid->height_offset < low - y - 2.0f)
            zoid->height_offset = low - y - 2.0f;
        zoid->position[1] = y;
    }
    if (y > zoid->ground_height && zoid->height_offset < 0.0f) {
        dx = y - zoid->ground_height;
        if (dx > -zoid->height_offset) {
            y += zoid->height_offset;
            zoid->height_offset = 0.0f;
        } else {
            y = zoid->ground_height;
            zoid->height_offset += dx;
        }
        zoid->position[1] = y;
    }
    rx = 0.0f;
    rz = 0.0f;
    if (poly != GROUND_POLYGON_NONE)
        sColGetRxRz(&grdcNormal[grdcPolygon[poly].normal_index], zoid->heading, &rx, &rz);
    if (rx > DEG(30))
        rx = DEG(30);
    if (rz > DEG(30))
        rz = DEG(30);
    if (rx < -DEG(30))
        rx = -DEG(30);
    if (rz < -DEG(30))
        rz = -DEG(30);
    dx = rx - zoid->ground_rx;
    dz = rz - zoid->ground_rz;
    if (dx > 0.0017453292482296542)
        dx = 0.0017453292482296542;
    if (dx < -0.0017453292482296542)
        dx = -0.0017453292482296542;
    if (dz > 0.005235987874726123)
        dz = 0.005235987874726123;
    if (dz < -0.005235987874726123)
        dz = -0.005235987874726123;
    zoid->ground_rx += dx;
    zoid->ground_rz += dz;
    zdSetXYZ(zoid);
    if (zoid->f_base_joint != 0) {
        if (control->field_00F4 != 2) {
            sSetRxRzF(zoid, &zoid->feet[1], &zoid->feet[0], &rx, &rz);
            if (rx > DEG(30))
                rx = DEG(30);
            if (rz > DEG(30))
                rz = DEG(30);
            if (rx < -DEG(30))
                rx = -DEG(30);
            if (rz < -DEG(30))
                rz = -DEG(30);
            dx = rx - zoid->f_base_rx;
            dz = rz - zoid->f_base_rz;
            if (dx > 0.005235987874726123)
                dx = 0.005235987874726123;
            if (dx < -0.005235987874726123)
                dx = -0.005235987874726123;
            if (dz > 0.005235987874726123)
                dz = 0.005235987874726123;
            if (dz < -0.005235987874726123)
                dz = -0.005235987874726123;
            zoid->f_base_rx += dx;
            zoid->f_base_rz += dz;
            HSD_JObjSetRotationX(zoid->f_base_joint, zoid->f_base_rx);
            HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->f_base_rz);
        } else {
            HSD_JObjSetRotationX(zoid->f_base_joint, zoid->ground_rx);
            HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->ground_rz);
        }
    }
    if (zoid->b_base_joint != 0 && control->field_00F4 != 0) {
        sSetRxRzB(zoid, &zoid->feet[3], &zoid->feet[2], &zoid->field_1AA4, &zoid->field_1AA8);
        HSD_JObjSetRotationX(zoid->b_base_joint, zoid->ground_rx);
        HSD_JObjSetRotationZ(zoid->b_base_joint, zoid->ground_rz);
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    zoid->ground_normal_count = 0;
    zoid->ground_normal_sum[0] = 0.0f;
    zoid->ground_normal_sum[1] = 0.0f;
    zoid->ground_normal_sum[2] = 0.0f;
    if (control->field_00F4 != 2) {
        ik3d(zoid, &zoid->feet[0]);
        ik3d(zoid, &zoid->feet[1]);
    }
    ik3d(zoid, &zoid->feet[2]);
    ik3d(zoid, &zoid->feet[3]);
    if (zoid->unsupported_frames < 0)
        zoid->unsupported_frames = 0;
}

void ZoidPutJumpingXZ(ZoidState *zoid)
{
    ZoidControlData *control;
    u8 frame_padding[0x10];

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    control = zoid->control;
    if (zoid->height_offset < 0.0f) {
        zoid->height_offset += 0.02;
    }
    if (zoid->height_offset > 0.0f) {
        zoid->height_offset -= 0.02;
    }
    zdSetXYZ(zoid);
    if (zoid->f_base_joint != 0 && control->field_00F4 == 4) {
        if (zoid->f_base_rx > 0.0f) {
            zoid->f_base_rx -= DEG(5);
        }
        if (zoid->f_base_rx < 0.0f) {
            zoid->f_base_rx += DEG(5);
        }
        if (zoid->f_base_rz > 0.0f) {
            zoid->f_base_rz -= DEG(5);
        }
        if (zoid->f_base_rz < 0.0f) {
            zoid->f_base_rz += DEG(5);
        }
        HSD_JObjSetRotationX(zoid->f_base_joint, zoid->f_base_rx);
        HSD_JObjSetRotationZ(zoid->f_base_joint, zoid->f_base_rz);
    }
    if (zoid->b_base_joint != 0 && control->field_00F4 != 0) {
        if (zoid->ground_rx > 0.0f) {
            zoid->ground_rx -= DEG(5);
        }
        if (zoid->ground_rx < 0.0f) {
            zoid->ground_rx += DEG(5);
        }
        if (zoid->ground_rz > 0.0f) {
            zoid->ground_rz -= DEG(5);
        }
        if (zoid->ground_rz < 0.0f) {
            zoid->ground_rz += DEG(5);
        }
        HSD_JObjSetRotationX(zoid->b_base_joint, zoid->ground_rx);
        HSD_JObjSetRotationZ(zoid->b_base_joint, zoid->ground_rz);
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    zoid->ground_normal_count = 0;
    zoid->ground_normal_sum[0] = 0.0f;
    zoid->ground_normal_sum[1] = 0.0f;
    zoid->ground_normal_sum[2] = 0.0f;
    if (control->field_00F4 != 2) {
        ik3d(zoid, &zoid->feet[0]);
        ik3d(zoid, &zoid->feet[1]);
    }
    ik3d(zoid, &zoid->feet[2]);
    ik3d(zoid, &zoid->feet[3]);
}

static const char s4445[] = "wp dmg %d \n";
static const char s6574[] = "debug/mtp_grid.dat";

typedef struct PicHeader {
    u8 reserved_00[0x10];
    s32 format;
    u8 reserved_14[4];
    s32 width;
    s32 height;
    u8 reserved_20[0x2C];
    u16 colors;
} PicHeader;

extern PicHeader *skipPicData(u8 *data);
extern u32 calc_doltexture_size(s32 format, s32 width, s32 height);
extern void putErr(const char *message);
extern void OSReport(const char *format, ...);
extern void MemCpy(u8 *source, u8 *destination, s32 size);
extern void DCFlushRange(void *memory, u32 size);
extern void GXInvalidateTexAll(void);

#pragma push
#pragma opt_common_subs off
s32 zdSetTex(u8 *data, u8 *texture, u32 size)
{
    PicHeader *pic;
    s32 colors;
    u8 *image;
    u32 tsize;

    pic = skipPicData(data);
    if (pic->format != 10) {
        colors = 256;
    } else {
        s32 n = pic->colors;

        colors = n;
        if (n > 1024) {
            putErr("tex-size  large      >1024");
            return 0;
        }
    }
    image = (u8 *)pic + 744 + (colors - 256) * 2;
    tsize = calc_doltexture_size(pic->format, pic->width, pic->height);
    if (tsize != size) {
        putErr("tex size \201\202 file-tex-size");
        OSReport("tex size=%d(%d,%d,[%d])    != tsize=%d \n", tsize, pic->width, pic->height, pic->format, size);
        if (pic->format != 14) {
            putErr("tex size \201\202 file-tex-size    file-tex not CMPR");
            OSReport("file -tex   not CMPR\n");
        }
        return 0;
    }
    OSReport("headsize=%d    size = %d \n", 744, tsize);
    MemCpy(image, texture, tsize);
    DCFlushRange(image, tsize);
    DCFlushRange(texture, tsize);
    GXInvalidateTexAll();
    return 1;
}

static const char s6756[] = "imgsize=%d tsize=%d \n";

typedef struct ColorImageDesc {
    u8 *image;
    u16 width;
    u16 height;
    s32 format;
} ColorImageDesc;

typedef struct ColorTObj {
    u8 reserved_00[0x58];
    ColorImageDesc *imagedesc;
} ColorTObj;

extern ColorTObj *searchTObj(HSD_JObj *joint);
extern void *sReadFileU(char *name, s32 mode);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 zdSetTex2(u8 *texture, u8 *image, s32 size);
extern void free(void *ptr);

#pragma pop
s32 ZoidColor(ZoidState *zoid, s32 color, s32 mode)
{
    char path[256];
    ColorTObj *tobj;
    HSD_JObj *joint;
    ColorImageDesc *desc;
    u8 *data;
    u8 *image;
    u32 tsize;

    if (color < 0)
        return 0;
    if (zoid == 0)
        return 0;
    if (zoid->joint == 0)
        return 0;
    if (zoid->color == color)
        return 1;
    {
        HSD_JObj *j = zoid->body_coobj.joint;

        joint = j;
        if (j == 0) {
            putErr("zoidColor : Zoid.coBody not found.");
            return 0;
        }
    }
    tobj = searchTObj(joint);
    if (tobj == 0) {
        putErr("zoidColor : tobj not found.");
        return 0;
    }
    desc = tobj->imagedesc;
    if (desc == 0) {
        putErr("zoidColor : imagedesc(tobj) not found.");
        return 0;
    }
    tsize = calc_doltexture_size(desc->format, desc->width, desc->height);
    image = desc->image;
    sprintf(path, "zoid/all_tex/%s_%c.tpl", zoid, color + 'A');
    data = sReadFileU(path, mode);
    if (data != 0) {
        if (zdSetTex2(data, image, tsize) != 0) {
            zoid->color = color;
            free(data);
            OSReport("tex2\n");
            return 1;
        }
    } else {
        sprintf(path, "zoid/all_tex/%s_%c.pic", zoid, color + 'A');
        data = sReadFileU(path, mode);
        if (data != 0 && zdSetTex(data, image, tsize) != 0) {
            zoid->color = color;
            free(data);
            OSReport("tex\n");
            return 1;
        }
    }
    if (data == 0) {
        putErr("zoidColor : file not found.");
        return 0;
    }
    OSReport("text set. error   zd-tex (%d,%d,[%d])\n", desc->width, desc->height, desc->format);
    if (desc->format != 14) {
        putErr("zoidColor : set Tex  error    zoid-tex not CMPR");
        OSReport("zoid -tex   not CMPR\n");
    }
    free(data);
    return 0;
}
