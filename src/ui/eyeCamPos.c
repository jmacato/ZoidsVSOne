#include "model_archive.h"
#include "ttl_main_data.h"

extern ModelArchive *menu_back1p;
extern void HSD_CObjSetEyePosition(struct HSD_CObj *cobj, Vec3 *position);

void eyeCamPos(void)
{
    eyeCam.x = 0.0f;
    eyeCam.y = 3.0f;
    eyeCam.z = 19.5f;
    HSD_CObjSetEyePosition(menu_back1p->camera, &eyeCam);
}
