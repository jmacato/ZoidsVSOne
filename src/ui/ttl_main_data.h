#ifndef ZOIDS_TTL_MAIN_DATA_H
#define ZOIDS_TTL_MAIN_DATA_H

#include "types.h"
#include "lobj.h"
#include "wobj.h"

typedef struct SampleVoice {
    u8 character;
    u8 reserved_1;
    s16 voice;
} SampleVoice;

extern f32 shininess;

#pragma force_active on
u32 TXT_Menu[1176] = {
    0x00000000, 0x0000002E, 0x0000005C, 0x0000008A, 0x000000B8, 0x00000140,
    0x000001C8, 0x000001F6, 0x00000224, 0x00000252, 0x00000280, 0x000002AE,
    0x000002D8, 0x00000360, 0x000003E8, 0x00000412, 0x0000043C, 0x00000466,
    0x00000490, 0x000004BA, 0x000004E4, 0x0000050E, 0x00000538, 0x00000562,
    0x0000058C, 0x000005B6, 0x000005E0, 0x0000060A, 0x00000634, 0x0000065E,
    0x00000688, 0x000006B2, 0x000006DC, 0x00000706, 0x00000730, 0x0000075A,
    0x00000784, 0x000007AE, 0x000007C6, 0x000007F0, 0x0000081A, 0x00000844,
    0x000008CC, 0x000008F6, 0x00000920, 0x0000094A, 0x00000974, 0x0000099E,
    0x000009C8, 0x000009F2, 0x00000A70, 0x00000AEE, 0x00000B6C, 0x00000BEA,
    0x00000C68, 0x00000CE6, 0x00000D64, 0x00000DE2, 0x00000E60, 0x00000EDE,
    0x00000F5C, 0x00000FDA, 0x00001058, 0x000010D6, 0x00001154, 0x000011D2,
    0x00001250, 0x000012CE, 0x0000134C, 0x000013CA, 0x00001448, 0x000014C6,
    0x00001544, 0x000015CC, 0x00001654, 0x000016DC, 0x00001764, 0x000017EC,
    0x00001874, 0x000018FC, 0x00001984, 0x00001A0C, 0x00001A36, 0x00001A60,
    0x00001AE8, 0x00001B70, 0x00001BF8, 0x00001C80, 0x00001CFE, 0x00001D7C,
    0x00001DFA, 0x00001E78, 0x00001EF6, 0x00001F74, 0x00001FF2, 0x00002070,
    0x0000209A, 0x000020C4, 0x000020EE, 0x0000216C, 0x00002172, 0x000021FA,
    0x00002260, 0x000022C6, 0x0000232C, 0x00002392, 0x000023F8, 0x0000245E,
    0x000024C4, 0x0000252A, 0x00002590, 0x000025F6, 0x0000265C, 0x000026C2,
    0x00002728, 0x0000278E, 0x000027F4, 0x0000285A, 0x000028C0, 0x00002926,
    0x0000298C, 0x000029F2, 0x00002A58, 0x00002ABE, 0x00002B24, 0x00002B8A,
    0x00002BF0, 0x00002C56, 0x00002CBC, 0x00002D22, 0x00002D88, 0x00002DEE,
    0x00002E54, 0x00002EBA, 0x00002F20, 0x00002F86, 0x00002FEC, 0x00003052,
    0x000030B8, 0x0000311E, 0x00003184, 0x000031EA, 0x00003250, 0x000032B6,
    0x0000331C, 0x00003382, 0x000033E8, 0x0000344E, 0x000034B4, 0x0000351A,
    0x00003580, 0x000035E6, 0x0000364C, 0x000036B2, 0x00003718, 0x0000377E,
    0x000037E4, 0x0000384A, 0x000038B0, 0x00003916, 0x0000397C, 0x000039E2,
    0x00003A48, 0x00003AAE, 0x00003B14, 0x00003B7A, 0x00003BE0, 0x00003C46,
    0x00003CAC, 0x00003D12, 0x00003D78, 0x00003DDE, 0x00003E44, 0x00003EAA,
    0x00003F10, 0x00003F76, 0x00003FDC, 0x00004042, 0x000040A8, 0x0000410E,
    0x00004174, 0x000041DA, 0x00004240, 0x000042A6, 0x0000430C, 0x00004372,
    0x000043D8, 0x0000443E, 0x000044A4, 0x0000450A, 0x00004570, 0x000045D6,
    0x0000463C, 0x000046A2, 0x00004708, 0x0000476E, 0x000047D4, 0x0000483A,
    0x000048A0, 0x00004906, 0x0000496C, 0x000049D2, 0x00004A38, 0x00004A9E,
    0x00004B04, 0x00004B6A, 0x00004BD0, 0x00004C36, 0x00004C9C, 0x00004D02,
    0x00004D68, 0x00004DCE, 0x00004E34, 0x00004E9A, 0x00004F00, 0x00004F66,
    0x00004FCC, 0x00005032, 0x00005098, 0x000050FE, 0x00005164, 0x000051CA,
    0x00005230, 0x00005296, 0x000052FC, 0x00005362, 0x000053C8, 0x0000542E,
    0x00005494, 0x000054FA, 0x00005560, 0x000055C6, 0x0000562C, 0x00005692,
    0x000056F8, 0x0000575E, 0x000057C4, 0x0000582A, 0x00005890, 0x000058F6,
    0x0000595C, 0x000059C2, 0x00005A28, 0x00005A8E, 0x00005AF4, 0x00005B5A,
    0x00005BC0, 0x00005C26, 0x00005C8C, 0x00005CF2, 0x00005D58, 0x00005DBE,
    0x00005E24, 0x00005E8A, 0x00005EF0, 0x00005F56, 0x00005FBC, 0x00006022,
    0x00006088, 0x000060EE, 0x00006154, 0x000061BA, 0x00006220, 0x00006286,
    0x000062EC, 0x00006352, 0x000063B8, 0x0000641E, 0x00006484, 0x000064EA,
    0x00006550, 0x000065B6, 0x0000661C, 0x00006682, 0x000066E8, 0x0000674E,
    0x000067B4, 0x0000681A, 0x00006880, 0x000068E6, 0x0000694C, 0x000069B2,
    0x00006A18, 0x00006A7E, 0x00006AE4, 0x00006B4A, 0x00006BB0, 0x00006C16,
    0x00006C7C, 0x00006CE2, 0x00006D48, 0x00006DAE, 0x00006E14, 0x00006E7A,
    0x00006EE0, 0x00006F46, 0x00006FAC, 0x00007012, 0x00007078, 0x000070DE,
    0x00007144, 0x000071AA, 0x00007210, 0x00007276, 0x000072DC, 0x00007342,
    0x000073A8, 0x0000740E, 0x00007474, 0x000074DA, 0x00007540, 0x000075A6,
    0x0000760C, 0x00007672, 0x000076D8, 0x0000773E, 0x000077A4, 0x0000780A,
    0x00007870, 0x000078D6, 0x0000793C, 0x000079A2, 0x00007A08, 0x00007A6E,
    0x00007AD4, 0x00007B3A, 0x00007BA0, 0x00007C06, 0x00007C6C, 0x00007CD2,
    0x00007D38, 0x00007D9E, 0x00007E04, 0x00007E6A, 0x00007ED0, 0x00007F36,
    0x00007F9C, 0x00008002, 0x00008068, 0x000080CE, 0x00008134, 0x0000819A,
    0x00008200, 0x00008266, 0x000082CC, 0x00008332, 0x00008398, 0x000083FE,
    0x00008464, 0x000084CA, 0x00008530, 0x00008596, 0x000085FC, 0x00008662,
    0x000086C8, 0x0000872E, 0x00008794, 0x000087FA, 0x00008860, 0x000088C6,
    0x0000892C, 0x00008992, 0x000089F8, 0x00008A5E, 0x00008AC4, 0x00008B2A,
    0x00008B90, 0x00008BF6, 0x00008C5C, 0x00008CC2, 0x00008D28, 0x00008D8E,
    0x00008DF4, 0x00008E5A, 0x00008EC0, 0x00008F26, 0x00008F8C, 0x00008FF2,
    0x00009058, 0x000090BE, 0x00009124, 0x0000918A, 0x000091F0, 0x00009256,
    0x000092BC, 0x00009322, 0x00009388, 0x000093EE, 0x00009454, 0x000094BA,
    0x00009520, 0x00009586, 0x000095EC, 0x00009652, 0x000096B8, 0x0000971E,
    0x00009784, 0x000097EA, 0x00009850, 0x000098B6, 0x0000991C, 0x00009982,
    0x000099E8, 0x00009A4E, 0x00009AB4, 0x00009B1A, 0x00009B80, 0x00009BE6,
    0x00009C4C, 0x00009CB2, 0x00009D18, 0x00009D7E, 0x00009DE4, 0x00009E4A,
    0x00009EB0, 0x00009F16, 0x00009F7C, 0x00009FE2, 0x0000A048, 0x0000A0AE,
    0x0000A114, 0x0000A17A, 0x0000A1E0, 0x0000A246, 0x0000A2AC, 0x0000A312,
    0x0000A378, 0x0000A3DE, 0x0000A444, 0x0000A4AA, 0x0000A510, 0x0000A576,
    0x0000A5DC, 0x0000A642, 0x0000A6A8, 0x0000A70E, 0x0000A774, 0x0000A7DA,
    0x0000A840, 0x0000A8A6, 0x0000A90C, 0x0000A972, 0x0000A9D8, 0x0000AA3E,
    0x0000AAA4, 0x0000AB0A, 0x0000AB70, 0x0000ABD6, 0x0000AC3C, 0x0000ACA2,
    0x0000AD08, 0x0000AD6E, 0x0000ADD4, 0x0000AE3A, 0x0000AEA0, 0x0000AF06,
    0x0000AF6C, 0x0000AFD2, 0x0000B038, 0x0000B09E, 0x0000B104, 0x0000B16A,
    0x0000B1D0, 0x0000B236, 0x0000B29C, 0x0000B302, 0x0000B368, 0x0000B3CE,
    0x0000B434, 0x0000B49A, 0x0000B500, 0x0000B566, 0x0000B5CC, 0x0000B632,
    0x0000B698, 0x0000B6FE, 0x0000B764, 0x0000B7CA, 0x0000B830, 0x0000B896,
    0x0000B8FC, 0x0000B962, 0x0000B9C8, 0x0000BA2E, 0x0000BA94, 0x0000BAFA,
    0x0000BB60, 0x0000BBC6, 0x0000BC2C, 0x0000BC92, 0x0000BCF8, 0x0000BD5E,
    0x0000BDC4, 0x0000BE2A, 0x0000BE90, 0x0000BEF6, 0x0000BF5C, 0x0000BFC2,
    0x0000C028, 0x0000C08E, 0x0000C0F4, 0x0000C15A, 0x0000C1C0, 0x0000C226,
    0x0000C28C, 0x0000C2F2, 0x0000C358, 0x0000C3BE, 0x0000C424, 0x0000C48A,
    0x0000C4F0, 0x0000C556, 0x0000C5BC, 0x0000C622, 0x0000C688, 0x0000C6EE,
    0x0000C754, 0x0000C7BA, 0x0000C820, 0x0000C886, 0x0000C8EC, 0x0000C952,
    0x0000C9B8, 0x0000CA1E, 0x0000CA84, 0x0000CAEA, 0x0000CB50, 0x0000CBB6,
    0x0000CC1C, 0x0000CC82, 0x0000CCE8, 0x0000CD4E, 0x0000CDB4, 0x0000CE1A,
    0x0000CE80, 0x0000CEE6, 0x0000CF4C, 0x0000CFB2, 0x0000D018, 0x0000D07E,
    0x0000D0E4, 0x0000D14A, 0x0000D1B0, 0x0000D216, 0x0000D2BE, 0x0000D366,
    0x0000D40E, 0x0000D4B6, 0x0000D55E, 0x0000D606, 0x0000D6AE, 0x0000D756,
    0x0000D7FE, 0x0000D8A6, 0x0000D94E, 0x0000D9F6, 0x0000DA9E, 0x0000DB46,
    0x0000DBEE, 0x0000DC96, 0x0000DD3E, 0x0000DDE6, 0x0000DE8E, 0x0000DF36,
    0x0000DFDE, 0x0000E000, 0x0000E022, 0x0000E0CA, 0x0000E172, 0x0000E21A,
    0x0000E226, 0x0000E2CE, 0x0000E376, 0x0000E398, 0x0000E3BA, 0x0000E462,
    0x0000E50A, 0x0000E5B2, 0x0000E65A, 0x0000E702, 0x0000E7AA, 0x0000E852,
    0x0000E8FA, 0x0000E914, 0x0000E928, 0x0000E9D0, 0x0000EA78, 0x0000EB20,
    0x0000EBC8, 0x0000EC70, 0x0000ED18, 0x0000ED24, 0x0000EDCC, 0x0000EE74,
    0x0000EF1E, 0x0000EF2A, 0x0000EFD2, 0x0000EFDE, 0x0000EFEA, 0x0000F092,
    0x0000F13A, 0x0000F146, 0x0000F152, 0x0000F15E, 0x0000F206, 0x0000F212,
    0x0000F21E, 0x0000F22A, 0x0000F236, 0x0000F242, 0x0000F24E, 0x0000F2F6,
    0x0000F302, 0x0000F3AA, 0x0000F452, 0x0000F45E, 0x0000F4C4, 0x0000F52A,
    0x0000F590, 0x0000F5F6, 0x0000F602, 0x0000F60E, 0x0000F61A, 0x0000F626,
    0x0000F632, 0x0000F63E, 0x0000F64A, 0x0000F6F2, 0x0000F79A, 0x0000F7A6,
    0x0000F84E, 0x0000F8F6, 0x0000F99E, 0x0000FA46, 0x0000FAEE, 0x0000FB98,
    0x0000FBA4, 0x0000FC4C, 0x0000FC58, 0x0000FC64, 0x0000FD0C, 0x0000FD18,
    0x0000FD24, 0x0000FD30, 0x0000FDD8, 0x0000FE80, 0x0000FF28, 0x0000FF34,
    0x0000FFDC, 0x00010084, 0x0001012C, 0x000101D4, 0x0001027C, 0x00010324,
    0x000103CC, 0x00010474, 0x0001051C, 0x000105C4, 0x0001066C, 0x00010714,
    0x000107BC, 0x00010864, 0x0001090C, 0x000109B4, 0x000109C0, 0x00010A68,
    0x00010A74, 0x00010A80, 0x00010A8C, 0x00010A98, 0x00010AA4, 0x00010AB0,
    0x00010ABC, 0x00010AC8, 0x00010AD4, 0x00010B7C, 0x00010B88, 0x00010B94,
    0x00010BA0, 0x00010C48, 0x00010CF0, 0x00010D98, 0x00010DA4, 0x00010E4C,
    0x00010E58, 0x00010E64, 0x00010E70, 0x00010E7C, 0x00010E88, 0x00010E94,
    0x00010EA0, 0x00010F48, 0x00010F54, 0x00010FFC, 0x000110A4, 0x0001114C,
    0x00011158, 0x00011200, 0x000112A8, 0x00011350, 0x0001135C, 0x00011404,
    0x000114AC, 0x000114B8, 0x00011560, 0x0001156C, 0x00011578, 0x00011620,
    0x000116C8, 0x000116D4, 0x000116E0, 0x00011788, 0x00011830, 0x000118D8,
    0x00011980, 0x00011A28, 0x00011AD0, 0x00011B78, 0x00011C20, 0x00011C2C,
    0x00011C38, 0x00011C44, 0x00011C50, 0x00011CF8, 0x00011D04, 0x00011D10,
    0x00011D1C, 0x00011D28, 0x00011D34, 0x00011D40, 0x00011D4C, 0x00011DF4,
    0x00011E00, 0x00011E0C, 0x00011E18, 0x00011E24, 0x00011E30, 0x00011E3C,
    0x00011E48, 0x00011E54, 0x00011E60, 0x00011E6C, 0x00011E78, 0x00011F20,
    0x00011F2C, 0x00011F38, 0x00011F44, 0x00011F50, 0x00011F5C, 0x00011F68,
    0x00011F74, 0x00011F80, 0x00012028, 0x000120D0, 0x000120DC, 0x00012184,
    0x0001222C, 0x000122D4, 0x0001237C, 0x00012388, 0x00012394, 0x0001243C,
    0x00012448, 0x00012454, 0x00012460, 0x0001246C, 0x00012478, 0x00012520,
    0x0001252C, 0x00012538, 0x00012544, 0x00012550, 0x000125F8, 0x00012604,
    0x00012610, 0x0001261C, 0x00012628, 0x00012634, 0x00012640, 0x0001264C,
    0x00012658, 0x00012664, 0x00012670, 0x0001267C, 0x00012688, 0x00012694,
    0x000126A0, 0x000126AC, 0x000126B8, 0x000126C4, 0x000126D0, 0x000126DC,
    0x000126E8, 0x000126F4, 0x00012700, 0x0001270C, 0x00012718, 0x00012724,
    0x00012730, 0x0001273C, 0x00012748, 0x00012754, 0x00012760, 0x0001276C,
    0x00012778, 0x00012784, 0x00012790, 0x0001279C, 0x000127A8, 0x000127B4,
    0x000127C0, 0x000127CC, 0x000127D8, 0x000127E4, 0x000127F0, 0x000127FC,
    0x00012808, 0x00012814, 0x00012820, 0x0001282C, 0x00012838, 0x00012844,
    0x00012850, 0x0001285C, 0x00012868, 0x00012874, 0x00012880, 0x0001288C,
    0x00012898, 0x000128A4, 0x000128B0, 0x000128BC, 0x000128C8, 0x000128D4,
    0x000128E0, 0x000128EC, 0x000128F8, 0x00012904, 0x00012910, 0x0001291C,
    0x00012928, 0x00012934, 0x00012940, 0x0001294C, 0x00012958, 0x00012964,
    0x00012970, 0x0001297C, 0x00012988, 0x00012994, 0x000129A0, 0x000129AC,
    0x000129B8, 0x000129C4, 0x000129D0, 0x000129DC, 0x000129E8, 0x000129F4,
    0x00012A00, 0x00012AA8, 0x00012AB4, 0x00012B5C, 0x00012C04, 0x00012C10,
    0x00012C1C, 0x00012C28, 0x00012C34, 0x00012C40, 0x00012C4C, 0x00012C58,
    0x00012C64, 0x00012C70, 0x00012C7C, 0x00012C88, 0x00012C94, 0x00012CA0,
    0x00012CAC, 0x00012D54, 0x00012D60, 0x00012D6C, 0x00012D78, 0x00012D84,
    0x00012D90, 0x00012D9C, 0x00012DA8, 0x00012DB4, 0x00012DC0, 0x00012E68,
    0x00012E74, 0x00012E80, 0x00012E8C, 0x00012F34, 0x00012F40, 0x00012FE8,
    0x00012FF4, 0x00013000, 0x000130A8, 0x000130B4, 0x000130C0, 0x000130CC,
    0x000130D8, 0x000130E4, 0x000130F0, 0x000130FC, 0x00013108, 0x00013114,
    0x00013120, 0x0001312C, 0x000131D4, 0x000131E0, 0x000131EC, 0x000131F8,
    0x00013204, 0x000132AC, 0x000132B8, 0x000132C4, 0x000132D0, 0x00013378,
    0x00013384, 0x00013390, 0x0001339C, 0x000133A8, 0x000133B4, 0x000133C0,
    0x00013468, 0x00013474, 0x00013480, 0x0001348C, 0x00013498, 0x00013540,
    0x0001354C, 0x00013558, 0x00013600, 0x0001360C, 0x00013618, 0x00013624,
    0x00013630, 0x000136D8, 0x000136E4, 0x000136F0, 0x000136FC, 0x00013708,
    0x000137B0, 0x000137BC, 0x000137C8, 0x000137D4, 0x000137E0, 0x000137EC,
    0x000137F8, 0x00013804, 0x00013810, 0x0001381C, 0x00013828, 0x00013834,
    0x00013840, 0x0001384C, 0x00013858, 0x00013864, 0x00013870, 0x0001387C,
    0x00013888, 0x00013894, 0x000138A0, 0x000138AC, 0x000138B8, 0x000138C4,
    0x000138D0, 0x000138DC, 0x000138E8, 0x000138F4, 0x00013900, 0x0001390C,
    0x00013918, 0x00013924, 0x00013930, 0x0001393C, 0x00013948, 0x00013954,
    0x00013960, 0x0001396C, 0x00013978, 0x00013984, 0x00013990, 0x0001399C,
    0x000139A8, 0x000139B4, 0x000139C0, 0x000139CC, 0x000139D8, 0x000139E4,
    0x000139F0, 0x000139FC, 0x00013A08, 0x00013AB0, 0x00013ABC, 0x00013AC8,
    0x00013AD4, 0x00013B7C, 0x00013C24, 0x00013CCC, 0x00013D74, 0x00013D80,
    0x00013E28, 0x00013ED0, 0x00013EDC, 0x00013F84, 0x0001402C, 0x000140D4,
    0x0001417C, 0x00014188, 0x00014230, 0x000142D8, 0x00014380, 0x00014428,
    0x000144D0, 0x00014578, 0x00014584, 0x0001462C, 0x000146D4, 0x0001477C,
    0x00014788, 0x00014794, 0x0001483C, 0x000148E4, 0x0001498C, 0x00014A34,
    0x00014ADC, 0x00014AE8, 0x00014B90, 0x00014C38, 0x00014C44, 0x00014C50,
    0x00014C5C, 0x00014C68, 0x00014D10, 0x00014DB8, 0x00014E60, 0x00014F08,
    0x00014FB0, 0x00014FBC, 0x00015064, 0x0001510C, 0x000151B4, 0x0001525C,
    0x00015304, 0x000153AC, 0x00015454, 0x000154FC, 0x000155A4, 0x0001564C,
    0x000156F4, 0x0001579C, 0x000157A8, 0x00015850, 0x000158F8, 0x000159A0,
    0x00015A48, 0x00015AF0, 0x00015B98, 0x00015C40, 0x00015CE8, 0x00015D90,
    0x00015E38, 0x00015EE0, 0x00015F88, 0x00015F94, 0x00015FA0, 0x00016048,
    0x00016054, 0x000160FC, 0x000161A4, 0x0001624C, 0x00016258, 0x00016264,
    0x00016270, 0x0001627C, 0x00016288, 0x00016294, 0x0001631C, 0x000163A4,
    0x0001642C, 0x00016438, 0x00016444, 0x000164EC, 0x00016594, 0x0001663C,
    0x000166E4, 0x0001678C, 0x00016834, 0x000168DC, 0x00016970, 0x0001697C,
    0x00016988, 0x00016994, 0x00016A3C, 0x00016AE4, 0x00016AF0, 0x00016AFC,
    0x00016B08, 0x00016BB0, 0x00016C58, 0x00016D00, 0x00016DA8, 0x00016E50,
    0x00016EF8, 0x00016FA0, 0x00017048, 0x000170F0, 0x00017198, 0x00017240,
    0x000172E8, 0x00017390, 0x00017438, 0x000174E0, 0x00017588, 0x00017630,
    0x000176D8, 0x00017780, 0x00017828, 0x000178D0, 0x000178DC, 0x00017964,
    0x000179EC, 0x00017A74, 0x00017AFC, 0x00017B84, 0x00017C0C, 0x00017C94,
    0x00017D1C, 0x00017DA4, 0x00017E2C, 0x00017EB4, 0x00017F3C, 0x00017FC4,
    0x0001804C, 0x000180D4, 0x0001815C, 0x000181E4, 0x0001826C, 0x000182F4,
    0x0001837C, 0x00018404, 0x0001848C, 0x00018514, 0x0001859C, 0x00018624,
    0x000186AC, 0x00018734, 0x000187BC, 0x00018844, 0x000188CC, 0x00018954,
    0x000189DC, 0x00018A64, 0x00018AEC, 0x00018B74, 0x00018B8D, 0x00018BA6,
    0x00018BBF, 0x00018BD8, 0x00018BF1, 0x00018C0A, 0x00018C23, 0x00018C3C,
    0x00018C55, 0x00018C6E, 0x00018C87, 0x00018CA0, 0x00018CB9, 0x00018CD2,
    0x00018CEB, 0x00018D04, 0x00018D1D, 0x00018D36, 0x00018D4F, 0x00018D4F
};
#ifndef TTL_MAIN_CPP
typedef struct BatMapEntry {
    s16 reserved_00[3];
    s16 map;
    s16 first;
    s16 first_zoid;
    s16 second;
    s16 second_zoid;
} BatMapEntry;
#endif

