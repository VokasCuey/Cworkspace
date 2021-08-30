//Composition List: {1:卡农, 2:清华校歌, 3:闪亮的日子, 4:千本樱, 5:One more time, one more chance}
#include "msp430.h"
const unsigned char Group[6] = {0, 1, 2, 3, 4, 5}; //极低/低/中/高/极高/任意音(播放器)
const unsigned char Scale[6][13] = {{249, 235, 222, 210, 198, 187, 176, 166, 157, 148, 140, 132, 0},
                                    {124, 117, 111, 104, 98, 93, 88, 83, 78, 73, 69, 65, 0},
                                    {62, 58, 55, 52, 49, 46, 43, 41, 38, 36, 34, 32, 0},
                                    {30, 29, 27, 25, 24, 22, 21, 20, 19, 18, 17, 16, 0},
                                    {15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0}};       //音阶(播放器)
const unsigned char Piano_Group[3] = {0, 1, 2}; //低/中/高/音(电子琴)
const unsigned char Piano_Scale[3][7] = {{124, 111, 98, 93, 83, 73, 65},
                                         {62, 55, 49, 46, 41, 36, 32},
                                         {30, 27, 24, 22, 20, 18, 16}};                                               //音阶(电子琴)
const unsigned long int Time[12] = {131072, 98304, 65536, 49152, 32768, 24576, 16384, 12288, 8192, 4096, 2048, 1024}; //时值  Crotchet=60
#define Standard_Speed 60                                                                                             //速度 标准速度 Crotchet=60
const unsigned char Key[7] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6};                                              //按键
//------------------------------------
#define Gp 0 //音高
#define Se 1 //音阶
#define Te 2 //时值
//------------------------------------
#define L_Low 0  //极低
#define Low 1    //低
#define Medium 2 //中
#define High 3   //高
#define H_High 4 //极高
#define None 5   //任意
//------------------------------------
#define C 0      //do
#define S_C 1    //升do
#define F_D 1    //降re
#define D 2      //re
#define S_D 3    //升re
#define F_E 3    //降mi
#define E 4      //mi
#define F 5      //fa
#define S_F 6    //升fa
#define F_G 6    //降so
#define G 7      //so
#define S_G 8    //升so
#define F_A 8    //降la
#define A 9      //la
#define S_A 10   //升la
#define F_B 10   //降si
#define B 11     //si
#define Pause 12 //休止
//------------------------------------
#define Semibreve 0           //全音符
#define D_Minim 1             //附点二分音符
#define Minim 2               //二分音符
#define D_Crotchet 3          //附点四分音符
#define Crotchet 4            //四分音符
#define D_Quaver 5            //附点八分音符
#define Quaver 6              //八分音符
#define D_Semiquaver 7        //附点十六分音符
#define Semiquaver 8          //十六分音符
#define demisemiquaver 9      //三十二分音符
#define hemidemisemiquaver 10 //六十四分音符
#define Interval 11           //音间隔
//------------------------------------//谱子
#define Composition_Num 5
#define Canon_Num 391
#define Canon_Speed 60
const unsigned int Canon_Sheet[3][Canon_Num] = {{High, High, High, Medium, Medium, Medium, Medium, Medium,
                                                 High, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                 High, Medium, High, Medium, Low, Medium, Medium, Medium, Medium, High, Medium, Medium, Medium, High, High, High, High, High, High, High, High, High, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                 Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Low, Medium, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                 Medium, High, High, High, High, High, High, High, High, High, High, High, High, High, High, High, Medium, Medium, Medium, High, High, High, High,
                                                 High, High, High, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, High, Medium, Medium, Medium, High, High, High, High, High,
                                                 High, High, High, High, High, High, High, Medium, High, High, High, High, High, Medium, High, Medium, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, High, Medium, High, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                 Medium, High, Medium, High, Medium, Medium, Medium, High, High, High, Medium, High, Medium, Medium, High, Medium, Medium, Medium, Medium, High, High, High, High, Medium, Medium, Medium, High, Low, Low, Low,
                                                 Low, Medium, Medium, Medium, Medium, Low, Low, Low, Low, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, High, High, High, Medium, Low, Medium, Low, Low, Medium, Medium, Medium, Medium, Low, Medium, Medium,
                                                 Medium, High, High, High, High, Medium, Medium, High, High, High, High, High, High, Medium, Medium, Medium, Medium, High, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, High, High, High, High, High, High, High, High, Medium,
                                                 Medium, Medium, Medium, Medium, Medium, High, High, High, High, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, High, High, High, High, High, High, High, High, High, High, Medium,
                                                 Medium, High, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                 High, Medium, Medium, Medium, Medium, Medium, Medium, High, Medium, Medium, High, Medium, Medium, High, High, High,
                                                 High, Medium, High, Medium, High, Medium, Low, Medium, Medium, Low, Low, Medium, Medium, High, High, Medium,
                                                 Medium, Medium, Medium, High, High, Medium, Medium, High, High, Medium, Low, Medium, Medium, High, High, Medium,
                                                 Medium, High, Medium, High, High, None, None},
                                                {E, D, C, B, A, G, A, B,
                                                 C, B, A, G, F, E, F, D,
                                                 C, B, C, C, B, G, D, E, C, C, B, A, B, E, G, A, F, E, D, F, F, E, C, B, A, G, F, E, D, F, E, D,
                                                 C, D, E, F, G, D, G, F, E, A, G, F, G, F, E, D, C, A, A, B, C, B, A, G, F, E, D, A, G, A, G, F,
                                                 E, E, D, C, D, C, E, D, F, G, E, F, G, E, F, G, G, A, B, C, D, E, F,
                                                 E, C, D, E, E, F, G, A, G, F, G, E, F, G, F, A, G, F, E, D, E, D, C, D, E, F, G, A, F, A, G, A, B, C, G, A, B, C, D, E, F, G,
                                                 E, C, D, E, D, C, D, B, C, D, E, D, C, B, C, A, B, C, C, D, E, F, E, D, E, C, B, C, A, C, B, A, G, F, G, F, E, F, G, A, B, C,
                                                 A, C, B, C, B, A, B, C, D, C, B, C, A, B, E, E, F, E, D, D, E, D, C, E, C, A, G, G, F, G,
                                                 A, A, B, A, B, G, F, G, A, A, G, A, B, B, A, B, C, C, D, C, B, B, C, B, A, A, G, A, B, B, E, D,
                                                 C, C, D, F, E, E, G, E, C, F, E, F, D, G, F, G, E, C, B, C, E, G, G, A, B, G, E, C, D, E, C, E, E, D, C, B,
                                                 A, A, G, A, B, C, E, D, C, E, F, C, B, A, A, G, D, G, G, E, E, E, F, E, D, C, C, C, D, C, B,
                                                 A, C, C, F_B, A, F_B, G, G, G, G, G, A, G, F, E, E, E, F, E, D,
                                                 C, F_B, A, F_B, G, G, F, C, B, B, G, G, F, E, E, D,
                                                 C, C, C, B, C, C, B, B, A, A, G, G, F, F, E, E,
                                                 D, A, D, D, E, E, D, D, C, C, B, B, A, A, G, G,
                                                 F, D, G, D, E, Pause, Pause},
                                                {Minim, Minim, Minim, Minim, Minim, Minim, Minim, Minim,
                                                 Minim, Minim, Minim, Minim, Minim, Minim, Minim, Minim,
                                                 Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                                 Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                                 Crotchet, Crotchet, Minim, Minim, Minim, Crotchet, Crotchet, Crotchet, Crotchet, Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                 Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                 Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                 Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                                 Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                                 Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Quaver, Quaver,
                                                 Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, D_Crotchet, Quaver, Quaver, Quaver, Quaver, Quaver, D_Crotchet, Quaver, Quaver, Quaver, Quaver, Quaver,
                                                 Minim, Minim, Quaver, Quaver, Quaver, Quaver, D_Crotchet, Quaver, D_Crotchet, Quaver, Quaver, Quaver, Quaver, Quaver, D_Crotchet, Quaver, Quaver, Quaver, Quaver, Quaver,
                                                 Quaver, Quaver, Quaver, Quaver, D_Crotchet, Quaver, Crotchet, Crotchet, D_Crotchet, Quaver, Minim, D_Crotchet, Quaver, Minim, D_Crotchet, Quaver,
                                                 D_Minim, Crotchet, Minim, Minim, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet,
                                                 Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet,
                                                 D_Crotchet, Quaver, Crotchet, Crotchet, Minim, Crotchet, Crotchet}};
