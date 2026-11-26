#include "game_mode.h"
#include "game_save.h"

extern void ttlMenuPurgeBack(void), ttlMenuPurgeParts(void);
extern void TeaBgm(s16 track);
extern void ttlMenuLoadParts(s32 mode), ttlMenuLoadBack(s32 mode);
extern void ttlMenuLoadZoidBanner(void), ttlMenuLoadPersonBanner(void);
extern void ttlMenuLoadYesNo(void), ttlMenuLoadZoid(void);

s32 menufncZoidBattle01Human(void)
{
    ttlMenuPurgeBack();
    ttlMenuPurgeParts();
    TeaBgm(7);
    IveSave[0].selected_person = 0;
    IveSave[0].partner_person = 1;
    ttlMenuLoadParts(5);
    ttlMenuLoadBack(4);
    ttlMenuLoadZoidBanner();
    ttlMenuLoadPersonBanner();
    ttlMenuLoadYesNo();
    return 0xDC;
}

s32 menufncZoidBattle02(void)
{
    ttlMenuPurgeBack();
    ttlMenuPurgeParts();
    if (GameMode.country == 0)
        TeaBgm(7);
    else
        TeaBgm(GameMode.country + 22);
    ttlMenuLoadParts(4);
    ttlMenuLoadBack(6);
    ttlMenuLoadZoidBanner();
    ttlMenuLoadPersonBanner();
    ttlMenuLoadYesNo();
    ttlMenuLoadZoid();
    return 0xCC;
}

s32 menufncZoidBattle02Hokyu(void)
{
    ttlMenuPurgeBack();
    ttlMenuPurgeParts();
    GameMode.country = IveSave[0].country;
    GameMode.game_type = IveSave[0].game_type;
    TeaBgm(GameMode.country + 22);
    ttlMenuLoadParts(4);
    ttlMenuLoadBack(6);
    ttlMenuLoadZoidBanner();
    ttlMenuLoadPersonBanner();
    ttlMenuLoadYesNo();
    return 0xCC;
}
