#include "model_archive.h"
#include "game_pad.h"
#include "map_info.h"

extern PadState *sPad1;
extern s32 anmN;
extern MapInfo *rdMapInfo(s32 mode, s32 map);
extern s32 menu_sDispMissionHokyu(MapInfo *info, ModelArchive *archive, s32 done);
extern void sPadAll(void);
extern void SeRet(void);
extern void ttl_HaveAddZoid(s16 record, s16 zoid);
extern void ttl_HaveAddParts(s16 record, s16 part);

void hokyuu(s32 map)
{
    MapInfo *info = rdMapInfo(1, map);
    ModelArchive *archive;
    s32 done;
    s32 finished;
    s32 i;
    s32 value;

    if (info == 0)
        return;
    archive = LoadArc2("menu/battle_menu/detail.dat");
    if (archive != 0) {
        SetAnimArc2(archive, 5, 1);
        anmN = 1;
    }
    done = 0;
    do {
        finished = menu_sDispMissionHokyu(info, archive, done);
        sPadAll();
        if (sPad1->pressed_b != 0)
            done = 1;
        if (sPad1->pressed_a != 0)
            done = 1;
    } while (finished == 0);
    SeRet();
    if (archive != 0)
        PurgeArc2(archive);
    for (i = 0; i < 2; i++) {
        value = info->new_zoids[i];
        if (value != -1) {
            ttl_HaveAddZoid(0, value);
            ttl_HaveAddZoid(4, value);
        }
    }
    for (i = 0; i < 8; i++) {
        value = info->new_parts[i];
        if (value > 0) {
            ttl_HaveAddParts(0, value);
            ttl_HaveAddParts(4, value);
        }
    }
}
