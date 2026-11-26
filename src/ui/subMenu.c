#include "types.h"

extern s32 sbT;
extern void voiceSn2i(void);
extern void sub0(void), sub1(void), sub2(void), sub3(void);
extern void sub4(void), sub5(void), sub6(void), sub7(void);

void subMenu(void)
{
    if (sbT == -1) {
        voiceSn2i();
        return;
    }
    switch (sbT) {
    case 0:
        sub0();
        break;
    case 1:
        sub1();
        break;
    case 2:
        sub2();
        break;
    case 3:
        sub3();
        break;
    case 4:
        sub4();
        break;
    case 5:
        sub5();
        break;
    case 6:
        sub6();
        break;
    case 7:
        sub7();
        break;
    }
}
