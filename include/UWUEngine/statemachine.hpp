#pragma once

#include <UWUEngine/constants.h>
#include <UWUEngine/Helper.h>
#include <magic_enum.hpp>
#include <vector>

// NUM_ARGS(...) evaluates to the literal number of the passed-in arguments.
#define _NUM_ARGS2(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N
#define NUM_ARGS(...) EXPAND(_NUM_ARGS2(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))

#pragma region declarations
#define _VIRTUAL_DECLARATION1(Action, state) virtual void Action ## _ ##state();
#define _VIRTUAL_DECLARATION2(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION1(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION3(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION2(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION4(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION3(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION5(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION4(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION6(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION5(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION7(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION6(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION8(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION7(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION9(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION8(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION10(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION9(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION11(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION10(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION12(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION11(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION13(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION12(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION14(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION13(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION15(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION14(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION16(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION15(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION17(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION16(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION18(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION17(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION19(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION18(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION20(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION19(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION21(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION20(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION22(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION21(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION23(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION22(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION24(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION23(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION25(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION24(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION26(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION25(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION27(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION26(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION28(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION27(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION29(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION28(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION30(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION29(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION31(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION30(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION32(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION31(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION33(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION32(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION34(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION33(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION35(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION34(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION36(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION35(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION37(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION36(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION38(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION37(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION39(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION38(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION40(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION39(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION41(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION40(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION42(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION41(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION43(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION42(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION44(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION43(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION45(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION44(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION46(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION45(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION47(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION46(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION48(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION47(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION49(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION48(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION50(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION49(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION51(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION50(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION52(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION51(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION53(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION52(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION54(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION53(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION55(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION54(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION56(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION55(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION57(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION56(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION58(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION57(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION59(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION58(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION60(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION59(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION61(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION60(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION62(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION61(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION63(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION62(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#define _VIRTUAL_DECLARATION64(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION63(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION1(Action, state)
#pragma endregion

#pragma region declarations_dt
#define _VIRTUAL_DECLARATION_DT1(Action, state) virtual void Action ## _ ##state(float dt);
#define _VIRTUAL_DECLARATION_DT2(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT1(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT3(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT2(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT4(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT3(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT5(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT4(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT6(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT5(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT7(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT6(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT8(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT7(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT9(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT8(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT10(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT9(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT11(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT10(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT12(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT11(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT13(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT12(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT14(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT13(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT15(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT14(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT16(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT15(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT17(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT16(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT18(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT17(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT19(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT18(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT20(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT19(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT21(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT20(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT22(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT21(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT23(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT22(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT24(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT23(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT25(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT24(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT26(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT25(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT27(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT26(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT28(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT27(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT29(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT28(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT30(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT29(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT31(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT30(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT32(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT31(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT33(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT32(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT34(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT33(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT35(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT34(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT36(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT35(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT37(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT36(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT38(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT37(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT39(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT38(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT40(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT39(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT41(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT40(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT42(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT41(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT43(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT42(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT44(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT43(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT45(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT44(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT46(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT45(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT47(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT46(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT48(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT47(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT49(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT48(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT50(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT49(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT51(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT50(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT52(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT51(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT53(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT52(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT54(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT53(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT55(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT54(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT56(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT55(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT57(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT56(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT58(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT57(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT59(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT58(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT60(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT59(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT61(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT60(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT62(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT61(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT63(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT62(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)
#define _VIRTUAL_DECLARATION_DT64(Action, state, ...) EXPAND(_VIRTUAL_DECLARATION_DT63(Action, __VA_ARGS__)) _VIRTUAL_DECLARATION_DT1(Action, state)


#pragma endregion