#define Tsinghua_Num 97
#define Tsinghua_Speed 60
const unsigned int Tsinghua_Sheet[3][Tsinghua_Num] = {{Medium, Medium, Medium, Medium, Medium, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Low, Medium, Medium, Medium,
                                                       Medium, Medium, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, High, High, Medium, High, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                       Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                       High, High, None, Medium, Medium, None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                       High, High, None, Medium, Medium, None, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium},
                                                      {C, C, E, G, G, A, C, A, G, G, E, E, G, E, C, A, C, D, G,
                                                       A, A, A, C, G, E, D, E, D, C, D, G, G, S_F, G, A, A, B, A, G,
                                                       C, C, A, C, G, A, G, A, A, G, E, D, D, E, G,
                                                       C, C, C, E, D, E, D, C, A, A, G, E, D, E, D, C,
                                                       C, C, Pause, A, A, Pause, G, G, A, G, D, E, G,
                                                       C, C, Pause, A, A, Pause, G, G, A, G, D, E, D, C},
                                                      {Crotchet, Quaver, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Crotchet, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Crotchet, Crotchet, Quaver, Quaver, Minim,
                                                       Crotchet, Crotchet, Quaver, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Minim,
                                                       D_Crotchet, Quaver, Crotchet, Crotchet, D_Crotchet, Quaver, Minim, D_Crotchet, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Minim,
                                                       D_Crotchet, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Minim, D_Crotchet, Quaver, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Minim,
                                                       Crotchet, Minim, Crotchet, Crotchet, Minim, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Minim,
                                                       Crotchet, Minim, Crotchet, Crotchet, Minim, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Quaver, Quaver, Minim}};
