#include "msp430.h"
const unsigned char Group[4] = {0, 1, 2, 4}; //高/中/低/任意音
const unsigned char Scale[4][10] = {{250, 222, 198, 187, 176, 166, 148, 140, 132, 0},
                                    {124, 110, 98, 93, 88, 83, 73, 69, 65, 0},
                                    {62, 55, 49, 46, 43, 41, 36, 34, 32, 0},
                                    /*{30, 27, 24, 22, 21, 20, 18, 17, 16, 0},*/
                                    {0}};                                                                             //音阶
const unsigned long int Time[12] = {131072, 98304, 65536, 49152, 32768, 24576, 16384, 12288, 8192, 4096, 2048, 1024}; //时值  Crotchet=60
const unsigned char Key[7] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6};                                              //按键
//------------------------------------
#define Scale_1 BIT0    //K1
#define Canon_2 BIT1    //K2
#define Tsinghua_3 BIT2 //K3
#define Days_4 BIT3     //K4
//------------------------------------
#define Gp 0
#define Se 1
#define Te 2
//------------------------------------
#define Low 0
#define Medium 1
#define High 2
#define None 3
//------------------------------------
#define C 0
#define D 1
#define E 2
#define F 3
#define S_F 4
#define G 5
#define A 6
#define F_B 7
#define B 8
#define Pause 9
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
#define Scale_Num 22
const unsigned int Scale_Sheet[3][Scale_Num] = {{Low, Low, Low, Low, Low, Low, Low,
                                                 Medium, Medium, Medium, Medium, Medium, Medium, Medium,
                                                 High, High, High, High, High, High, High,
                                                 None},
                                                {C, D, E, F, G, A, B,
                                                 C, D, E, F, G, A, B,
                                                 C, D, E, F, G, A, B,
                                                 Pause},
                                                {Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet,
                                                 Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet,
                                                 Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet, Crotchet,
                                                 Crotchet}};
#define Canon_Num 391
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
//------------------------------------
int K = 1;
int I = 1;
int scale = 0;
int group = 0;
int mode = 0;
int note_Num = 0;
void Delay(unsigned long int time);
void Interval_G(int I);
void Scale_Play();
void Canon_Play();
void Tsinghua_Play();
void Days_Play();
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
    group = Medium;
    scale = C;
    K = 1;
    I = 1;
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
void Scale_Play()
{
    for (note_Num = 0; note_Num < Scale_Num; note_Num++)
    {
        TA1CCR0 = Scale[Scale_Sheet[Gp][note_Num]][Scale_Sheet[Se][note_Num]];
        Delay(Time[Scale_Sheet[Te][note_Num]]);
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void Canon_Play()
{
    for (note_Num = 0; note_Num < Canon_Num; note_Num++)
    {
        TA1CCR0 = Scale[Canon_Sheet[Gp][note_Num]][Canon_Sheet[Se][note_Num]];
        Delay(Time[Canon_Sheet[Te][note_Num]]);
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void Tsinghua_Play()
{
    for (note_Num = 0; note_Num < Tsinghua_Num; note_Num++)
    {
        TA1CCR0 = Scale[Tsinghua_Sheet[Gp][note_Num]][Tsinghua_Sheet[Se][note_Num]];
        Delay(Time[Tsinghua_Sheet[Te][note_Num]]);
        Interval_G(I);
    }
    TA1CCR0 = 0;
}
void Days_Play()
{
    for (note_Num = 0; note_Num < Days_Num; note_Num++)
    {
        TA1CCR0 = Scale[Days_Sheet[Gp][note_Num]][Days_Sheet[Se][note_Num]];
        Delay(Time[Days_Sheet[Te][note_Num]]);
        Interval_G(I);
    }
    TA1CCR0 = 0;
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
            group = Group[K];
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
                    scale = key_num;
                    TA1CCR0 = Scale[group][scale];
                    //TA1CCR1=0.05*Scale[group][scale];
                    Delay(Time[Crotchet]);
                    TA1CCR0 = 0;
                    //TA1CCR1=0;
                    P1IFG &= ~Key[scale];
                }
            }
        }
        P1IFG = 0;
    }
    else if (mode == Player)
    {
        P2OUT ^= PLAYING_LED;
        if ((P1IFG & Scale_1) != 0)
        {
            Scale_Play();
            P1IFG &= ~Scale_1;
        }
        if ((P1IFG & Canon_2) != 0)
        {
            Canon_Play();
            P1IFG &= ~Canon_2;
        }
        if ((P1IFG & Tsinghua_3) != 0)
        {
            Tsinghua_Play();
            P1IFG &= ~Tsinghua_3;
        }
        if ((P1IFG & Days_4) != 0)
        {
            Days_Play();
            P1IFG &= ~Days_4;
        }
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
            P1IFG &= !INTERVAL_SWITCH;
            P2OUT ^= SCALE_INTERVAL_LED;
            Delay(Time[Crotchet]);
            P2OUT ^= SCALE_INTERVAL_LED;
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
