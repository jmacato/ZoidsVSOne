#pragma readonly_strings on
#include "zoid.h"
#include "ground_collision.h"

static const char s393[] = "zoid/stels_mat.dat";
static const char s394[] = "debug/c_.dat";
static const char s430[] = "zoid purge! [%s] \n";
static const char s474[] = "joint error [%s] \n ============";
static const char sZoidDatPathFormat[] = "zoid/%s.dat";
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
static const s32 sMountAngleDefaults[20] = {180, 172, 171, 204, 180, 205, 153, 180, 180, 158, 214, 153, 221, 157, 221, 148, 220, 230, 140, 180};
static const s32 sMountDistanceDefaults[20] = {32, 17, 14, 27, 34, 20, 15, 23, 1, 14, 32, 36, 21, 41, 68, 41, 91, 22, 25, 6};
static const s32 sMountHeightDefaults[20] = {39, 28, 27, 30, 41, 35, 30, 43, 35, 24, 38, 40, 46, 50, 65, 63, 85, 30, 30, 40};
static const char sZoidHGDatPathFormat[] = "zoid/HG/%s.dat";
static const char sSceneDataName[] = "scene_data";
static const char sFBaseJointName[] = "f_base_joint";
static const char sBBaseJointName[] = "b_base_joint";
static const char sBaseJointName[] = "base_joint";
static const char sRGloveJointName[] = "R_glove_joint";
static const char sLGloveJointName[] = "L_glove_joint";
static const char sRShoeJointName[] = "R_shoe_joint";
static const char sLShoeJointName[] = "L_shoe_joint";
static const char sSenterJointName[] = "senter_joint";
static const char sBerut1JointName[] = "berut1_joint";
static const char sCapJointName[] = "cap_joint";
static const char sCollarJointName[] = "collar_joint";
static const char sJacketJointName[] = "jacket_joint";
static const char sFlyJointName[] = "fly_joint";
static const char sToFly1JointName[] = "to_fly_joint";
static const char sToFly2JointName[] = "to_to_fly_joint";
static const char sToFly3JointName[] = "to_to_to_fly_joint";
static const char sToFly4JointName[] = "to_to_to_to_fly_joint";
static const char sToFly5JointName[] = "to_to_to_to_to_fly_joint";
static const char sToFly6JointName[] = "to_to_to_to_to_to_fly_joint";
static const char sToFly7JointName[] = "to_to_to_to_to_to_to_fly_joint";
static const char sBuckleJointName[] = "buckle_joint";
static const char sNavelJointName[] = "NAVEL_joint";
static const char sStateJointName[] = "STATE_joint";
static const char sCBodyJointName[] = "c_BODY_joint";
static const char sCHeadJointName[] = "c_head_joint";
static const char sCNeckJointName[] = "c_neck_joint";
static const char sCBustJointName[] = "c_bust_joint";
static const char sCHipJointName[] = "c_hip_joint";
static const char sCTailJointName[] = "c_tail_joint";
static const char sCTailJointFormat[] = "c_tail%d_joint";
static const char sCLArm1JointName[] = "c_l_arm1_joint";
static const char sCLArm2JointName[] = "c_l_arm2_joint";
static const char sCRArm1JointName[] = "c_r_arm1_joint";
static const char sCRArm2JointName[] = "c_r_arm2_joint";
static const char sCLLeg1JointName[] = "c_l_leg1_joint";
static const char sCLLeg2JointName[] = "c_l_leg2_joint";
static const char sCRLeg1JointName[] = "c_r_leg1_joint";
static const char sCRLeg2JointName[] = "c_r_leg2_joint";
static const char sCLFootJointName[] = "c_l_foot_joint";
static const char sCRFootJointName[] = "c_r_foot_joint";
static const char sAttackJointFormat[] = "a_%1d_joint";
static const char sZoidPrmPathFormat[] = "zoid/%s.prm";
static const char sJobjLookError[] = "jobjLook error \n";
static const char sZoidOK[] = "===================zoid OK============\n";
static const char s936[] = "zd color =%d \n";
static const char s944[] = "mount [%s] -- ";
static const char s983[] = "option set!------ [no.%d] ---------\n";
static const char s1249[] = "add power z%d \222e=%d , \212i\223\254=%d \n";
#include "game_zoid_data.h"
#include "archive.h"

#define NULL 0

typedef struct NameTable {
    const char *n[28];
} NameTable;