#pragma region cases
#define _VIRTUAL_CASE1(Action, state) case (state) : Action ## _ ##state(); break;
#define _VIRTUAL_CASE2(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE1(Action, __VA_ARGS__))
#define _VIRTUAL_CASE3(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE2(Action, __VA_ARGS__))
#define _VIRTUAL_CASE4(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE3(Action, __VA_ARGS__))
#define _VIRTUAL_CASE5(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE4(Action, __VA_ARGS__))
#define _VIRTUAL_CASE6(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE5(Action, __VA_ARGS__))
#define _VIRTUAL_CASE7(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE6(Action, __VA_ARGS__))
#define _VIRTUAL_CASE8(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE7(Action, __VA_ARGS__))
#define _VIRTUAL_CASE9(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE8(Action, __VA_ARGS__))
#define _VIRTUAL_CASE10(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE9(Action, __VA_ARGS__))
#define _VIRTUAL_CASE11(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE10(Action, __VA_ARGS__))
#define _VIRTUAL_CASE12(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE11(Action, __VA_ARGS__))
#define _VIRTUAL_CASE13(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE12(Action, __VA_ARGS__))
#define _VIRTUAL_CASE14(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE13(Action, __VA_ARGS__))
#define _VIRTUAL_CASE15(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE14(Action, __VA_ARGS__))
#define _VIRTUAL_CASE16(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE15(Action, __VA_ARGS__))
#define _VIRTUAL_CASE17(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE16(Action, __VA_ARGS__))
#define _VIRTUAL_CASE18(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE17(Action, __VA_ARGS__))
#define _VIRTUAL_CASE19(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE18(Action, __VA_ARGS__))
#define _VIRTUAL_CASE20(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE19(Action, __VA_ARGS__))
#define _VIRTUAL_CASE21(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE20(Action, __VA_ARGS__))
#define _VIRTUAL_CASE22(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE21(Action, __VA_ARGS__))
#define _VIRTUAL_CASE23(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE22(Action, __VA_ARGS__))
#define _VIRTUAL_CASE24(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE23(Action, __VA_ARGS__))
#define _VIRTUAL_CASE25(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE24(Action, __VA_ARGS__))
#define _VIRTUAL_CASE26(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE25(Action, __VA_ARGS__))
#define _VIRTUAL_CASE27(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE26(Action, __VA_ARGS__))
#define _VIRTUAL_CASE28(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE27(Action, __VA_ARGS__))
#define _VIRTUAL_CASE29(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE28(Action, __VA_ARGS__))
#define _VIRTUAL_CASE30(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE29(Action, __VA_ARGS__))
#define _VIRTUAL_CASE31(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE30(Action, __VA_ARGS__))
#define _VIRTUAL_CASE32(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE31(Action, __VA_ARGS__))
#define _VIRTUAL_CASE33(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE32(Action, __VA_ARGS__))
#define _VIRTUAL_CASE34(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE33(Action, __VA_ARGS__))
#define _VIRTUAL_CASE35(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE34(Action, __VA_ARGS__))
#define _VIRTUAL_CASE36(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE35(Action, __VA_ARGS__))
#define _VIRTUAL_CASE37(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE36(Action, __VA_ARGS__))
#define _VIRTUAL_CASE38(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE37(Action, __VA_ARGS__))
#define _VIRTUAL_CASE39(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE38(Action, __VA_ARGS__))
#define _VIRTUAL_CASE40(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE39(Action, __VA_ARGS__))
#define _VIRTUAL_CASE41(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE40(Action, __VA_ARGS__))
#define _VIRTUAL_CASE42(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE41(Action, __VA_ARGS__))
#define _VIRTUAL_CASE43(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE42(Action, __VA_ARGS__))
#define _VIRTUAL_CASE44(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE43(Action, __VA_ARGS__))
#define _VIRTUAL_CASE45(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE44(Action, __VA_ARGS__))
#define _VIRTUAL_CASE46(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE45(Action, __VA_ARGS__))
#define _VIRTUAL_CASE47(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE46(Action, __VA_ARGS__))
#define _VIRTUAL_CASE48(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE47(Action, __VA_ARGS__))
#define _VIRTUAL_CASE49(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE48(Action, __VA_ARGS__))
#define _VIRTUAL_CASE50(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE49(Action, __VA_ARGS__))
#define _VIRTUAL_CASE51(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE50(Action, __VA_ARGS__))
#define _VIRTUAL_CASE52(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE51(Action, __VA_ARGS__))
#define _VIRTUAL_CASE53(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE52(Action, __VA_ARGS__))
#define _VIRTUAL_CASE54(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE53(Action, __VA_ARGS__))
#define _VIRTUAL_CASE55(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE54(Action, __VA_ARGS__))
#define _VIRTUAL_CASE56(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE55(Action, __VA_ARGS__))
#define _VIRTUAL_CASE57(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE56(Action, __VA_ARGS__))
#define _VIRTUAL_CASE58(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE57(Action, __VA_ARGS__))
#define _VIRTUAL_CASE59(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE58(Action, __VA_ARGS__))
#define _VIRTUAL_CASE60(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE59(Action, __VA_ARGS__))
#define _VIRTUAL_CASE61(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE60(Action, __VA_ARGS__))
#define _VIRTUAL_CASE62(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE61(Action, __VA_ARGS__))
#define _VIRTUAL_CASE63(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE62(Action, __VA_ARGS__))
#define _VIRTUAL_CASE64(Action, state, ...) _VIRTUAL_CASE1(Action, state) EXPAND(_VIRTUAL_CASE63(Action, __VA_ARGS__))

