#include "joint.h"
extern void setAnimRateXor(HSD_JObj *, HSD_JObj *, f32);
void setAnimStopXor(HSD_JObj *joint, HSD_JObj *excluded)
{
    setAnimRateXor(joint, excluded, 0.0f);
}