#define Days_Num 136
#define Days_Speed 60
const unsigned int Days_Sheet[3][Days_Num] = {{Medium, Low, Medium, Medium, Medium, Low, Low, Medium, Medium, Low, Low, Medium, Low, Low,
                                               Medium, Low, Medium, Medium, Medium, Low, Low, Medium, Medium, Low, Low, Medium, Low, Low, Low,
                                               Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, None, Medium,
                                               Medium, Medium, Medium, Low, None, Low, Medium, Medium, Medium, Low, Low, Low,
                                               Medium, Medium, Medium, Medium, Medium, None, Medium, Medium, Medium, Medium, Medium, Medium, None, Medium,
                                               Medium, Medium, Medium, Low, None, Low, Low, Medium, Low, Low, Low, Low, Low,
                                               Medium, Medium, Medium, Medium, Medium, High, Low, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                               Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Low, Low,
                                               Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, None, Medium, Medium,
                                               Medium, Medium, Medium, Low, None, Low, Low, Medium, Low, Low, Medium, None, None},
                                              {E, A, C, E, D, G, B, D, C, A, B, C, B, A,
                                               E, A, C, E, D, G, B, D, C, A, B, C, B, E, E,
                                               E, D, C, D, E, A, E, D, C, D, E, Pause, C,
                                               D, D, E, A, Pause, A, C, C, D, B, E, E,
                                               E, D, C, D, E, Pause, A, E, D, C, D, E, Pause, C,
                                               D, D, E, A, Pause, G, A, C, B, A, A, E, E,
                                               A, G, F, G, A, C, B, A, A, G, A, A, E, E, C, C,
                                               D, D, E, D, C, D, E, E, F, E, E, E,
                                               E, D, C, D, E, A, E, D, C, D, E, Pause, C, C,
                                               D, D, E, A, Pause, A, A, C, B, A, A, Pause, Pause},
                                              {D_Minim, Crotchet, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Minim,
                                               D_Minim, Crotchet, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Crotchet,
                                               D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Minim, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Crotchet,
                                               Minim, D_Minim, Crotchet, Semibreve, Crotchet, Crotchet, Minim, D_Minim, Crotchet, Semibreve, Crotchet, Crotchet,
                                               D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Crotchet,
                                               Minim, D_Minim, Crotchet, Semibreve, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Crotchet,
                                               D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Minim, D_Minim, Crotchet, Crotchet, Quaver, Quaver, Crotchet, D_Minim, Crotchet, Quaver, Quaver,
                                               Minim, D_Minim, Crotchet, Semibreve, Crotchet, Crotchet, Minim, D_Minim, Crotchet, Semibreve, Crotchet, Crotchet,
                                               D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Minim, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Quaver, Quaver,
                                               Minim, D_Minim, Crotchet, Semibreve, Crotchet, Crotchet, D_Minim, Crotchet, Crotchet, Crotchet, Semibreve, Crotchet, Crotchet}};