#pragma endregion

#pragma region cases_dt
#define _VIRTUAL_CASE_DT1(Action, state) case (state) : Action ## _ ##state(dt); break;
#define _VIRTUAL_CASE_DT2(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT1(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT3(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT2(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT4(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT3(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT5(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT4(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT6(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT5(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT7(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT6(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT8(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT7(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT9(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT8(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT10(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT9(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT11(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT10(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT12(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT11(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT13(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT12(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT14(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT13(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT15(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT14(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT16(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT15(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT17(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT16(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT18(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT17(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT19(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT18(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT20(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT19(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT21(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT20(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT22(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT21(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT23(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT22(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT24(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT23(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT25(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT24(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT26(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT25(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT27(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT26(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT28(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT27(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT29(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT28(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT30(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT29(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT31(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT30(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT32(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT31(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT33(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT32(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT34(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT33(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT35(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT34(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT36(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT35(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT37(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT36(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT38(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT37(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT39(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT38(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT40(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT39(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT41(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT40(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT42(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT41(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT43(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT42(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT44(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT43(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT45(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT44(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT46(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT45(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT47(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT46(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT48(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT47(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT49(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT48(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT50(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT49(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT51(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT50(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT52(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT51(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT53(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT52(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT54(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT53(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT55(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT54(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT56(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT55(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT57(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT56(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT58(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT57(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT59(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT58(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT60(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT59(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT61(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT60(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT62(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT61(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT63(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT62(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT64(Action, state, ...) _VIRTUAL_CASE_DT1(Action, state) EXPAND(_VIRTUAL_CASE_DT63(Action, __VA_ARGS__))

#pragma endregion

#define _VIRTUAL_DECLARATION_N3(N, Action, ...) EXPAND(_VIRTUAL_DECLARATION ## N(Action, __VA_ARGS__))
#define _VIRTUAL_DECLARATION_N2(N, Action, ...) EXPAND(_VIRTUAL_DECLARATION_N3(N, Action, __VA_ARGS__))
#define _VIRTUAL_DECLARATION_N(Action, ...) EXPAND(_VIRTUAL_DECLARATION_N2(NUM_ARGS(__VA_ARGS__), Action, __VA_ARGS__))

#define _VIRTUAL_DECLARATION_DT_N3(N, Action, ...) EXPAND(_VIRTUAL_DECLARATION_DT ## N(Action, __VA_ARGS__))
#define _VIRTUAL_DECLARATION_DT_N2(N, Action, ...) EXPAND(_VIRTUAL_DECLARATION_DT_N3(N, Action, __VA_ARGS__))
#define _VIRTUAL_DECLARATION_DT_N(Action, ...) EXPAND(_VIRTUAL_DECLARATION_DT_N2(NUM_ARGS(__VA_ARGS__), Action, __VA_ARGS__))

#define _VIRTUAL_CASE_N3(N, Action, ...) EXPAND(_VIRTUAL_CASE ## N(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_N2(N, Action, ...) EXPAND(_VIRTUAL_CASE_N3(N, Action, __VA_ARGS__))
#define _VIRTUAL_CASE_N(Action, ...) EXPAND(_VIRTUAL_CASE_N2(NUM_ARGS(__VA_ARGS__), Action, __VA_ARGS__))

#define _VIRTUAL_CASE_DT_N3(N, Action, ...) EXPAND(_VIRTUAL_CASE_DT ## N(Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT_N2(N, Action, ...) EXPAND(_VIRTUAL_CASE_DT_N3(N, Action, __VA_ARGS__))
#define _VIRTUAL_CASE_DT_N(Action, ...) EXPAND(_VIRTUAL_CASE_DT_N2(NUM_ARGS(__VA_ARGS__), Action, __VA_ARGS__))