BatMapEntry menu_BatMapData[37] = {
    { { 65, 1670, 1 }, 8, 22, 28, 11, 28 },
    { { 82, 1670, 1 }, 8, 22, 28, 11, 28 },
    { { 72, 1670, 1 }, 8, 22, 28, 11, 28 },
    { { 83, 1667, 2 }, 1, 9, 14, 10, 14 },
    { { 0, 1667, 2 }, 1, 9, 14, 10, 14 },
    { { 75, 1667, 2 }, 1, 9, 14, 10, 14 },
    { { 84, 1675, 3 }, 12, 1, 25, 7, 25 },
    { { 85, 1675, 3 }, 12, 1, 25, 7, 25 },
    { { 10, 1675, 3 }, 12, 1, 25, 7, 25 },
    { { 2, 1683, 4 }, 2, 16, 8, 17, 1 },
    { { 18, 1683, 4 }, 2, 16, 8, 17, 1 },
    { { 6, 1683, 4 }, 2, 16, 8, 17, 1 },
    { { 86, 1679, 5 }, 9, 21, 20, 19, 18 },
    { { 87, 1679, 5 }, 9, 21, 20, 19, 18 },
    { { 88, 1679, 5 }, 9, 21, 20, 19, 18 },
    { { 89, 1665, 6 }, 10, 0, 10, 2, 9 },
    { { 1, 1665, 6 }, 10, 0, 10, 2, 9 },
    { { 76, 1665, 6 }, 10, 0, 10, 2, 9 },
    { { 66, 1669, 7 }, 5, 40, 22, -1, -1 },
    { { 17, 1669, 7 }, 5, 40, 22, -1, -1 },
    { { 54, 1669, 7 }, 5, 40, 22, -1, -1 },
    { { 78, 1666, 8 }, 12, 3, 31, 8, 24 },
    { { 22, 1666, 8 }, 12, 3, 31, 8, 24 },
    { { 11, 1666, 8 }, 12, 3, 31, 8, 24 },
    { { 90, 1678, 9 }, 17, 27, 13, 28, 32 },
    { { 91, 1678, 9 }, 17, 27, 13, 28, 32 },
    { { 92, 1678, 9 }, 17, 27, 13, 28, 32 },
    { { 53, 1674, 10 }, 3, 4, 5, 14, 19 },
    { { 93, 1674, 10 }, 3, 4, 5, 14, 19 },
    { { 23, 1674, 10 }, 3, 4, 5, 14, 19 },
    { { 73, 1688, 11 }, 4, 31, 7, 33, 17 },
    { { 94, 1688, 11 }, 4, 31, 7, 33, 17 },
    { { 95, 1688, 11 }, 4, 31, 7, 33, 17 },
    { { 96, 1684, 12 }, 11, 26, 21, -1, -1 },
    { { 97, 1684, 12 }, 11, 26, 21, -1, -1 },
    { { 98, 1684, 12 }, 11, 26, 21, -1, -1 },
    { { 99, 1669, 12 }, 2, 40, 22, -1, -1 }
};
BatMapEntry menu_MisMapData[60] = {
    { { 65, 1683, 1 }, 19, 16, 28, 17, 1 },
    { { 83, 1670, 2 }, 11, 19, 28, 11, 28 },
    { { 84, 1675, 3 }, 3, 24, 33, 25, 4 },
    { { 2, 1665, 4 }, 6, 0, 10, 2, 1 },
    { { 86, 1676, 5 }, 7, 22, 28, -1, -1 },
    { { 89, 1666, 6 }, 7, 3, 0, 5, 14 },
    { { 66, 1683, 7 }, 8, 16, 8, 23, 2 },
    { { 78, 1692, 8 }, 8, 22, 33, 18, 15 },
    { { 90, 1667, 9 }, 9, 5, 14, 17, 14 },
    { { 53, 1691, 10 }, 9, 37, 32, 38, 15 },
    { { 65, 1683, 11 }, 2, 16, 28, 17, 1 },
    { { 83, 1670, 12 }, 17, 19, 28, 11, 28 },
    { { 84, 1675, 13 }, 10, 24, 33, 25, 4 },
    { { 2, 1665, 14 }, 14, 0, 10, 2, 1 },
    { { 86, 1676, 15 }, 15, 22, 28, -1, -1 },
    { { 89, 1666, 16 }, 8, 3, 0, 5, 14 },
    { { 66, 1683, 17 }, 9, 16, 8, 23, 2 },
    { { 78, 1692, 18 }, 9, 22, 33, 18, 15 },
    { { 90, 1667, 19 }, 9, 5, 14, 17, 14 },
    { { 53, 1691, 20 }, 14, 37, 32, 38, 15 },
    { { 65, 1683, 21 }, 12, 16, 28, 17, 1 },
    { { 83, 1670, 22 }, 2, 19, 28, 11, 28 },
    { { 84, 1675, 23 }, 4, 24, 33, 25, 4 },
    { { 2, 1665, 24 }, 9, 0, 10, 2, 1 },
    { { 86, 1676, 25 }, 5, 22, 28, -1, -1 },
    { { 89, 1666, 26 }, 14, 3, 0, 5, 14 },
    { { 66, 1683, 27 }, 18, 16, 8, 23, 2 },
    { { 78, 1692, 28 }, 13, 22, 33, 18, 15 },
    { { 90, 1667, 29 }, 13, 5, 14, 17, 14 },
    { { 53, 1691, 30 }, 5, 37, 32, 38, 15 },
    { { 65, 1683, 31 }, 14, 16, 28, 17, 1 },
    { { 83, 1670, 32 }, 14, 19, 28, 11, 28 },
    { { 84, 1675, 33 }, 15, 24, 33, 25, 4 },
    { { 2, 1665, 34 }, 1, 0, 10, 2, 1 },
    { { 86, 1676, 35 }, 6, 22, 28, -1, -1 },
    { { 89, 1666, 36 }, 9, 3, 0, 5, 14 },
    { { 99, 1669, 37 }, 9, 40, 22, -1, -1 },
    { { 89, 1666, 38 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 39 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 40 }, 9, 3, 0, 5, 14 },
    { { 89, 1666, 41 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 42 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 43 }, 9, 3, 0, 5, 14 },
    { { 89, 1666, 44 }, 7, 3, 0, 5, 14 },
    { { 89, 1666, 45 }, 7, 3, 0, 5, 14 },
    { { 89, 1666, 46 }, 7, 3, 0, 5, 14 },
    { { 89, 1666, 47 }, 7, 3, 0, 5, 14 },
    { { 89, 1666, 48 }, 8, 3, 0, 5, 14 },
    { { 89, 1666, 49 }, 9, 3, 0, 5, 14 },
    { { 89, 1666, 50 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 51 }, 9, 3, 0, 5, 14 },
    { { 89, 1666, 52 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 53 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 54 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 55 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 56 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 57 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 58 }, 0, 3, 0, 5, 14 },
    { { 89, 1666, 59 }, 0, 3, 0, 5, 14 },
    { { 99, 1669, 60 }, 0, 40, 22, -1, -1 }
};
static HSD_WObjDesc infinite_light_pos_wobjdesc = { 0, { 0.0f, 1000.0f, 1000.0f }, 0 };
static HSD_LightDesc infinite_light = {
    0, 0, 13, 0, { 255, 255, 255, 255 }, &infinite_light_pos_wobjdesc, 0, { &shininess }
};
static inline void menustrMainOwner777(void)
{
    /* {label, 2, n, 0} rows; labels are sStoryModeLabel .. sZoidSettingLabel (ttl_main.cpp) */
    static u32 menustrMain[28] = {
        0x800F0608, 0x00000002, 0x00000064, 0x00000000, 0x800F0614, 0x00000002,
        0x000000C8, 0x00000000, 0x800F0628, 0x00000002, 0x0000012C, 0x00000000,
        0x800F063C, 0x00000002, 0x00000190, 0x00000000, 0x800F0650, 0x00000002,
        0x000001F4, 0x00000000, 0x800F065C, 0x00000002, 0x00002328, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000
    };
}
static inline void menustrMainOwner810(void)
{
    /* labels: sRepublicArmyLabel and the .sdata2 string "teikoku-gun" (Empire army) */
    static u32 menustrMain[12] = {
        0x800F06D0, 0x00000002, 0x00000067, 0x00000000, 0x802A0934, 0x00000002,
        0x00000068, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    };
}
u8 menufarmjno[12] = { 0, 2, 2, 2, 2, 2, 2, 2, 8, 8, 0xFF, 0xFF };
u8 menufarmano[12] = { 0, 0, 1, 2, 3, 4, 5, 6, 0, 1, 0xFF, 0xFF };
Vec3 menubackcampos = { 0.0f, 0.0f, 0.0f };
Vec3 menubackcambak = { 0.0f, 0.0f, 0.0f };
Vec3 menubackintpos = { 0.0f, 0.0f, 0.0f };
Vec3 menubackintbak = { 0.0f, 0.0f, 0.0f };
u32 stagename_mis[52] = {
    0x802A09A8, 0x802A09AC, 0x802A09B0, 0x802A09B4, 0x802A09B8, 0x802A09BC,
    0x802A09B8, 0x802A09C0, 0x802A09C4, 0x802A09B8, 0x802A09C8, 0x802A09CC,
    0x802A09D0, 0x802A09D4, 0x802A09D8, 0x802A09DC, 0x802A09E0, 0x802A09B8,
    0x802A09B8, 0x802A09A8, 0x802A09AC, 0x802A09B0, 0x802A09B4, 0x802A09E4,
    0x802A09E8, 0x802A09EC, 0x802A09C8, 0x802A09CC, 0x802A09D0, 0x802A09D4,
    0x802A09D8, 0x802A09DC, 0x802A09E0, 0x802A09F0, 0x802A09F4, 0x802A09B8,
    0x802A09F8, 0x802A09B8, 0x802A09B8, 0x802A09FC, 0x802A09B8, 0x802A09B8,
    0x802A0A00, 0x802A09B8, 0x802A09B8, 0x802A0A04, 0x802A09B8, 0x802A0A08,
    0x802A0A0C, 0x802A09B8, 0x802A0A10, 0x802A0928
};
#ifdef TTL_MAIN_CPP
extern s16 TEA_menufnc(s16 *menup, s16 *menust, s16 maxn, s16 max);
extern s32 menu_StageUpDownFlag;
extern s16 dlgzoidno;
extern s32 menu_sDispBattleStageDown(s32 mode);
extern void menu_sDispBattleEntry(void);
extern void menu_BattleSet_EntryPersonPartnerExit(void);
extern void menu_sDispSetButton(void);
extern void ttl_WeaponAllMount(s16 slot);
extern void menufncZoidBattle_BattleMenuReturn(void);
extern void SeCancel(void);
extern void SeRet(void);
extern void SeSelectB(void);
extern void TEA_VoiceOn(u8 character, s32 voice);
extern void TEA_setvsync(void);
extern void menuSetTitle(s16 type);
extern s32 menuCursor;
extern s32 menuParticles;
extern s8 menufarmmode;
extern s32 ZoidInit(ZoidState *zoid, s32 type);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void ZoidWeaponPurge(ZoidState *zoid);
extern void ZoidPurge(ZoidState *zoid);
extern void ttl_WeaponAllUnMount(s16 slot);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncZoidBattle_BattleMenuEntry(void)
{
    s32 unused[12];
    s32 i;
    s16 j;
    s16 x;
    s16 z2;
    s16 z1;
    s16 zd1;
    s16 zd2;

    menumode = 3;
    menuCursor = 0;
    menuParticles = 0;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++)
        menufarmanm[i] = 0;
    vsyncN = 0;
    menucuranm = 1;
    menuSetTitle(1);
    TEA_setvsync();
    menufarmmode = 1;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    if (menuZoidBattleModeSingleTeam == 1) {
        menufarmmh[2] = 2;
        menufarmmn[2] = 2;
    } else if (menuZoidBattleStage != -1) {
        menufarmmh[2] = 1;
        menufarmmn[2] = 1;
    } else {
        menufarmmh[2] = 2;
        menufarmmn[2] = 2;
    }
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menufarmcl[4] = 0;
    menufarmsl[4] = 0;
    menufarmst[4] = 0;
    menufarmmh[4] = 2;
    menufarmmn[4] = 2;
    menufarmcl[5] = 0;
    menufarmsl[5] = 0;
    menufarmst[5] = 0;
    menufarmmh[5] = 8;
    menufarmmn[5] = 2;
    menufarmcl[6] = 0;
    menufarmsl[6] = 0;
    menufarmst[6] = 0;
    menufarmmh[6] = 8;
    menufarmmn[6] = 2;
    menufarmcl[7] = 0;
    menufarmsl[7] = 0;
    menufarmst[7] = 0;
    menufarmmh[7] = 8;
    menufarmmn[7] = 2;
    menufarmcl[8] = 0;
    menufarmsl[8] = 0;
    menufarmst[8] = 0;
    menufarmmh[8] = 8;
    menufarmmn[8] = 2;
    menufarmsl[5] = 0;
    menufarmmn[5] = IveSave[0].person_list_count;
    if (menufarmmn[5] < menufarmmh[5])
        menufarmmh[5] = menufarmmn[5];
    menufarmst[5] = -1;
    menufarmsl[6] = 0;
    menufarmmn[6] = IveSave[0].person_list_count;
    if (menufarmmn[6] < menufarmmh[6])
        menufarmmh[6] = menufarmmn[6];
    menufarmst[6] = -1;
    menufarmsl[7] = IveSave[0].selected_zoid_slot;
    menufarmmn[7] = IveSave[0].owned_zoid_count;
    if (menufarmmn[7] < menufarmmh[7])
        menufarmmh[7] = menufarmmn[7];
    menufarmst[7] = -1;
    menufarmsl[8] = IveSave[0].partner_zoid_slot;
    menufarmmn[8] = IveSave[0].owned_zoid_count;
    if (menufarmmn[8] < menufarmmh[8])
        menufarmmh[8] = menufarmmn[8];
    menufarmst[8] = -1;
    OSReport(sLogZoidNum, IveSave[0].owned_zoid_count);
    menufarmmh[5] = 8;
    menufarmmh[6] = 8;
    menufarmmn[5] = IveSave[0].person_list_count;
    menufarmmn[6] = IveSave[0].person_list_count;
    IveSave[4].selected_zoid = IveSave[0].selected_zoid;
    IveSave[4].partner_zoid = IveSave[0].partner_zoid;
    zd1 = IveSave[0].selected_zoid;
    zd2 = IveSave[0].partner_zoid;
    z1 = IveSave[0].selected_person;
    z2 = IveSave[0].partner_person;
    OSReport(sLogEntry, z1, z2, IveSave[0].selected_zoid, IveSave[0].partner_zoid);
    for (i = 0; i < IveSave[0].person_list_count; i++) {
        if (IveSave[0].selected_person == IveSave[0].person_list[i]) {
            j = i;
            menufarmcl[5] = j;
            menufarmsl[5] = j;
            menufarmst[5] = -1;
            IveSave[0].selected_person_index = j;
            break;
        }
    }
    for (i = 0; i < IveSave[0].person_list_count; i++) {
        if (IveSave[0].partner_person == IveSave[0].person_list[i]) {
            j = i;
            menufarmcl[6] = j;
            menufarmsl[6] = j;
            menufarmst[6] = -1;
            IveSave[0].partner_person_index = j;
            break;
        }
    }
    menufarmcl[5] = 0;
    menufarmsl[5] = 0;
    menufarmst[5] = 0;
    menufarmmn[5] = menufarmmh[5] = menuZoidBattleModeSingleTeam + 1;
    menufarmcl[6] = 0;
    menufarmsl[6] = 0;
    menufarmst[6] = 0;
    menufarmmn[6] = menufarmmh[6] = menuZoidBattleModeSingleTeam + 1;
    menu_BattleSet_EntryPersonPartnerExit();
    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
    OSReport(sLogZoidBattleEntryStart, IveSave[0].owned_zoid_count);
    while (1) {
        sPadAll();
        menu_sDispSetButton();
        if (menumode <= 2)
            menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if (menumode >= 5)
            menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        menu_BattleSet_EntryPersonPartnerExit();
        menu_sDispBattleEntry();
        if (sPad1->pressed_b != 0) {
            SeCancel();
            if (menumode == 2) {
                if (menufarmcl[2] == 1)
                    continue;
                continue;
            } else if (menumode <= 4) {
                menumode = 2;
                menufarmsl[2] = 2;
                menufarmcl[2] = 2;
            } else if (menumode == 5) {
                if (IveSave[0].selected_person == IveSave[0].partner_person) {
                    if (IveSave[0].selected_person == z1)
                        IveSave[0].selected_person = z1;
                    else
                        IveSave[0].selected_person = z2;
                }
                menumode = 3;
            } else if (menumode == 6) {
                if (IveSave[0].partner_person == IveSave[0].selected_person) {
                    if (IveSave[0].partner_person == z2)
                        IveSave[0].partner_person = z1;
                    else
                        IveSave[0].partner_person = z2;
                }
                menumode = 4;
            } else if (menumode == 7) {
                IveSave[0].selected_zoid = zd1;
                menumode = 3;
            } else if (menumode == 8) {
                IveSave[0].partner_zoid = zd2;
                menumode = 4;
            }
        }
        if (sPad1->pressed_a != 0) {
            switch (menumode) {
            case 2:
                if (menufarmcl[menumode] == 2) {
                    SeRet();
                    menumode = -1;
                    menufncZoidBattle_BattleMenuReturn();
                    if (menuZoidBattleStage == -1) {
                        menuZoidBattleStage = 0;
                        GameMode.win = 1;
                    }
                    IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                    OSReport(sLogZd1Zd2, IveSave[0].selected_zoid, IveSave[0].partner_zoid);
                    return 204;
                }
                if (menufarmcl[2] == 1) {
                    SeRet();
                    menumode = 4;
                } else if (menufarmcl[2] == 0) {
                    SeRet();
                    menumode = 3;
                }
                break;
            case 3:
                SeRet();
                if (menufarmcl[3] == 0)
                    menumode = 5;
                if (menufarmcl[3] == 1) {
                    menumode = 7;
                    IveSave[0].previous_zoid_slot = IveSave[0].selected_zoid_slot;
                    IveSave[0].previous_partner_zoid_slot = IveSave[0].partner_zoid_slot;
                    menufarmcl[menumode] = 0;
                    menufarmsl[menumode] = 0;
                    menufarmst[menumode] = 0;
                    OSReport("dummy\n");
                }
                break;
            case 4:
                SeRet();
                if (menufarmcl[4] == 0)
                    menumode = 6;
                if (menufarmcl[4] == 1) {
                    IveSave[0].previous_zoid_slot = IveSave[0].selected_zoid_slot;
                    IveSave[0].previous_partner_zoid_slot = IveSave[0].partner_zoid_slot;
                    menumode = 8;
                    menufarmcl[menumode] = 0;
                    menufarmsl[menumode] = 0;
                    menufarmst[menumode] = 0;
                }
                break;
            case 5:
                if (menufarmcl[menumode] == 1) {
                    SeRet();
                    x = IveSave[0].selected_person;
                    IveSave[0].selected_person = IveSave[0].partner_person;
                    IveSave[0].partner_person = x;
                    TEA_VoiceOn(IveSave[0].selected_person, 1);
                } else {
                    SeCancel();
                }
                menumode = 3;
                break;
            case 6:
                if (menufarmcl[menumode] == 0) {
                    SeRet();
                    x = IveSave[0].selected_person;
                    IveSave[0].selected_person = IveSave[0].partner_person;
                    IveSave[0].partner_person = x;
                    TEA_VoiceOn(IveSave[0].partner_person, 1);
                } else {
                    SeCancel();
                }
                menumode = 4;
                break;
            case 7:
                menumode = 3;
                if (menuZoidBattleModeSingleTeam == 1 && IveSave[0].partner_zoid_slot == menufarmcl[7]) {
                    IveSave[0].selected_zoid = zd1;
                    menufarmcl[7] = menufarmsl[7] = IveSave[0].previous_zoid_slot;
                    menufarmst[7] = 0;
                    SeCancel();
                    continue;
                }
                SeRet();
                menumode = 3;
                menu_StageUpDownFlag = 0;
                while (menu_sDispBattleStageDown(1) == 0)
                    menu_sDispBattleEntry();
                ttl_WeaponAllUnMount(IveSave[0].previous_zoid_slot);
                ZoidWeaponPurge(&Zoid[0]);
                ZoidPurge(&Zoid[0]);
                IveSave[0].selected_zoid_slot = menufarmcl[7];
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                ZoidInit(&Zoid[0], IveSave[0].selected_zoid);
                ZoidSetAnim(&Zoid[0], 103);
                ZoidColor(&Zoid[0], (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot], 0);
                ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                menu_StageUpDownFlag = 0;
                while (menu_sDispBattleStageDown(0) == 0)
                    menu_sDispBattleEntry();
                zd1 = dlgzoidno = IveSave[0].selected_zoid;
                menumode = 3;
                break;
            case 8:
                menumode = 4;
                if (IveSave[0].selected_zoid_slot == menufarmcl[8]) {
                    IveSave[0].partner_zoid = zd2;
                    menufarmcl[8] = menufarmsl[8] = IveSave[0].previous_partner_zoid_slot;
                    menufarmst[8] = 0;
                    SeCancel();
                    continue;
                }
                SeRet();
                zd2 = IveSave[0].partner_zoid;
                IveSave[0].partner_zoid_slot = menufarmcl[8];
                IveSave[0].partner_zoid = IveSave[0].owned_zoids[IveSave[0].partner_zoid_slot];
                menumode = 4;
                break;
            }
        }
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0) {
            if (menuZoidBattleModeSingleTeam == 1) {
                if (menumode == 4) {
                    menumode = 3;
                    menufarmsl[2] = 0;
                    menufarmcl[2] = 0;
                }
            } else if (menumode == 2 && menufarmcl[2] == 1) {
                menufarmsl[2] = 0;
                menufarmcl[2] = 0;
            }
            if (menumode == 3 || menumode == 4)
                SeSelectB();
            if (menumode == 7)
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
            if (menumode == 8)
                IveSave[0].partner_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
        } else if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0) {
            if (menumode == 2 && menufarmcl[2] >= 2) {
                menufarmsl[2] = 2;
                menufarmcl[2] = 2;
            }
            if (menuZoidBattleModeSingleTeam == 1 && menumode == 3) {
                menumode = 4;
                menufarmsl[2] = 1;
                menufarmcl[2] = 1;
            }
            if (menumode == 3 || menumode == 4)
                SeSelectB();
            if (menumode == 7)
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
            if (menumode == 8)
                IveSave[0].partner_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
        } else {
            if (sPad1->pressed_dpad_left != 0 || sPad1->pressed_stick_left != 0) {
                if (menumode == 2 && menufarmcl[2] == 2)
                    menumode = 3;
                if (menumode == 3 || menumode == 4) {
                    SeSelectB();
                    if (menufarmcl[menumode] != 0) {
                        menufarmsl[menumode] = 0;
                        menufarmcl[menumode] = 0;
                    }
                }
            } else if (sPad1->pressed_dpad_right != 0 || sPad1->pressed_stick_right != 0) {
                if (menumode == 2 && menufarmcl[2] != 2) {
                    menufarmsl[2] = 2;
                    menufarmcl[2] = 2;
                }
                if (menumode == 3 || menumode == 4) {
                    SeSelectB();
                    if (menufarmcl[menumode] == 0) {
                        menufarmsl[menumode] = 1;
                        menufarmcl[menumode] = 1;
                    } else if (menufarmcl[menumode] == 1) {
                        menumode = 2;
                        menufarmsl[2] = 2;
                        menufarmcl[2] = 2;
                    }
                }
            }
        }
    }
}
#pragma pop
#pragma readonly_strings off

