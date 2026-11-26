#include "types.h"

extern s32 menudispyesnoflag;
extern char menudispyesnostr1[180];
extern char menudispyesnostr2[180];

void clrYesNoMsg(void)
{
    menudispyesnoflag = 0;
    menudispyesnostr1[0] = 0;
    menudispyesnostr2[0] = 0;
}