//#define _AUTO_REGISTER(name, b_register) EXPAND(_AUTO_REGISTER_ ## b_register(name))
//#define _AUTO_REGISTER_true(name) int RegisterStateHelper<name ## StateMachine>::RegisterStateHelper_ID = StateMachineUpdater::AddMachine<name ## StateMachine>()
//#define _AUTO_REGISTER_false(name)

class StateMachineBase
{
public:
  void RestartState()
  {
    next_state = StateMachineConsts::_STATE_RESTART;
  }
  void UpdateState(float dt)
  {
    if (next_state != StateMachineConsts::_STATE_INVALID && current_state != next_state)
    {
      Exit();
      if (next_state == StateMachineConsts::_STATE_RESTART)
      {
        next_state = current_state;
      }
      else
      {
        Unload();
        previous_state = current_state;
        current_state = next_state;
        Load();
      }
      Enter();
      
    }
    Update(dt);
  }
  virtual void Enter() = 0;
  virtual void Load() = 0;
  virtual void Update(float dt) = 0;
  virtual void Unload() = 0;
  virtual void Exit() = 0;
  StateMachineBase() = default;
  virtual ~StateMachineBase() = default;
protected: 
  int previous_state = StateMachineConsts::_STATE_INVALID;
  int current_state = StateMachineConsts::_STATE_INITIAL;
  int next_state = StateMachineConsts::_STATE_INVALID;

};

class StateMachineUpdater
{
private:
public:
	static void StartUp();
	static void Update();
	static std::vector<StateMachineBase*>& GetMachines()
	{
		static std::vector<StateMachineBase*> machines;
		return machines;
	}
	
	template<typename T>
	static int AddMachine() noexcept
	{
		GetMachines().push_back(static_cast<StateMachineBase*>(new T()));
		return 0;
	}
};

template <typename T>
struct RegisterStateHelper
{
	RegisterStateHelper() {};
	static int RegisterStateHelper_ID;
};

template<typename T> \
int RegisterStateHelper<T>::RegisterStateHelper_ID = StateMachineUpdater::AddMachine<T>();

#define StateMachine(name, auto_register, ...) \
class name ## StateMachine : public StateMachineBase, public RegisterStateHelper<name ## StateMachine> {  \
public: \
using StateMachineBase::StateMachineBase; \
enum _ ## name ## StateMachine ## state { Restart = StateMachineConsts::_STATE_RESTART, Invalid = StateMachineConsts::_STATE_INVALID, __VA_ARGS__, Num,}; \
std::string GetCurrentStateName() { return magic_enum::enum_name<_ ## name ## StateMachine ## state>(GetCurrentState()).data();} \
_ ## name ## StateMachine ## state GetCurrentState() { return magic_enum::enum_cast<_ ## name ## StateMachine ## state>(current_state).value(); } \
_ ## name ## StateMachine ## state GetNextState() { return magic_enum::enum_cast<_ ## name ## StateMachine ## state>(next_state).value(); } \
void SetNextState(_ ## name ## StateMachine ## state s) { next_state = magic_enum::enum_integer<_ ## name ## StateMachine ## state>(s); } \
_VIRTUAL_DECLARATION_N(Enter, __VA_ARGS__) \
_VIRTUAL_DECLARATION_N(Load, __VA_ARGS__) \
_VIRTUAL_DECLARATION_DT_N(Update, __VA_ARGS__) \
_VIRTUAL_DECLARATION_N(Unload, __VA_ARGS__) \
_VIRTUAL_DECLARATION_N(Exit, __VA_ARGS__) \
void Enter() { switch (current_state) { _VIRTUAL_CASE_N(Enter, __VA_ARGS__) } } \
void Load() { switch (current_state) { _VIRTUAL_CASE_N(Load, __VA_ARGS__) } } \
void Update(float dt) { switch (current_state) { _VIRTUAL_CASE_DT_N(Update, __VA_ARGS__) } } \
void Unload() { switch (current_state) { _VIRTUAL_CASE_N(Unload, __VA_ARGS__) } } \
void Exit() { switch (current_state) { _VIRTUAL_CASE_N(Exit, __VA_ARGS__) } } \
}; \
//_AUTO_REGISTER(name, auto_register)

#define RegisterStateMachine(class_name) int RegisterStateHelper<class_name>::RegisterStateHelper_ID = StateMachineUpdater::AddMachine<class_name>()