#define Sakura_Num 372
#define Sakura_Speed 100
const unsigned int Sakura_Sheet[3][Sakura_Num] = {{Medium, Medium, Medium, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, Medium, High,
                                                   Medium, Medium, Medium, Medium, Medium, Medium,
                                                   Medium, High, High, High,

                                                   Medium, Medium, Low, Low, Low, Low, Medium, Medium, Low, Low, Low, Low,
                                                   Medium, Medium, Low, Low, Low, Low, Medium, Low, Low, Low,
                                                   Medium, Medium, Low, Low, Low, Low, Medium, Medium, Low, Low, Low, Low,
                                                   Medium, Medium, Medium, High, Medium, High, Medium, Medium, Medium, Medium,

                                                   Medium, Medium, Low, Low, Low, Low, Medium, Medium, Low, Low, Low, Low,
                                                   Medium, Medium, Low, Low, Low, Low, Medium, Low, Low, Low,
                                                   Medium, Low, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium, Low, Medium, Medium,
                                                   High, Medium, Medium, Medium, Medium, Medium, High,

                                                   High, High, Medium, Medium, Medium, Medium, High, High, Medium, Medium, Medium, Medium,
                                                   High, High, Medium, Medium, Medium, Medium, High, Medium, Medium, Medium,
                                                   High, High, Medium, Medium, Medium, Medium, High, High, Medium, Medium, Medium, Medium,
                                                   High, High, High, H_High, High, H_High, High, High, High, High,

                                                   High, High, Medium, Medium, Medium, Medium, High, High, Medium, Medium, Medium, Medium,
                                                   High, High, Medium, Medium, Medium, Medium, High, Medium, Medium, Medium,
                                                   High, High, High, High, High, High, High, High, Medium, High, High, High,
                                                   High, High, High, High,

                                                   Medium, Medium, Medium, Medium, High, High, High,
                                                   Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, Medium, High, High, High,
                                                   High, High, High, Medium,

                                                   Medium, Medium, Medium, Medium, High, High, High,
                                                   Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, Medium, Medium, High, High,
                                                   High, High, High, Medium,

                                                   High, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, High, Medium,
                                                   High, Medium, Medium, Medium,

                                                   High, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                   Medium, Medium, Medium, High, High,
                                                   Medium, Medium, High,

                                                   High, High, High, High, High,
                                                   High, High, High, High, High, Medium, High,
                                                   High, High, High, High, High, High,
                                                   High, High, High, High, High, Medium, High,

                                                   High, High, High, High, High,
                                                   High, High, High, High, High, Medium, High,
                                                   High, High, High, High,
                                                   High, High, Medium, Medium, Medium, Medium, High,

                                                   High, High, High, High, High,
                                                   High, High, High, High, High, Medium, High,
                                                   High, High, High, High, High, High,
                                                   High, High, High, High, High, Medium, High,

                                                   High, High, High, High, High,
                                                   High, High, High, High, High, Medium, High,
                                                   High, High, High, High,
                                                   High, High, High, High, High},
                                                  {A, A, G, A, A, G,
                                                   A, A, G, A, C,
                                                   A, A, G, A, A, G,
                                                   A, C, D, E,

                                                   D, E, A, G, A, G, D, E, A, G, A, G,
                                                   D, E, A, G, A, G, C, B, A, G,
                                                   D, E, A, G, A, G, D, E, A, G, A, G,
                                                   D, E, G, C, B, C, B, A, G, E,

                                                   D, E, A, G, A, G, D, E, A, G, A, G,
                                                   D, E, A, G, A, G, C, B, A, G,
                                                   C, A, C, D, C, D, E, D, E, G, C, E, G,
                                                   C, B, A, G, A, A, C,

                                                   D, E, A, G, A, G, D, E, A, G, A, G,
                                                   D, E, A, G, A, G, C, B, A, G,
                                                   D, E, A, G, A, G, D, E, A, G, A, G,
                                                   D, E, G, C, B, C, B, A, G, E,

                                                   D, E, A, G, A, G, D, E, A, G, A, G,
                                                   D, E, A, G, A, G, C, B, A, G,
                                                   E, D, E, G, A, G, E, D, A, C, E, G,
                                                   A, A, G, A,

                                                   A, A, G, A, C, D, E,
                                                   A, A, G, A, G, E, G,
                                                   A, A, G, A, C, D, E,
                                                   E, D, C, A,

                                                   A, A, G, A, C, D, E,
                                                   A, A, G, A, G, G, E,
                                                   A, A, G, G, A, C, D,
                                                   E, D, C, A,

                                                   C, B, A, G,
                                                   G, G, A, E, D, E,
                                                   E, G, A, D, B,
                                                   C, B, G, A,

                                                   C, B, A, G,
                                                   G, G, A, E, D, E, E, G,
                                                   A, A, A, C, D,
                                                   B, A, C,

                                                   D, D, E, E, E,
                                                   G, A, D, C, E, A, C,
                                                   D, D, E, E, E, E,
                                                   F, E, D, C, C, A, C,

                                                   D, D, E, E, E,
                                                   G, A, D, C, E, A, C,
                                                   F, E, D, C,
                                                   C, D, B, G, A, A, C,

                                                   D, D, E, E, E,
                                                   G, A, D, C, E, A, C,
                                                   D, D, E, E, E, E,
                                                   F, E, D, C, C, A, C,

                                                   D, D, E, E, E,
                                                   G, A, D, C, E, A, C,
                                                   F, E, D, C,
                                                   D, C, E, G, A},
                                                  {Quaver, Crotchet, Quaver, Quaver, Crotchet, Quaver,
                                                   Quaver, Crotchet, Quaver, Crotchet, Crotchet,
                                                   Quaver, Crotchet, Quaver, Quaver, Crotchet, Quaver,
                                                   Crotchet, Crotchet, Crotchet, Crotchet,

                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver,

                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,

                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver,

                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver,
                                                   Quaver, Quaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Quaver, Crotchet, Quaver, Minim,

                                                   Crotchet, D_Quaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Crotchet, D_Quaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Crotchet, D_Quaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Crotchet, Crotchet, Crotchet, Crotchet,

                                                   Crotchet, D_Quaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Crotchet, D_Quaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Crotchet, D_Quaver, Semiquaver, Quaver, Quaver, Quaver, Quaver,
                                                   Crotchet, Crotchet, Crotchet, Crotchet,

                                                   Crotchet, Crotchet, Crotchet, Crotchet,
                                                   Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Minim,
                                                   Quaver, Quaver, Crotchet, Crotchet, Crotchet,
                                                   Crotchet, Quaver, Quaver, Minim,

                                                   Crotchet, Crotchet, Crotchet, Crotchet,
                                                   Quaver, Semiquaver, Semiquaver, Quaver, Quaver, Crotchet, Quaver, Quaver,
                                                   Quaver, Crotchet, Quaver, Crotchet, Crotchet,
                                                   D_Minim, Quaver, Quaver,

                                                   Quaver, Crotchet, Quaver, D_Crotchet, Quaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,
                                                   Quaver, Crotchet, Quaver, Crotchet, Quaver, Quaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,

                                                   Quaver, Crotchet, Quaver, D_Crotchet, Quaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,
                                                   Crotchet, Crotchet, Crotchet, Crotchet,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,

                                                   Quaver, Crotchet, Quaver, D_Crotchet, Quaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,
                                                   Quaver, Crotchet, Quaver, Crotchet, Quaver, Quaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,

                                                   Quaver, Crotchet, Quaver, D_Crotchet, Quaver,
                                                   Quaver, Quaver, Quaver, Quaver, Crotchet, Quaver, Quaver,
                                                   Crotchet, Crotchet, Crotchet, Crotchet,
                                                   Quaver, Quaver, Quaver, Quaver, Minim}};