#else
static u32 pool_4703[9] = {
    0x8004C734, 0x8004C734, 0x8004C3B4, 0x8004C468, 0x8004C4C4, 0x8004C514,
    0x8004C560, 0x8004C5AC, 0x8004C6CC
};
#endif
static Vec3 eyeCam = { 0.0f, 0.0f, 100.0f };
#ifdef TTL_MAIN_CPP
extern void sMakeMatrix(HSD_JObj *joint);

void menu_sDispBattleShopHaveListDsip(void)
{
    s32 idx = 21;
    s32 n = 8;
    s32 result;

    if (menusetbtanm[8].cur != menusetbtanm[8].old) {
        menusetbtanm[8].state = 1;
        menusetbtanm[8].old = menusetbtanm[8].cur;
    }
    if (menusetbtanm[8].state == 1) {
        menusetbtanm[8].state = 2;
        SetAnimArc2(menu1p, 21, menusetbtanm[n].cur);
    }
    if (menusetbtanm[8].state == 2) {
        result = jobjAnim(menu1p->models[idx]);
        sMakeMatrix(menu1p->models[idx]);
        if (result != 0) {
            menusetbtanm[8].state = 3;
            menuanmend = 1;
            switch (menusetbtanm[8].cur) {
            case 0:
                menusetbtanm[8].cur = 0;
                menusetbtanm[8].state = 2;
                break;
            case 1:
                menusetbtanm[8].cur = 2;
                menusetbtanm[8].state = 2;
                break;
            case 2:
                menusetbtanm[8].cur = 2;
                menusetbtanm[8].state = 2;
                break;
            case 3:
                menusetbtanm[8].cur = 0;
                menusetbtanm[8].state = 2;
                break;
            case 4:
                menusetbtanm[8].cur = 5;
                menusetbtanm[8].state = 2;
                break;
            case 5:
                menusetbtanm[8].cur = 5;
                menusetbtanm[8].state = 2;
                break;
            case 6:
                menusetbtanm[8].cur = 0;
                menusetbtanm[8].state = 2;
                break;
            case 7:
                menusetbtanm[8].cur = 8;
                menusetbtanm[8].state = 2;
                break;
            case 8:
                menusetbtanm[8].cur = 8;
                menusetbtanm[8].state = 2;
                break;
            case 9:
                menusetbtanm[8].cur = 0;
                menusetbtanm[8].state = 2;
                break;
            default:
                menusetbtanm[8].state = 2;
                break;
            }
            SetAnimArc2(menu1p, 21, menusetbtanm[n].cur);
            jobjAnim(menu1p->models[idx]);
            sMakeMatrix(menu1p->models[idx]);
        }
    }
    HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
}
#else
static u32 pool_6908[10] = {
    0x80053CD4, 0x80053CE8, 0x80053CF8, 0x80053D08, 0x80053D1C, 0x80053D30,
    0x80053D44, 0x80053D58, 0x80053D6C, 0x80053D80
};
#endif
#ifdef TTL_MAIN_CPP
void menu_sDispBattleShopLButtonAnimZoidWepOptSub(void)
{
    s32 idx = 17;
    s32 n = 7;
    s32 result;

    if (menusetbtanm[7].cur != menusetbtanm[7].old) {
        menusetbtanm[7].state = 1;
        menusetbtanm[7].old = menusetbtanm[7].cur;
    }
    if (menusetbtanm[7].state == 1) {
        menusetbtanm[7].state = 2;
        SetAnimArc2(menu1p, 17, menusetbtanm[n].cur);
    }
    if (menusetbtanm[7].state == 2) {
        result = jobjAnim(menu1p->models[idx]);
        sMakeMatrix(menu1p->models[idx]);
        if (result != 0) {
            menusetbtanm[7].state = 3;
            menuanmend = 1;
            switch (menusetbtanm[7].cur) {
            case 0:
                menusetbtanm[7].cur = 1;
                menusetbtanm[7].state = 2;
                break;
            case 1:
                menusetbtanm[7].cur = 1;
                menusetbtanm[7].old = 2;
                break;
            case 2:
                menusetbtanm[7].cur = 3;
                menusetbtanm[7].old = 2;
                break;
            case 3:
                menusetbtanm[7].cur = 3;
                menusetbtanm[7].old = 2;
                break;
            case 4:
                menusetbtanm[7].cur = 1;
                menusetbtanm[7].old = 2;
                break;
            case 5:
                menusetbtanm[7].cur = 6;
                menusetbtanm[7].old = 2;
                break;
            case 6:
                menusetbtanm[7].cur = 6;
                menusetbtanm[7].old = 2;
                break;
            case 7:
                menusetbtanm[7].cur = 1;
                menusetbtanm[7].old = 2;
                break;
            case 8:
                menusetbtanm[7].cur = 9;
                menusetbtanm[7].old = 2;
                break;
            case 9:
                menusetbtanm[7].cur = 9;
                menusetbtanm[7].old = 2;
                break;
            case 10:
                menusetbtanm[7].cur = 1;
                menusetbtanm[7].old = 2;
                break;
            case 11:
                menusetbtanm[7].cur = 12;
                menusetbtanm[7].old = 2;
                break;
            case 12:
                menusetbtanm[7].cur = 12;
                menusetbtanm[7].old = 2;
                break;
            case 13:
                menusetbtanm[7].cur = 1;
                menusetbtanm[7].old = 2;
                break;
            case 14:
                menusetbtanm[7].cur = 14;
                menusetbtanm[7].old = 14;
                menusetbtanm[7].state = 3;
                return;
            default:
                menusetbtanm[7].state = 2;
                break;
            }
            SetAnimArc2(menu1p, 17, menusetbtanm[n].cur);
            jobjAnim(menu1p->models[idx]);
            sMakeMatrix(menu1p->models[idx]);
        }
    }
    HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
}
#else
static u32 pool_7070[15] = {
    0x80054AA0, 0x80054AB0, 0x80054AC0, 0x80054AD0, 0x80054AE0, 0x80054AF0,
    0x80054B04, 0x80054B18, 0x80054B28, 0x80054B3C, 0x80054B50, 0x80054B60,
    0x80054B74, 0x80054B88, 0x80054B98
};
#endif
#pragma force_active off

