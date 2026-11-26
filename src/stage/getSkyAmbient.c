#include "model_archive.h"
#include "mobj.h"
extern ModelArchive *Sky;
extern GXColor SkyAmbient;
extern HSD_MObj *searchMObj(HSD_JObj *);
void getSkyAmbient(void)
{
    HSD_MObj *material;
    if (Sky != 0) {
        HSD_JObj *joint = Sky->models[1];
        if (joint != 0) {
            material = searchMObj(joint);
            if (material != 0 && material->mat != 0)
                SkyAmbient = material->mat->ambient;
        }
    }
}