#define One_Num 211
#define One_Speed 60
const unsigned int One_Sheet[3][One_Num] = {{Low, Low, Medium, Low,
                                             Medium, Medium, Medium,
                                             Medium, Low, Medium,
                                             Medium,

                                             Low, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium,
                                             Low,
                                             Low,

                                             None, Low, Low, Medium, Medium, Medium,
                                             Medium, Medium, Low, Low,
                                             None, None, Low, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium, Medium,

                                             None, Low, Low, Medium, Medium, Medium,
                                             Medium, Medium, Low, Low,
                                             None, None, Low, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium, Medium,

                                             Medium, Medium, Medium,
                                             Medium, Medium, Medium,
                                             Medium, Medium, Low, Medium,
                                             Medium, Medium, Medium,

                                             Medium, Medium, Medium,
                                             Medium, Medium, Medium,
                                             Medium, Medium, Low, Medium,
                                             Medium, Medium, Medium,

                                             None, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Low, Low,
                                             None, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium, Medium, Medium,

                                             None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                             None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                             None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,

                                             None, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Low, Low,
                                             None, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium, Medium, Medium,

                                             None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                             None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                             None, Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                             Medium, Medium, Medium, Medium, Medium, Medium, Medium, Medium,

                                             Medium,
                                             Low, Low, Medium, Low,
                                             Medium, Medium, Medium,
                                             Medium, Low, Medium,

                                             Medium, Medium,
                                             Medium},
                                            {C, G, C, G,
                                             C, C, D,
                                             E, A, C,
                                             D,

                                             C, G, F, E,
                                             F, E, C, C,
                                             G,
                                             B,

                                             Pause, G, G, C, D, F,
                                             E, C, G, G,
                                             Pause, Pause, A, G, F, E, F,
                                             F, G, F, E, E,

                                             Pause, G, G, C, D, F,
                                             E, C, G, G,
                                             Pause, Pause, A, G, F, E, F,
                                             F, G, F, E, C,

                                             D, G, E,
                                             D, E, F,
                                             E, D, G, D,
                                             E, D, C,

                                             D, G, E,
                                             D, E, F,
                                             E, D, G, D,
                                             D, D, C,

                                             Pause, G, G, F, E,
                                             E, E, C, G, G,
                                             Pause, G, G, F, E,
                                             E, E, C, D, E, D,

                                             Pause, F, F, F, G, F, E, F,
                                             Pause, F, F, F, G, F, E, F,
                                             Pause, D, D, D, D, D, E, F,
                                             A, G, G, E, G, D, A, G,

                                             Pause, G, G, F, E,
                                             E, E, C, G, G,
                                             Pause, G, G, F, E,
                                             E, E, C, D, E, D,

                                             Pause, F, F, F, G, F, E, F,
                                             Pause, F, F, F, G, F, E, F,
                                             Pause, D, D, D, D, D, E, F,
                                             A, G, G, E, G, D, A, G,

                                             G,
                                             C, G, C, G,
                                             C, C, D,
                                             E, A, C,

                                             F, G,
                                             C},
                                            {Crotchet, Crotchet, Crotchet, Crotchet,
                                             Minim, Crotchet, Crotchet,
                                             Crotchet, Crotchet, Minim,
                                             Semibreve,

                                             Crotchet, Crotchet, Crotchet, Crotchet,
                                             Crotchet, Quaver, D_Crotchet, Crotchet,
                                             Semibreve,
                                             Semibreve,

                                             Crotchet, Quaver, Quaver, Crotchet, Quaver, D_Crotchet,
                                             Crotchet, Quaver, Quaver, Crotchet,
                                             Crotchet, Quaver, Quaver, Quaver, Quaver, Quaver, D_Crotchet,
                                             Quaver, Quaver, Quaver, Quaver, Crotchet,

                                             Crotchet, Quaver, Quaver, Crotchet, Quaver, D_Crotchet,
                                             Crotchet, Quaver, Quaver, Crotchet,
                                             Crotchet, Quaver, Quaver, Quaver, Quaver, Quaver, D_Crotchet,
                                             Quaver, Quaver, Quaver, Quaver, Crotchet,

                                             Minim, Crotchet, D_Minim,
                                             Quaver, Quaver, Crotchet,
                                             Crotchet, Crotchet, Crotchet, Crotchet,
                                             Crotchet, Crotchet, Minim,

                                             Minim, Crotchet, D_Minim,
                                             Quaver, Quaver, Crotchet,
                                             Crotchet, Crotchet, Crotchet, Crotchet,
                                             Crotchet, Crotchet, Minim,

                                             Crotchet, Quaver, Quaver, Quaver, D_Crotchet,
                                             Crotchet, Crotchet, Quaver, Quaver, Crotchet,
                                             Crotchet, Quaver, Quaver, Quaver, D_Crotchet,
                                             Crotchet, Crotchet, Quaver, Quaver, Quaver, Quaver,

                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,

                                             Crotchet, Quaver, Quaver, Quaver, D_Crotchet,
                                             Crotchet, Crotchet, Quaver, Quaver, Crotchet,
                                             Crotchet, Quaver, Quaver, Quaver, D_Crotchet,
                                             Crotchet, Crotchet, Quaver, Quaver, Quaver, Quaver,

                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,
                                             Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver, Quaver,

                                             Semibreve,
                                             Crotchet, Crotchet, Crotchet, Crotchet,
                                             Minim, Crotchet, Crotchet,
                                             Crotchet, Crotchet, Minim,

                                             Minim, Minim,
                                             Semibreve}};
