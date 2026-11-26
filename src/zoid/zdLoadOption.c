#pragma readonly_strings on
#include "zoid.h"
#include "game_part_data.h"

extern void OSReport(const char *format, ...);
extern void zdLoadOption1(ZoidState *zoid, s32 part);
extern void zdLoadOption2(ZoidState *zoid, s32 part);
extern void zdLoadOption3(ZoidState *zoid);
extern void zdLoadOption4(ZoidState *zoid);
extern void zdLoadOption5(ZoidState *zoid);

void zdLoadOption(ZoidState *zoid, s32 part)
{
    u32 flags;
    s32 type;

    if (part != -1 && zoid != 0 && zoid->joint != 0) {
        flags = Tea_partsdat[part].flags;
        zoid->booster_on = 0;
        type = ZOID_OPTION_NONE;
        if (flags & PART_FLAG_CAMOUFLAGE)
            type = ZOID_OPTION_CAMOUFLAGE;
        if (flags & PART_FLAG_BOOSTER)
            type = ZOID_OPTION_BOOSTER;
        if (flags & PART_FLAG_SHIELD)
            type = ZOID_OPTION_SHIELD;
        if (flags & PART_FLAG_MINE)
            type = ZOID_OPTION_MINE;
        if (flags & PART_FLAG_SMOKE)
            type = ZOID_OPTION_SMOKE;
        zoid->option_type = type;
        if (zoid->option_type == ZOID_OPTION_SHIELD)
            zdLoadOption1(zoid, part);
        if (zoid->option_type == ZOID_OPTION_BOOSTER)
            zdLoadOption2(zoid, part);
        if (zoid->option_type == ZOID_OPTION_CAMOUFLAGE)
            zdLoadOption3(zoid);
        if (zoid->option_type == ZOID_OPTION_SMOKE)
            zdLoadOption4(zoid);
        if (zoid->option_type == ZOID_OPTION_MINE)
            zdLoadOption5(zoid);
        OSReport("option set!------ [no.%d] ---------\n", type);
    }
}
