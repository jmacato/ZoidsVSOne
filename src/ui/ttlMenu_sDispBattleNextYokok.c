#include "model_archive.h"
#include "game_mode.h"

extern ModelArchive *menu1p;
extern s32 enemyChara[2];
extern s32 enemyZoid[2];
extern void OSReport(const char *format, ...);
extern s32 jobjAnim(HSD_JObj *joint);
extern void yokoku(s32 map);

void ttlMenu_sDispBattleNextYokok(void)
{
    if (menu1p == 0) {
        OSReport("menu1p non \n");
        return;
    }
    enemyChara[0] = -1;
    enemyChara[1] = -1;
    enemyZoid[0] = -1;
    enemyZoid[1] = -1;
    SetAnimArc2(menu1p, 25, 1);
    jobjAnim(menu1p->models[25]);
    yokoku(GameMode.map_variant + GameMode.map * 3);
}