//------------------------------------
#define Piano 0
#define Player 1
#define PLAYING_LED BIT4        //P2.4 PLAYING LED-L5
#define SCALE_INTERVAL_LED BIT5 //P2.5 SCALE/INTERVAL_SWITCH LED-L6
#define SCALE_SWITCH BIT7       //P1.7 K8 SCALE_SWITCH
#define MODE_SWITCH BIT0        //P2.0 Key MODE_SWITCH
#define BUZZ BIT1               //P2.1 BUZZ
#define PIANO_LED BIT2          //P2.2 PLAY_LED-L3
#define PLAYER_LED BIT3         //P2.3 PLAYER_LED-L4
#define INTERVAL_SWITCH BIT7    //P1.7 K8 INTERVAL SWITCH
#define BACK BIT0
#define NEXT BIT1
#define PLAY BIT2
//------------------------------------
int playing_num = 0;
int K = 1;
int I = 1;
int piano_scale = 0;
int piano_group = 0;
int mode = 0;
int note_Num = 0;
void Delay(unsigned long int time);
void Interval_G(int I);
void Canon_Play();
void Tsinghua_Play();
void Days_Play();
void Sakura_Play();
void One_Play();
typedef void (*Music_Play)();
Music_Play Play[Composition_Num] = {Canon_Play, Tsinghua_Play, Days_Play, Sakura_Play, One_Play};
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer
    P1SEL = 0X00;             //P1IN按键输入
    P1SEL2 = 0X00;
    P1DIR = 0X00;
    P1REN = 0XFF;
    P1OUT = 0XFF;
    P1IES = 0XFF;
    P1IFG = 0;
    P1IE = 0XFF;
    //------------------------------------
    P2SEL &= ~(PIANO_LED + PLAYER_LED); //P2.2 PIANO LED-L3, P2.3 PALYER LED-L4
    P2SEL2 &= ~(PIANO_LED + PLAYER_LED);
    P2DIR |= (PIANO_LED + PLAYER_LED);
    P2OUT |= PLAYER_LED; //Initialize
    P2OUT &= ~PIANO_LED;
    //------------------------------------
    P2SEL &= ~PLAYING_LED; //P2.4 PALYING LED-L5
    P2SEL2 &= ~PLAYING_LED;
    P2DIR |= PLAYING_LED;
    P2OUT |= PLAYING_LED; //Initialize
    //------------------------------------
    P2SEL &= ~SCALE_INTERVAL_LED; //P2.5 SCALE/INTERVAL LED-L6
    P2SEL2 &= ~SCALE_INTERVAL_LED;
    P2DIR |= SCALE_INTERVAL_LED;
    P2OUT &= ~SCALE_INTERVAL_LED; //Initialize
    //------------------------------------
    P2SEL &= ~MODE_SWITCH; //P2.0 MODE SWITCH
    P2SEL2 &= ~MODE_SWITCH;
    P2DIR &= ~MODE_SWITCH;
    P2IES |= MODE_SWITCH;
    P2IFG = 0;
    P2IE |= MODE_SWITCH;
    _EINT();
    //------------------------------------
    P2SEL |= BUZZ; //P2.1输出PWM
    P2SEL2 &= ~BUZZ;
    P2DIR |= BUZZ;
    TA1CTL |= TASSEL_1;
    TA1CTL |= (TACLR + MC_1);
    TA1CCTL1 |= OUTMOD1;
    TA1CCR1 = 1;
    //------------------------------------
    BCSCTL3 |= LFXT1S_0; //MCLK设置
    BCSCTL2 |= SELM_2;
    BCSCTL2 |= DIVM_0;
    //------------------------------------
    TA1CCR0 = 0; //Initialize
    //TA1CCR1=0;
    mode = Piano;
    piano_group = 1;
    piano_scale = 0;
    K = 1;
    I = 1;
    playing_num = 0;
    //------------------------------------
    while (1)
    {
    }; //main circulation
}
void Delay(unsigned long int time)
{
    for (; time > 0; time--)
        ;
}
void Interval_G(int I)
{
    if (I == 1)
    {
        TA1CCR0 = 0;
        Delay(Time[Interval]);
    }
}
void Canon_Play()
{
    for (note_Num = 0; note_Num < Canon_Num; note_Num++)
    {
        TA1CCR0 = Scale[Canon_Sheet[Gp][note_Num]][Canon_Sheet[Se][note_Num]];
        Delay((unsigned long int)(Time[Canon_Sheet[Te][note_Num]]) * ((float)(Standard_Speed) / (float)(Canon_Speed)));
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void Tsinghua_Play()
{
    for (note_Num = 0; note_Num < Tsinghua_Num; note_Num++)
    {
        TA1CCR0 = Scale[Tsinghua_Sheet[Gp][note_Num]][Tsinghua_Sheet[Se][note_Num]];
        Delay((unsigned long int)(Time[Tsinghua_Sheet[Te][note_Num]]) * ((float)(Standard_Speed) / (float)(Tsinghua_Speed)));
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void Days_Play()
{
    for (note_Num = 0; note_Num < Days_Num; note_Num++)
    {
        TA1CCR0 = Scale[Days_Sheet[Gp][note_Num]][Days_Sheet[Se][note_Num]];
        Delay((unsigned long int)(Time[Days_Sheet[Te][note_Num]]) * ((float)(Standard_Speed) / (float)(Days_Speed)));
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void Sakura_Play()
{
    for (note_Num = 0; note_Num < Sakura_Num; note_Num++)
    {
        TA1CCR0 = Scale[Sakura_Sheet[Gp][note_Num]][Sakura_Sheet[Se][note_Num]];
        Delay((unsigned long int)(Time[Sakura_Sheet[Te][note_Num]]) * ((float)(Standard_Speed) / (float)(Sakura_Speed)));
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void One_Play()
{
    for (note_Num = 0; note_Num < One_Num; note_Num++)
    {
        TA1CCR0 = Scale[One_Sheet[Gp][note_Num]][One_Sheet[Se][note_Num]];
        Delay((unsigned long int)(Time[One_Sheet[Te][note_Num]]) * ((float)(Standard_Speed) / (float)(One_Speed)));
        Interval_G(I);
    }
}
#pragma vector = PORT1_VECTOR
__interrupt void Key_Press(void)
{
    if (mode == Piano)
    {
        if ((P1IFG & SCALE_SWITCH) != 0)
        {
            K++;
            if (K == 3)
            {
                K = 0;
            }
            piano_group = Piano_Group[K];
            P2OUT ^= SCALE_INTERVAL_LED;
            Delay(Time[Crotchet]);
            P2OUT ^= SCALE_INTERVAL_LED;
        }
        else
        {
            int key_num = 0;
            for (key_num = 0; key_num < 7; key_num++)
            {
                if ((P1IFG & Key[key_num]) != 0)
                {
                    piano_scale = key_num;
                    TA1CCR0 = Piano_Scale[piano_group][piano_scale];
                    //TA1CCR1=0.05*Scale[group][scale];
                    Delay(Time[Crotchet]);
                    TA1CCR0 = 0;
                    //TA1CCR1=0;
                    P1IFG &= ~Key[piano_scale];
                }
            }
        }
        P1IFG = 0;
    }
    else if (mode == Player)
    {
        P2OUT ^= PLAYING_LED;
        if ((P1IFG & INTERVAL_SWITCH) != 0)
        {
            if (I == 1)
            {
                I = 0;
            }
            else if (I == 0)
            {
                I = 1;
            }
            P1IFG &= ~INTERVAL_SWITCH;
            P2OUT ^= SCALE_INTERVAL_LED;
            Delay(Time[Crotchet]);
            P2OUT ^= SCALE_INTERVAL_LED;
        }
        else if ((P1IFG & BACK) != 0)
        {
            if (playing_num == 0)
            {
                playing_num = Composition_Num - 1;
            }
            else
            {
                playing_num--;
            }
            P1IFG &= ~BACK;
        }
        else if ((P1IFG & NEXT) != 0)
        {
            if (playing_num == Composition_Num - 1)
            {
                playing_num = 0;
            }
            else
            {
                playing_num++;
            }
            P1IFG &= ~NEXT;
        }
        else if ((P1IFG & PLAY) != 0)
        {
            (*Play[playing_num])();
            P1IFG &= ~PLAY;
        }
        Delay(Time[Crotchet]);
        P2OUT ^= PLAYING_LED;
        P1IFG = 0;
    }
}
#pragma vector = PORT2_VECTOR
__interrupt void Mode_Switch(void)
{
    if ((P2IFG & MODE_SWITCH) != 0)
    {
        if (mode == Piano)
        {
            mode = Player;
        }
        else if (mode == Player)
        {
            mode = Piano;
        }
        P2OUT ^= (PIANO_LED + PLAYER_LED);
        P2IFG &= ~MODE_SWITCH;
    }
    P2IFG = 0;
    Delay(Time[Crotchet]);
}