typedef struct ParamTable {
    s32 v[20];
} ParamTable;

extern s32 sZoidHG;

extern void __assert(const char *file, s32 line, const char *expr);
extern s32 sprintf(char *buffer, const char *format, ...);
extern void OSReport(const char *format, ...);
extern char *strcpy(char *dst, const char *src);
extern void ZoidPurge(ZoidState *zoid);
extern s32 fexist(char *name);
extern HSD_Archive *TEA_USBFileArchiveLoad(char *name, void **data);
extern HSD_Archive *sLoad(char *name, void **data);
extern HSD_JObj *HSD_JObjLoadJoint(HSD_JObjDesc *description);
extern void HSD_JObjAddAnimAll(HSD_JObj *joint, struct HSD_AnimJoint *animation, struct HSD_MatAnimJoint *material, struct HSD_ShapeAnimJoint *shape);
extern s32 jobjAnim(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern JointPose *makeJobj(void);
extern void stCopyObj(HSD_JObj *joint, JointPose *pose);
extern void stCopyMatMobj(HSD_JObj *joint, JointPose *pose);
extern void ZoidCopyAnim(ZoidState *zoid);
extern HSD_JObj *searchJoint(ZoidState *zoid, const char *name);
extern void searchJointFoot(ZoidState *zoid, FootJoint *foot, const char *name);
extern void searchJointCoObj(ZoidState *zoid, CoObj *part, const char *name, HSD_JObj *joint);
extern void zdCalcCoDmg(ZoidState *zoid);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void *getAnimAobj(HSD_JObj *joint);
extern ZoidControlData *sReadFileU(char *name, s32 usb);
extern void *malloc(u32 size);
extern void ZeroMemory(void *data, u32 size);

static inline f32 HSD_JObjGetTranslationY(HSD_JObj *jobj)
{
    if (jobj == NULL) {
        __assert("jobj.h", 1021, "jobj");
    }
    return jobj->translation.y;
}

static inline f32 HSD_JObjGetTranslationZ(HSD_JObj *jobj)
{
    if (jobj == NULL) {
        __assert("jobj.h", 1033, "jobj");
    }
    return jobj->translation.z;
}

s32 ZoidInit_(ZoidState *zoid, s32 type, s32 usb)
{
    char path[120];
    void *data;
    const char *names[28];
    char tail[200];
    char attack[200];
    s32 angles[20];
    s32 distances[20];
    s32 heights[20];
    s32 j;
    ZoidAIState *ai;
    HSD_JObj *look;
    ModelAnimation *model;
    char *name;
    ZoidControlData *param;
    ZoidControlData *defaults;
    ModelAnimationTable *scene;
    HSD_Archive *archive;
    s32 i;
    CameraMountInfo *entry;
    u8 pad[36];

    ZoidPurge(zoid);
    data = NULL;
    if (sZoidHG != 0) {
        sprintf(path, sZoidHGDatPathFormat, Tea_zoiddat[type].model_name);
        if (fexist(path) == 0) {
            sZoidHG = 0;
        }
    }
    if (sZoidHG == 0) {
        sprintf(path, sZoidDatPathFormat, Tea_zoiddat[type].model_name);
    }
    OSReport("%s\n", path);
    if (usb != 0) {
        archive = TEA_USBFileArchiveLoad(path, &data);
    } else {
        if (fexist(path) == 0) {
            return 0;
        }
        archive = sLoad(path, &data);
    }
    zoid->archive = archive;
    zoid->type = type;
    if (archive == NULL) {
        return 0;
    }
    HSD_ArchiveLoadDepends(archive, NULL, NULL, NULL);
    HSD_ArchiveResolveReference(archive, NULL);
    zoid->archive_data = data;
    scene = HSD_ArchiveGetPublicAddress(archive, (char *)sSceneDataName);
    zoid->animations = scene;
    if (scene == NULL) {
        ZoidPurge(zoid);
        return 0;
    }
    name = Tea_zoiddat[type].model_name;
    strcpy(zoid->name, name);
    if (scene->models != NULL) {
        zoid->joint = HSD_JObjLoadJoint(scene->models[0]->joint);
        model = scene->models[0];
        HSD_JObjAddAnimAll(zoid->joint,
                           model->joint_animations != NULL ? model->joint_animations[0] : NULL,
                           model->material_animations != NULL ? model->material_animations[0] : NULL,
                           model->shape_animations != NULL ? model->shape_animations[0] : NULL);
    }
    jobjAnim(zoid->joint);
    sMakeMatrix(zoid->joint);
    zoid->pose = makeJobj();
    stCopyObj(zoid->joint, zoid->pose);
    stCopyMatMobj(zoid->joint, zoid->pose);
    ZoidCopyAnim(zoid);
    *(NameTable *)names = *(NameTable *)sWeaponSlotJointNames;
    for (i = 0; i < 30; i++) {
        zoid->weapon_slots[i].joint = NULL;
    }
    for (i = 0; names[i] != NULL; i++) {
        zoid->weapon_slots[i].joint = searchJoint(zoid, names[i]);
    }
    zoid->f_base_joint = searchJoint(zoid, sFBaseJointName);
    zoid->b_base_joint = searchJoint(zoid, sBBaseJointName);
    if (zoid->f_base_joint == NULL) {
        zoid->f_base_joint = searchJoint(zoid, sBaseJointName);
    }
    if (zoid->b_base_joint == NULL) {
        zoid->b_base_joint = searchJoint(zoid, sBaseJointName);
    }
    zoid->foot_count = 0;
    searchJointFoot(zoid, &zoid->feet[0], sRGloveJointName);
    searchJointFoot(zoid, &zoid->feet[1], sLGloveJointName);
    searchJointFoot(zoid, &zoid->feet[2], sRShoeJointName);
    searchJointFoot(zoid, &zoid->feet[3], sLShoeJointName);
    zoid->senter_joint = searchJoint(zoid, sSenterJointName);
    if (zoid->senter_joint != NULL) {
        zoid->senter_translation_y = HSD_JObjGetTranslationY(zoid->senter_joint);
        zoid->senter_translation_z = HSD_JObjGetTranslationZ(zoid->senter_joint);
    }
    zoid->body_base_joint = searchJoint(zoid, sBerut1JointName);
    zoid->head_base_joint = searchJoint(zoid, sCapJointName);
    zoid->neck_base_joint = searchJoint(zoid, sCollarJointName);
    zoid->bust_base_joint = searchJoint(zoid, sJacketJointName);
    zoid->hip_base_joint = searchJoint(zoid, sBerut1JointName);
    zoid->tail_base_joints[0] = searchJoint(zoid, sFlyJointName);
    zoid->tail_base_joints[1] = zoid->tail_base_joints[0];
    zoid->tail_base_joints[2] = zoid->tail_base_joints[0];
    zoid->tail_base_joints[3] = zoid->tail_base_joints[0];
    zoid->tail_base_joints[4] = zoid->tail_base_joints[0];
    zoid->tail_base_joints[5] = zoid->tail_base_joints[0];
    zoid->tail_base_joints[6] = zoid->tail_base_joints[0];
    zoid->tail_base_joints[7] = zoid->tail_base_joints[0];
    zoid->limbs[1].joint = searchJoint(zoid, sToFly1JointName);
    zoid->limbs[2].joint = searchJoint(zoid, sToFly2JointName);
    zoid->limbs[3].joint = searchJoint(zoid, sToFly3JointName);
    zoid->limbs[4].joint = searchJoint(zoid, sToFly4JointName);
    zoid->limbs[5].joint = searchJoint(zoid, sToFly5JointName);
    zoid->limbs[6].joint = searchJoint(zoid, sToFly6JointName);
    zoid->limbs[7].joint = searchJoint(zoid, sToFly7JointName);
    zoid->limbs[8].joint = zoid->tail_base_joints[0];
    zoid->buckle_joint = searchJoint(zoid, sBuckleJointName);
    zoid->berut1_joint = searchJoint(zoid, sBerut1JointName);
    zoid->jacket_joint = searchJoint(zoid, sJacketJointName);
    zoid->collar_joint = searchJoint(zoid, sCollarJointName);
    zoid->navel_joint = searchJoint(zoid, sNavelJointName);
    zoid->animation_exclusion = searchJoint(zoid, sStateJointName);
    searchJointCoObj(zoid, &zoid->body_coobj, sCBodyJointName, zoid->body_base_joint);
    searchJointCoObj(zoid, &zoid->head_coobj, sCHeadJointName, zoid->head_base_joint);
    searchJointCoObj(zoid, &zoid->neck_coobj, sCNeckJointName, zoid->neck_base_joint);
    searchJointCoObj(zoid, &zoid->bust_coobj, sCBustJointName, zoid->bust_base_joint);
    searchJointCoObj(zoid, &zoid->hip_coobj, sCHipJointName, zoid->hip_base_joint);
    searchJointCoObj(zoid, &zoid->tail_coobjs[0], sCTailJointName, zoid->tail_base_joints[0]);
    for (i = 1; i < 8; i++) {
        sprintf(tail, sCTailJointFormat, i);
        searchJointCoObj(zoid, &zoid->tail_coobjs[i], tail, zoid->tail_base_joints[i]);
    }
    searchJointCoObj(zoid, &zoid->l_arm1_coobj, sCLArm1JointName, zoid->feet[1].joint);
    searchJointCoObj(zoid, &zoid->l_arm2_coobj, sCLArm2JointName, zoid->feet[1].joint);
    searchJointCoObj(zoid, &zoid->r_arm1_coobj, sCRArm1JointName, zoid->feet[0].joint);
    searchJointCoObj(zoid, &zoid->r_arm2_coobj, sCRArm2JointName, zoid->feet[0].joint);
    searchJointCoObj(zoid, &zoid->l_leg1_coobj, sCLLeg1JointName, zoid->feet[3].joint);
    searchJointCoObj(zoid, &zoid->l_leg2_coobj, sCLLeg2JointName, zoid->feet[3].joint);
    searchJointCoObj(zoid, &zoid->r_leg1_coobj, sCRLeg1JointName, zoid->feet[2].joint);
    searchJointCoObj(zoid, &zoid->r_leg2_coobj, sCRLeg2JointName, zoid->feet[2].joint);
    searchJointCoObj(zoid, &zoid->l_foot_coobj, sCLFootJointName, zoid->feet[3].joint);
    searchJointCoObj(zoid, &zoid->r_foot_coobj, sCRFootJointName, zoid->feet[2].joint);
    zdCalcCoDmg(zoid);
    for (i = 0; i < 10; i++) {
        sprintf(attack, sAttackJointFormat, i);
        zoid->attack_objects[i].joint = searchJoint(zoid, attack);
        HiddenParts(zoid->attack_objects[i].joint, 1);
    }
    zoid->aobj = getAnimAobj(zoid->joint);
    zoid->field_19F4 = 1.0f + zoid->senter_translation_y;
    zoid->field_1BA4 = 2;
    zoid->health = Tea_zoiddat[type].health;
    zoid->radar_range = Tea_zoiddat[type].radar_range;
    zoid->previous_health = zoid->health;
    zoid->max_health = zoid->health;
    zoid->field_1B84 = 900;
    sprintf(path, (const char *)sZoidPrmPathFormat, name);
    zoid->control = (ZoidControlData *)sReadFileU(path, usb);
    if (zoid->control == NULL) {
        defaults = malloc(1804);
        ZeroMemory(defaults, 1804);
        defaults->ground_modes[0] = 1;
        defaults->ground_modes[1] = 1;
        defaults->ground_modes[2] = 2;
        defaults->ground_modes[3] = 2;
        defaults->ground_modes[4] = 1;
        defaults->ground_modes[5] = 1;
        defaults->ground_modes[6] = 1;
        defaults->ground_modes[7] = 1;
        defaults->ground_modes[8] = 1;
        defaults->ground_modes[9] = 1;
        defaults->ground_modes[10] = 1;
        defaults->ground_modes[11] = 1;
        defaults->ground_modes[14] = 1;
        defaults->ground_modes[16] = 1;
        defaults->ground_modes[18] = 1;
        defaults->ground_modes[20] = 1;
        defaults->max_senter_roll = 0;
        defaults->field_00A0 = 10;
        defaults->field_00A4 = 15;
        defaults->field_00E8 = 0.0f;
        defaults->field_00F0 = 25.0f;
        defaults->field_00EC = 7.0f;
        defaults->field_009C = 120;
        defaults->anim6_rate = 9;
        defaults->max_reverse_speed = 40;
        defaults->anim3_rate = 10;
        defaults->anim4_min_speed = 31;
        defaults->anim4_rate = 18;
        defaults->base_max_speed = 71;
        defaults->anim5_rate = 12;
        defaults->max_steer = 400;
        defaults->field_00F4 = 4;
        defaults->max_f_base_ry = 40;
        defaults->max_face_yaw = 20;
        defaults->sweep_joint_index = 3;
        defaults->step_launch_y = 40;
        defaults->attack_chain_length = 4;
        zoid->control = (ZoidControlData *)defaults;
    }
    param = zoid->control;
    if (param != NULL) {
        if (param->attack_chain_length == 0) {
            param->attack_chain_length = 4;
        }
        if (param->step_launch_y == 0) {
            param->step_launch_y = 40;
        }
        for (i = 0; i < 20; i++) {
            *(ParamTable *)angles = *(ParamTable *)sMountAngleDefaults;
            *(ParamTable *)distances = *(ParamTable *)sMountDistanceDefaults;
            *(ParamTable *)heights = *(ParamTable *)sMountHeightDefaults;
            entry = &param->camera_mounts[i];
            if (entry->height == 0) {
                entry->angle = angles[i];
                entry->height = heights[i];
                entry->distance = distances[i];
                if (i == 8 && zoid->weapon_slots[19].joint != NULL) {
                    entry->joint_slot = 19;
                } else {
                    for (j = 0; j < 27; j++) {
                        if (zoid->weapon_slots[j].joint != NULL) {
                            entry->joint_slot = j;
                            break;
                        }
                    }
                }
            }
            if (entry->angle == 0) {
                entry->angle = 180;
            }
            if (entry->height == 0) {
                entry->height = 30;
            }
            if (entry->distance == 0) {
                entry->distance = 10;
            }
        }
        if (param->dmg3_launch_scale == 0) {
            param->dmg3_launch_scale = 100;
        }
        if (param->max_down_frames == 0) {
            param->max_down_frames = 90;
        }
        if (param->acceleration == 0) {
            param->acceleration = 150;
        }
        if (param->deceleration == 0) {
            param->deceleration = 150;
        }
        if (param->max_unsupported_frames == 0) {
            param->max_unsupported_frames = 15;
        }
        if (param->detail_distance == 0) {
            param->detail_distance = 250;
        }
    }
    zoid->weapon_mount = -1;
    zoid->selected_weapon_mount = 0;
    ai = malloc(sizeof(ZoidAIState));
    if (ai != NULL) {
        ZeroMemory(ai, sizeof(ZoidAIState));
        zoid->ai = ai;
    }
    if (zoid->control->field_00F4 != 2) {
        zoid->field_19E8 = zoid->foot_count;
    } else {
        zoid->field_19E8 = 2;
    }
    for (i = 0; i < 30; i++) {
        zoid->weapon_slots[i].weapon = -1;
    }
    for (i = 0; i < 20; i++) {
        zoid->weapon_mounts[i].active = 0;
        for (j = 0; j < 4; j++) {
            zoid->weapon_mounts[i].entries[j].slot = -1;
            zoid->weapon_mounts[i].entries[j].active = 0;
        }
        zoid->field_1648[i].slot = -1;
        zoid->field_1648[i].active = 0;
    }
    zoid->additional_parts[0] = -1;
    zoid->additional_parts[1] = -1;
    zoid->additional_parts[2] = -1;
    look = zoid->buckle_joint;
    sMakeMatrix(zoid->joint);
    if (look != NULL) {
        zoid->buckle_height = look->matrix[1][3] - zoid->joint->matrix[1][3];
    }
    look = zoid->berut1_joint;
    if (look == NULL) look = zoid->jacket_joint;
    if (look == NULL) look = zoid->collar_joint;
    if (look == NULL) look = zoid->bust_base_joint;
    if (look == NULL) look = zoid->hip_base_joint;
    if (look == NULL) look = zoid->neck_base_joint;
    if (look == NULL) look = zoid->head_base_joint;
    if (look == NULL) look = zoid->buckle_joint;
    if (look == NULL) OSReport(sJobjLookError);
    if (look == NULL) look = zoid->joint;
    zoid->camera_joint = look;
    switch (zoid->control->sweep_joint_index) {
    case 0:
        look = zoid->navel_joint;
        break;
    case 1:
        look = NULL;
        break;
    case 2:
        look = zoid->collar_joint;
        break;
    case 3:
        look = zoid->jacket_joint;
        break;
    case 4:
        look = zoid->berut1_joint;
        break;
    case 5:
        look = zoid->buckle_joint;
        break;
    default:
        look = NULL;
        break;
    }
    zoid->sweep_joint = look;
    OSReport(sZoidOK);
    return 1;
}
