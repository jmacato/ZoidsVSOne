#include "types.h"
#include "model_archive.h"

extern void *menu_saveloadp;
extern void *menu_saveloadbgp;
extern void ttlMenuPurgeSaveLoad(void);

void ttlMenuLoadSaveLoad(void)
{
    ttlMenuPurgeSaveLoad();
    menu_saveloadp = LoadArc2("menu/saveload/saveload.dat");
    menu_saveloadbgp = LoadArc2("menu/saveload/bgtitle.dat");
}
