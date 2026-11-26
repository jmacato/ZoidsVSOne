#include "types.h"

extern s32 dspPartnerMsg;
extern s32 dspPartnerMsgTm;

void PartnerFace(s32 message, s32 duration)
{
    dspPartnerMsg = message;
    dspPartnerMsgTm = duration;
}