#endif

#if !defined(TTL_MAIN_CPP) || defined(TTL_MAIN_DATA_TAIL)
#ifndef ZOIDS_TTL_MAIN_DATA_TAIL_H
#define ZOIDS_TTL_MAIN_DATA_TAIL_H

#ifdef TTL_MAIN_CPP
#pragma readonly_strings on
#pragma push
#pragma dont_inline on
extern s64 OSGetTime(void);
extern void menuZoidBattleGoPartsOptSet_GameZoid(s16 game, s16 save, s16 ms, s32 flag);
extern u32 VIGetRetraceCount(void);
extern void ttl_GameZoidSetZoidDefParts(s16 game, s16 zoid);

void menuMissionGo(void)
{
    s16 i;
    s16 pick;
    s16 slot;

    for (i = 0; i < 10; i++)
        GameZoid[i].type = -1;
    slot = IveSave[0].selected_zoid_slot;
    menuZoidBattleGoPartsOptSet_GameZoid(0, 0, slot, 0);
    if (menuZoidBattleModeSingleTeam == 1) {
        menuZoidBattleGoPartsOptSet_GameZoid(1, 0, IveSave[0].partner_zoid_slot, 1);
    } else {
        GameZoid[1].type = -1;
        GameZoid[1].person = -1;
        GameZoid[1].color = IveSave[0].zoid_colors[slot];
        for (i = 0; i < 28; i++) {
            GameZoid[1].weapons[i] = -1;
            GameZoid[1].reserved_3B[i] = 0;
        }
    }
    while (1) {
        pick = IveSave[0].person_list[(s16)((OSGetTime() / (__OSBusClock / 4 / 1000)) % IveSave[0].person_list_count)];
        if (IveSave[0].selected_person != pick && IveSave[0].partner_person != pick)
            break;
    }
    IveSave[2].selected_person = pick;
    switch (IveSave[2].selected_person) {
    case 0:
        IveSave[2].selected_zoid = 3;
        break;
    case 1:
        IveSave[2].selected_zoid = 2;
        break;
    case 2:
        IveSave[2].selected_zoid = 1;
        break;
    case 4:
        IveSave[2].selected_zoid = 5;
        break;
    case 13:
        IveSave[2].selected_zoid = 0;
        break;
    case 17:
        IveSave[2].selected_zoid = 15;
        break;
    case 22:
        IveSave[2].selected_zoid = 23;
        break;
    case 23:
        IveSave[2].selected_zoid = 4;
        break;
    default:
        IveSave[2].selected_zoid = 3;
        break;
    }
    while (1) {
        pick = IveSave[0].person_list[(s16)(VIGetRetraceCount() % IveSave[0].person_list_count)];
        if (IveSave[0].selected_person != pick && IveSave[0].partner_person != pick)
            break;
        pick = IveSave[0].person_list[(s16)((OSGetTime() / (__OSBusClock / 4 / 1000)) % IveSave[0].person_list_count)];
        if (IveSave[0].selected_person != pick && IveSave[0].partner_person != pick)
            break;
    }
    IveSave[3].selected_person = pick;
    switch (IveSave[3].selected_person) {
    case 0:
        IveSave[3].selected_zoid = 3;
        break;
    case 1:
        IveSave[3].selected_zoid = 2;
        break;
    case 2:
        IveSave[3].selected_zoid = 1;
        break;
    case 4:
        IveSave[3].selected_zoid = 5;
        break;
    case 13:
        IveSave[3].selected_zoid = 0;
        break;
    case 17:
        IveSave[3].selected_zoid = 15;
        break;
    case 22:
        IveSave[3].selected_zoid = 23;
        break;
    case 23:
        IveSave[3].selected_zoid = 4;
        break;
    default:
        IveSave[3].selected_zoid = 3;
        break;
    }
    GameZoid[5].person = IveSave[2].selected_person;
    GameZoid[6].person = IveSave[3].selected_person;
    ttl_GameZoidSetZoidDefParts(5, IveSave[2].selected_zoid);
    ttl_GameZoidSetZoidDefParts(6, IveSave[3].selected_zoid);
    OSReport(sLogGameZoidZ, GameZoid[0].type, GameZoid[1].type, GameZoid[5].type, GameZoid[6].type);
    OSReport(sLogGameZoidP, GameZoid[0].person, GameZoid[1].person, GameZoid[5].person, GameZoid[6].person);
}
#pragma pop
#pragma readonly_strings off
#else
#pragma force_active on
static u32 pool_9598[24] = {
    0x8005CE70, 0x8005CE7C, 0x8005CE88, 0x8005CED0, 0x8005CE94, 0x8005CED0,
    0x8005CED0, 0x8005CED0, 0x8005CED0, 0x8005CED0, 0x8005CED0, 0x8005CED0,
    0x8005CED0, 0x8005CEA0, 0x8005CED0, 0x8005CED0, 0x8005CED0, 0x8005CEAC,
    0x8005CED0, 0x8005CED0, 0x8005CED0, 0x8005CED0, 0x8005CEB8, 0x8005CEC4
};
static u32 pool_9597[24] = {
    0x8005CD30, 0x8005CD3C, 0x8005CD48, 0x8005CD90, 0x8005CD54, 0x8005CD90,
    0x8005CD90, 0x8005CD90, 0x8005CD90, 0x8005CD90, 0x8005CD90, 0x8005CD90,
    0x8005CD90, 0x8005CD60, 0x8005CD90, 0x8005CD90, 0x8005CD90, 0x8005CD6C,
    0x8005CD90, 0x8005CD90, 0x8005CD90, 0x8005CD90, 0x8005CD78, 0x8005CD84
};
#pragma force_active off
#endif
#ifdef TTL_MAIN_CPP
extern s8 vsman;
extern s8 menuvsmode[4];
extern s32 flag_menuvsenthuman[2];
extern s32 flag_menuvsentzoid[2];
extern s16 flag_VsEntryLoadButton[2][2];
extern s16 flag_VsFarmPlayer1Icon;
extern s16 flag_VsFarmPlayer2Icon;
extern void menuSetTitleButton(s16 type);
extern s32 TEA_menufnc2p(s16 *menup, s16 *menust, s16 maxn, s16 max);
extern void menu_sDispVsEntry(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncZoidVsMenuEntry(void)
{
    s32 unused[5];
    s32 i;
    s32 j;
    s16 k;
    s16 n;
    s16 sel;
    u8 map;
    u8 stage;

    menuCursor = 0;
    menuParticles = 0;
    menuvsmode[0] = 0;
    menuvsmode[1] = 1;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++)
        menufarmanm[i] = 0;
    OSReport(sLogVsEntry);
    vsyncN = 0;
    menuSetTitle(1);
    menuSetTitleButton(11);
    TEA_setvsync();
    menufarmmode = 1;
    menufarmcl[0] = 0;
    menufarmsl[0] = 0;
    menufarmst[0] = 0;
    menufarmmh[0] = 4;
    menufarmmn[0] = 4;
    menufarmcl[1] = 0;
    menufarmsl[1] = 0;
    menufarmst[1] = 0;
    menufarmmh[1] = 4;
    menufarmmn[1] = 4;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    menufarmmh[2] = 4;
    menufarmmn[2] = 4;
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 4;
    menufarmmn[3] = 4;
    menufarmsl[4] = 0;
    menufarmmn[4] = IveSave[0].person_list_count;
    menufarmst[4] = -1;
    menufarmmh[4] = 4;
    menufarmsl[5] = 0;
    menufarmmn[5] = IveSave[1].person_list_count;
    menufarmst[5] = -1;
    menufarmmh[5] = 4;
    for (i = 0; i < 2; i++) { menufarmsl[i + 6] = IveSave[i].selected_zoid_slot; menufarmmn[i + 6] = IveSave[i].owned_zoid_count; menufarmst[i + 6] = -1; menufarmmh[i + 6] = 4; }
    menufarmmh[4] = IveSave[0].person_list_count;
    if (menufarmmh[4] >= 4) menufarmmh[4] = 4;
    menufarmmn[4] = IveSave[0].person_list_count;
    menufarmmh[5] = IveSave[0].person_list_count;
    if (menufarmmh[5] >= 4) menufarmmh[5] = 4;
    menufarmmn[5] = IveSave[1].person_list_count;
    if (IveSave[0].owned_zoid_count > menufarmmn[6]) menufarmmn[6] = IveSave[0].owned_zoid_count;
    if (menufarmmn[6] < menufarmmh[6]) menufarmmh[6] = menufarmmn[6];
    if (((GameSaveRecord *)&IveSave[1])->owned_zoid_count < menufarmmh[7]) menufarmmh[7] = ((GameSaveRecord *)&IveSave[1])->owned_zoid_count;
    if (menufarmmn[7] < menufarmmh[7]) menufarmmh[7] = menufarmmn[7];
    flag_menuvsenthuman[0] = 0;
    flag_menuvsenthuman[1] = 0;
    flag_menuvsentzoid[0] = 0;
    flag_menuvsentzoid[1] = 0;
    vsman = 0;
    flag_VsEntryLoadButton[vsman][1] = 2;
    flag_VsEntryLoadButton[vsman][0] = 1;
    vsman = 1;
    flag_VsEntryLoadButton[vsman][1] = 2;
    flag_VsEntryLoadButton[vsman][0] = 1;
    menucuranm = 1;
    menuSetTitle(1);
    menuSetTitleButton(11);
    OSReport(sLogVsEntrySt);
    while (1) {
        sPadAll();
        for (vsman = 0; vsman < 2; vsman++) {
            if (vsman == 0) {
                menufarmcl[menuvsmode[vsman]] = TEA_menufnc(&menufarmsl[menuvsmode[vsman]], &menufarmst[menuvsmode[vsman]], menufarmmn[menuvsmode[vsman]], menufarmmh[menuvsmode[vsman]]);
                if (menuvsmode[vsman] == 0) {
                    if (menufarmcl[menuvsmode[vsman]] == 1)
                        flag_VsFarmPlayer1Icon = 5;
                    else if (menufarmcl[menuvsmode[vsman]] == 3)
                        flag_VsFarmPlayer1Icon = 4;
                    else
                        flag_VsFarmPlayer1Icon = -1;
                } else {
                    flag_VsFarmPlayer1Icon = -1;
                }
            }
            if (vsman == 1) {
                menufarmcl[menuvsmode[vsman]] = (u16)TEA_menufnc2p(&menufarmsl[menuvsmode[vsman]], &menufarmst[menuvsmode[vsman]], menufarmmn[menuvsmode[vsman]], menufarmmh[menuvsmode[vsman]]);
                if (menuvsmode[vsman] == 1) {
                    if (menufarmcl[menuvsmode[vsman]] == 1)
                        flag_VsFarmPlayer2Icon = 5;
                    else if (menufarmcl[menuvsmode[vsman]] == 3)
                        flag_VsFarmPlayer2Icon = 4;
                    else
                        flag_VsFarmPlayer2Icon = -1;
                } else {
                    flag_VsFarmPlayer2Icon = -1;
                }
            }
            if ((sPad1->pressed_up != 0 && vsman == 0) || (sPad1->pressed_down != 0 && vsman == 0)) {
                if (menuvsmode[vsman] == 0 && menufarmcl[vsman] == 1) {
                    flag_VsEntryLoadButton[vsman][1] = 3;
                    flag_VsEntryLoadButton[vsman][0] = 1;
                } else {
                    flag_VsEntryLoadButton[vsman][1] = 2;
                    flag_VsEntryLoadButton[vsman][0] = 1;
                }
            }
            if ((sPad2->pressed_up != 0 && vsman == 1) || (sPad2->pressed_down != 0 && vsman == 1)) {
                if (menuvsmode[vsman] == 1 && menufarmcl[vsman] == 1) {
                    flag_VsEntryLoadButton[vsman][1] = 3;
                    flag_VsEntryLoadButton[vsman][0] = 1;
                } else {
                    flag_VsEntryLoadButton[vsman][1] = 2;
                    flag_VsEntryLoadButton[vsman][0] = 1;
                }
            }
            if ((sPad1->pressed_b != 0 && vsman == 0) || (sPad2->pressed_b != 0 && vsman == 1)) {
                if (menuvsmode[vsman] == vsman + 4) {
                    SeCancel();
                    menuvsmode[vsman] = (s32)vsman;
                    flag_menuvsenthuman[vsman] = 0;
                } else if (menuvsmode[vsman] == vsman + 6) {
                    SeCancel();
                    menuvsmode[vsman] = (s32)vsman;
                    flag_menuvsentzoid[vsman] = 0;
                }
            } else if ((sPad1->pressed_a != 0 && vsman == 0) || (sPad2->pressed_a != 0 && vsman == 1)) {
                switch (menuvsmode[vsman]) {
                case 0:
                case 1:
                    SeRet();
                    k = vsman;
                    n = vsman;
                    sel = menufarmcl[vsman];
                    if (sel == 0) {
                        menuvsmode[k] = k + 4;
                        flag_menuvsenthuman[k] = 1;
                    } else if (sel == 2) {
                        menuvsmode[k] = k + 6;
                        flag_menuvsentzoid[k] = 1;
                    } else if (sel == 1) {
                        menuvsmode[0] = 0;
                        flag_menuvsentzoid[0] = 0;
                        menuvsmode[1] = 1;
                        flag_menuvsentzoid[1] = 0;
                        flag_menuvsenthuman[0] = 0;
                        flag_menuvsenthuman[1] = 0;
                        menu_sDispVsEntry();
                        GameMode.country = 0;
                        GameMode.game_type = GAME_TYPE_VS;
                        GameMode.game_type = GAME_TYPE_BATTLE;
                        map = GameMode.map;
                        stage = GameMode.map_no;
                        if (ttlMemCardChkStartNew() == 0) {
                            OSReport(sLogNoSaveLoad);
                            menuvsmode[0] = 0;
                            flag_menuvsentzoid[0] = 0;
                            menuvsmode[1] = 1;
                            flag_menuvsentzoid[1] = 0;
                            flag_menuvsenthuman[0] = 0;
                            flag_menuvsenthuman[1] = 0;
                            vsman = 2;
                            GameMode.game_type = GAME_TYPE_VS;
                        } else {
                            menu_TITLE_dispVsEntry(0);
                            if (ttlMenuBatSaveLoad(0) != 0) {
                                GameMode.game_type = GAME_TYPE_VS;
                                OSReport(sLogSaveLoadEnd);
                                IveSave[k].owned_zoid_count = IveSave[2].owned_zoid_count;
                                for (j = 0; j < 30; j++)
                                    IveSave[k].owned_zoids[j] = IveSave[2].owned_zoids[j];
                                for (i = 0; i < 30; i++) {
                                    for (j = 0; j < 28; j++)
                                        IveSave[k].zoid_weapons[i][j] = IveSave[2].zoid_weapons[i][j];
                                    for (j = 0; j < 3; j++)
                                        IveSave[k].contract_subparts[i][j] = IveSave[2].contract_subparts[i][j];
                                    IveSave[k].contract_options[i] = IveSave[2].contract_options[i];
                                    IveSave[k].zoid_colors[i] = IveSave[2].zoid_colors[i];
                                }
                                IveSave[k].selected_zoid = IveSave[2].selected_zoid;
                                IveSave[k].selected_zoid_slot = IveSave[2].selected_zoid_slot;
                                IveSave[k].previous_zoid_slot = IveSave[2].previous_zoid_slot;
                                IveSave[k].partner_zoid = IveSave[2].partner_zoid;
                                IveSave[k].partner_zoid_slot = IveSave[2].partner_zoid_slot;
                                IveSave[k].previous_partner_zoid_slot = IveSave[2].previous_partner_zoid_slot;
                                IveSave[k].have_zoid_count = IveSave[2].have_zoid_count;
                                IveSave[k].have_zoid_count = IveSave[2].have_zoid_count;
                                IveSave[k].have_zoid_count = IveSave[2].have_zoid_count;
                                for (i = 0; i < 100; i++)
                                    IveSave[k].have_zoid[i] = IveSave[2].have_zoid[i];
                                for (i = 0; i < 100; i++)
                                    IveSave[k].have_zoid_flag[i] = IveSave[2].have_zoid_flag[i];
                                menufarmmh[k + 6] = 4;
                                menufarmmn[k + 6] = IveSave[k].owned_zoid_count;
                                if (IveSave[k].owned_zoid_count > menufarmmn[k + 6])
                                    menufarmmn[k + 6] = IveSave[k].owned_zoid_count;
                                if (IveSave[k].owned_zoid_count < menufarmmh[k + 6])
                                    menufarmmh[k + 6] = IveSave[k].owned_zoid_count;
                                for (i = 0; i < IveSave[2].person_list_count; i++)
                                    IveSave[k].person_list[i] = IveSave[2].person_list[i];
                                IveSave[k].person_list_count = IveSave[2].person_list_count;
                                menufarmmh[k + 4] = IveSave[2].person_list_count;
                                if (menufarmmh[k + 4] >= 4)
                                    menufarmmh[k + 4] = 4;
                                menufarmmn[k + 4] = IveSave[2].person_list_count;
                                menufarmsl[4] = 0;
                                menufarmcl[4] = 0;
                                menufarmst[4] = 0;
                                IveSave[k].selected_person = IveSave[k].person_list[0];
                                menufarmsl[5] = 0;
                                menufarmcl[5] = 0;
                                menufarmst[5] = 0;
                                IveSave[k].selected_person = IveSave[k].person_list[0];
                                GameMode.map = map;
                                GameMode.map_no = stage;
                                GameMode.game_type = GAME_TYPE_VS;
                                GameMode.win = 0;
                                sCamNN2 = 2;
                                sCamNN = 2;
                                menuSetTitle(1);
                                menuSetTitleButton(11);
                                GameMode.game_type = GAME_TYPE_VS;
                                menufarmcl[k + 6] = 0;
                                menufarmst[k + 6] = 0;
                                menufarmsl[k + 6] = 0;
                                IveSave[n].selected_zoid_slot = menufarmcl[k + 6];
                                IveSave[n].selected_zoid = IveSave[n].owned_zoids[IveSave[n].selected_zoid_slot];
                                flag_menuvsentzoid[0] = 0;
                                flag_menuvsentzoid[1] = 0;
                                menuvsmode[0] = 0;
                                menuvsmode[1] = 1;
                            } else {
                                GameMode.game_type = GAME_TYPE_VS;
                                menuSetTitle(1);
                                menuSetTitleButton(11);
                                menuvsmode[0] = 0;
                                menuvsmode[1] = 1;
                                sPad1->pressed_a = 0;
                                sPad2->pressed_a = 0;
                                GameMode.map = map;
                                GameMode.map_no = stage;
                                GameMode.game_type = GAME_TYPE_VS;
                                GameMode.game_type = GAME_TYPE_VS;
                                menuZoidBattleModeSingleTeam = 1;
                                break;
                            }
                            GameMode.game_type = GAME_TYPE_VS;
                            GameMode.game_type = GAME_TYPE_VS;
                            menuSetTitle(1);
                            menuSetTitleButton(11);
                        }
                    } else if (sel == 3) {
                        menuZoidBattleModeSingleTeam = 1;
                        menu_TITLE_dispVsEntry(0);
                        return 8;
                    }
                    break;
                case 2:
                    SeRet();
                    break;
                case 3:
                    break;
                case 4:
                    SeRet();
                    IveSave[vsman].selected_person = IveSave[vsman].person_list[menufarmcl[4]];
                    flag_menuvsenthuman[vsman] = 0;
                    menuvsmode[vsman] = 0;
                    TEA_VoiceOn(IveSave[vsman].selected_person, 1);
                    break;
                case 5:
                    SeRet();
                    IveSave[vsman].selected_person = IveSave[vsman].person_list[menufarmcl[5]];
                    flag_menuvsenthuman[vsman] = 0;
                    menuvsmode[vsman] = 1;
                    TEA_VoiceOn(IveSave[vsman].selected_person, 1);
                    break;
                case 6:
                    SeRet();
                    IveSave[vsman].selected_zoid_slot = menufarmcl[6];
                    IveSave[vsman].selected_zoid = IveSave[vsman].owned_zoids[IveSave[vsman].selected_zoid_slot];
                    flag_menuvsentzoid[vsman] = 0;
                    menuvsmode[vsman] = 0;
                    break;
                case 7:
                    SeRet();
                    IveSave[vsman].selected_zoid_slot = menufarmcl[7];
                    IveSave[vsman].selected_zoid = IveSave[vsman].owned_zoids[IveSave[vsman].selected_zoid_slot];
                    flag_menuvsentzoid[vsman] = 0;
                    menuvsmode[vsman] = 1;
                    break;
                }
            }
        }
        menu_sDispVsEntry();
    }
}
#pragma pop
#pragma readonly_strings off
#else
#pragma force_active on
static u32 pool_11802[8] = {
    0x80063838, 0x80063838, 0x80063ED8, 0x8006402C, 0x80063EE0, 0x80063F34,
    0x80063F8C, 0x80063FDC
};
#pragma force_active off
#endif
#pragma force_active on
static s32 VolSeTBL[11] = {
    0x00000000, 0x0000000C, 0x00000018, 0x00000024, 0x00000030, 0x0000003C,
    0x00000048, 0x00000054, 0x00000060, 0x0000006C, 0x00000078
};
static s32 VolBgmTBL[11] = {
    0x00000000, 0x0000000C, 0x00000018, 0x00000024, 0x00000030, 0x0000003C,
    0x00000048, 0x00000054, 0x00000060, 0x0000006C, 0x00000078
};
static s32 VolVoiceTBL[11] = {
    0x00000000, 0x0000000C, 0x00000018, 0x00000024, 0x00000030, 0x0000003C,
    0x00000048, 0x00000054, 0x00000060, 0x0000006C, 0x00000078
};
SampleVoice samplevoiceno[100] = {
    { 0, 0, 1 }, { 0, 0, 7 }, { 0, 0, 20 }, { 1, 0, 1 },
    { 1, 0, 6 }, { 1, 0, 7 }, { 2, 0, 1 }, { 2, 0, 51 },
    { 2, 0, 8 }, { 3, 0, 1 }, { 3, 0, 6 }, { 3, 0, 10 },
    { 4, 0, 1 }, { 4, 0, 6 }, { 4, 0, 8 }, { 5, 0, 1 },
    { 5, 0, 7 }, { 5, 0, 10 }, { 6, 0, 1 }, { 6, 0, 7 },
    { 6, 0, 26 }, { 7, 0, 1 }, { 7, 0, 6 }, { 7, 0, 7 },
    { 8, 0, 1 }, { 8, 0, 8 }, { 8, 0, 6 }, { 9, 0, 1 },
    { 9, 0, 6 }, { 9, 0, 9 }, { 10, 0, 1 }, { 10, 0, 8 },
    { 10, 0, 10 }, { 11, 0, 1 }, { 11, 0, 6 }, { 11, 0, 54 },
    { 12, 0, 1 }, { 12, 0, 11 }, { 12, 0, 5 }, { 13, 0, 1 },
    { 13, 0, 6 }, { 13, 0, 7 }, { 14, 0, 10 }, { 14, 0, 5 },
    { 14, 0, 6 }, { 15, 0, 50 }, { 15, 0, 51 }, { 15, 0, 52 },
    { 16, 0, 1 }, { 16, 0, 8 }, { 16, 0, 9 }, { 17, 0, 25 },
    { 17, 0, 6 }, { 17, 0, 8 }, { 18, 0, 1 }, { 18, 0, 6 },
    { 18, 0, 8 }, { 19, 0, 1 }, { 19, 0, 7 }, { 20, 0, 7 },
    { 20, 0, 27 }, { 21, 0, 9 }, { 21, 0, 7 }, { 22, 0, 1 },
    { 22, 0, 7 }, { 23, 0, 7 }, { 23, 0, 10 }, { 24, 0, 25 },
    { 25, 0, 25 }, { 25, 0, 7 }, { 26, 0, 50 }, { 26, 0, 49 },
    { 27, 0, 1 }, { 27, 0, 6 }, { 28, 0, 1 }, { 28, 0, 10 },
    { 29, 0, 8 }, { 29, 0, 25 }, { 30, 0, 3 }, { 30, 0, 9 },
    { 31, 0, 25 }, { 31, 0, 15 }, { 32, 0, 1 }, { 32, 0, 3 },
    { 33, 0, 1 }, { 33, 0, 8 }, { 34, 0, 1 }, { 34, 0, 8 },
    { 35, 0, 1 }, { 35, 0, 25 }, { 36, 0, 1 }, { 36, 0, 7 },
    { 37, 0, 7 }, { 37, 0, 54 }, { 38, 0, 7 }, { 38, 0, 16 },
    { 39, 0, 49 }, { 39, 0, 9 }, { 40, 0, 10 }, { 40, 0, 7 }
};
u32 VsTimeTBL[5] = {
    0x00000001, 0x00000003, 0x00000005, 0x0000000A, 0xFFFFFFFF
};
static u32 menuMax[7] = {
    0x00000002, 0x00000002, 0x00000001, 0x00000001, 0x00000001, 0x00000001,
    0x00000000
};
u32 voiceSn[100] = {
    0x00000004, 0x00000002, 0x00000026, 0x00000002, 0x00000024, 0x00000002,
    0x00000025, 0x00000002, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000005, 0x00000051, 0x0000005D, 0x0000003A,
    0x0000001F, 0x0000001D, 0x00000008, 0x00000011, 0x00000059, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000006, 0x0000003C,
    0x0000003C, 0x00000019, 0x0000003C, 0x0000000B, 0x0000003C, 0x00000001,
    0x0000003C, 0x00000042, 0x0000003C, 0x00000005, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000007, 0x00000031, 0x00000042, 0x00000004, 0x00000019, 0x00000060,
    0x00000020, 0x00000045, 0x0000003D, 0x0000005B, 0x00000052, 0x0000004F,
    0x0000002B, 0x0000001C, 0x00000015, 0x0000004A, 0x00000027, 0x00000003,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000009, 0x00000047, 0x0000002F, 0x00000055,
    0x00000037, 0x00000032, 0x0000002E, 0x00000022, 0x00000012, 0x00000001,
    0x0000002D, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};
static u32 pool_12383[8] = {
    0x80065C98, 0x80065CA0, 0x80065CA8, 0x80065CB0, 0x80065CB8, 0x80065CC0,
    0x80065CC8, 0x80065CD0
};
#pragma force_active off

#endif
#endif
