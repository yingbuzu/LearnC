
#include <stdio.h>


#define _SUB_0
#define _SUB_1                  0
#define _SUB_2                  1
#define _SUB_3                  2
#define _SUB_4                  3
#define _SUB_5                  4
#define _SUB_6                  5
#define _SUB_7                  6
#define _SUB_8                  7
#define _SUB_9                  8

#define _SUB(x)                 _SUB_##x

#define __GEN_TMUL_0(y)
#define __GEN_TMUL_1(y)         __GEN_TMUL_0(y) "1x" y "=%d" " "
#define __GEN_TMUL_2(y)         __GEN_TMUL_1(y) "2x" y "=%-2d" " "
#define __GEN_TMUL_3(y)         __GEN_TMUL_2(y) "3x" y "=%-2d" " "
#define __GEN_TMUL_4(y)         __GEN_TMUL_3(y) "4x" y "=%-2d" " "
#define __GEN_TMUL_5(y)         __GEN_TMUL_4(y) "5x" y "=%-2d" " "
#define __GEN_TMUL_6(y)         __GEN_TMUL_5(y) "6x" y "=%-2d" " "
#define __GEN_TMUL_7(y)         __GEN_TMUL_6(y) "7x" y "=%-2d" " "
#define __GEN_TMUL_8(y)         __GEN_TMUL_7(y) "8x" y "=%-2d" " "
#define __GEN_TMUL_9(y)         __GEN_TMUL_8(y) "9x" y "=%-2d" " "

#define __GEN_TMULX(x)          #x ": " __GEN_TMUL_##x(#x) "\n"
#define _GEN_TMULX(x)           __GEN_TMULX(x)

#define __GEN_VMUL_0(y)
#define __GEN_VMUL_1(y)         __GEN_VMUL_0(y) ,y * 1
#define __GEN_VMUL_2(y)         __GEN_VMUL_1(y) ,y * 2
#define __GEN_VMUL_3(y)         __GEN_VMUL_2(y) ,y * 3
#define __GEN_VMUL_4(y)         __GEN_VMUL_3(y) ,y * 4
#define __GEN_VMUL_5(y)         __GEN_VMUL_4(y) ,y * 5
#define __GEN_VMUL_6(y)         __GEN_VMUL_5(y) ,y * 6
#define __GEN_VMUL_7(y)         __GEN_VMUL_6(y) ,y * 7
#define __GEN_VMUL_8(y)         __GEN_VMUL_7(y) ,y * 8
#define __GEN_VMUL_9(y)         __GEN_VMUL_8(y) ,y * 9

#define __GEN_VMULX(x)          __GEN_VMUL_##x(x)
#define _GEN_VMULX(x)           __GEN_VMULX(x)

#define __GEN_LINE_T0(y)
#define __GEN_LINE_T1(y)        __GEN_LINE_T0(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T2(y)        __GEN_LINE_T1(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T3(y)        __GEN_LINE_T2(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T4(y)        __GEN_LINE_T3(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T5(y)        __GEN_LINE_T4(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T6(y)        __GEN_LINE_T5(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T7(y)        __GEN_LINE_T6(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T8(y)        __GEN_LINE_T7(_SUB(y)) _GEN_TMULX(y)
#define __GEN_LINE_T9(y)        __GEN_LINE_T8(_SUB(y)) _GEN_TMULX(y)

#define __GEN_LINE_V0(y)
#define __GEN_LINE_V1(y)        __GEN_LINE_V0(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V2(y)        __GEN_LINE_V1(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V3(y)        __GEN_LINE_V2(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V4(y)        __GEN_LINE_V3(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V5(y)        __GEN_LINE_V4(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V6(y)        __GEN_LINE_V5(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V7(y)        __GEN_LINE_V6(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V8(y)        __GEN_LINE_V7(_SUB(y)) _GEN_VMULX(y)
#define __GEN_LINE_V9(y)        __GEN_LINE_V8(_SUB(y)) _GEN_VMULX(y)




#define GENT_T(x)               __GEN_LINE_T##x(x) __GEN_LINE_V##x(x)

int main()
{
    // 猜猜这里传递了几个参数
    printf(GENT_T(9));

    return 0;
}
