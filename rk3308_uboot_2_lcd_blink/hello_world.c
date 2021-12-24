#include <common.h>
#include "RK3308_Register.h"
//#include "logo.c"

//#define LOW(addr, bit)   addr &= ~(1 << bit); // addr のビットのみをLowに
//#define HIGH(addr, bit)  addr |= (1 << bit);  // addr のビットのみをHighに

#define KILO    1000
#define MEGA    1000000

#define COMM    0
#define DATA    1

volatile unsigned int d;
volatile unsigned int flag;

void zatsuDelay(unsigned int num)
{
    for(d = 0; d < num; d++);
}

void sspi_monad(unsigned int num)
{
    unsigned int* GPIO_1_DAT = (unsigned int*)GPIO1_DR;

    // 雑ディレイは1000以下にすると通信に失敗する。

    // CLK Low
    *(unsigned int *)GPIO_1_DAT = 0b0;
    zatsuDelay(1000);

    if(num == 1){
        // MOSI High
        *(unsigned int *)GPIO_1_DAT = 0b00100000000000000000000000;
        zatsuDelay(1000);
        // CLK Low to High
        *(unsigned int *)GPIO_1_DAT = 0b01100000000000000000000000;
    }else{
        // MOSI Low
        *(unsigned int *)GPIO_1_DAT = 0b0;
        zatsuDelay(1000);
        // CLK Low to High
        *(unsigned int *)GPIO_1_DAT = 0b01000000000000000000000000;
    }
    zatsuDelay(1000);

    // CLK High to Low
    *(unsigned int *)GPIO_1_DAT = 0b0;
    zatsuDelay(1000);
}

void sspi_9bit(unsigned int mode, unsigned int hexnum)
{
    sspi_monad(mode);               // D/CX
    sspi_monad(hexnum >> 7);        // D7
    sspi_monad((hexnum >> 6) & 1);  // D6
    sspi_monad((hexnum >> 5) & 1);  // D5
    sspi_monad((hexnum >> 4) & 1);  // D4
    sspi_monad((hexnum >> 3) & 1);  // D3
    sspi_monad((hexnum >> 2) & 1);  // D2
    sspi_monad((hexnum >> 1) & 1);  // D1
    sspi_monad(hexnum & 1);         // D0
}

// =============================================================================

int hello_world (int argc, char * const argv[])
{
    // 0. GRF
    // -------------------------------------------------------------------------

    // iomux Function Select
    unsigned int*       GRF_GPIO_1A_IOMUX = (unsigned int*)GRF_GPIO1A_IOMUX;
    *(unsigned int *)   GRF_GPIO_1A_IOMUX = 0xFFFF5555; // LCD
    unsigned int*       GRF_GPIO_1B_IOMUX_L = (unsigned int*)GRF_GPIO1B_IOMUX_L;
    *(unsigned int *)   GRF_GPIO_1B_IOMUX_L = 0xFFFF1555; // LCD
    unsigned int*       GRF_GPIO_1B_IOMUX_H = (unsigned int*)GRF_GPIO1B_IOMUX_H;
    *(unsigned int *)   GRF_GPIO_1B_IOMUX_H = 0xFFFF0001; // LCD
    unsigned int*       GRF_GPIO_1C_IOMUX_L = (unsigned int*)GRF_GPIO1C_IOMUX_L;
    *(unsigned int *)   GRF_GPIO_1C_IOMUX_L = 0xFFFF1115; // LCD
    unsigned int*       GRF_GPIO_1C_IOMUX_H = (unsigned int*)GRF_GPIO1C_IOMUX_H;
    *(unsigned int *)   GRF_GPIO_1C_IOMUX_H = 0xFFFF0001; // LCD and GPIO

    // Slew Rate Control
    unsigned int*       GRF_GPIO_1A_SR = (unsigned int*)GRF_GPIO1A_SR;
    *(unsigned int *)   GRF_GPIO_1A_SR = 0xFF00FF;                      // HighSpeed
    unsigned int*       GRF_GPIO_1B_SR = (unsigned int*)GRF_GPIO1B_SR;
    *(unsigned int *)   GRF_GPIO_1B_SR = 0xFF00FF;                      // HighSpeed
    unsigned int*       GRF_GPIO_1C_SR = (unsigned int*)GRF_GPIO1C_SR;
    *(unsigned int *)   GRF_GPIO_1C_SR = 0xFF00FF;                      // HighSpeed
    unsigned int*       GRF_GPIO_1D_SR = (unsigned int*)GRF_GPIO1D_SR;
    *(unsigned int *)   GRF_GPIO_1D_SR = 0x030003;                      // HighSpeed

    // VoP
    // -------------------------------------------------------------------------
    
    // dclk_vop_frac_div_con
    unsigned int*       CRU_CLKSEL_CON_8 = (unsigned int*)CRU_CLKSEL_CON8;
    *(unsigned int *)   CRU_CLKSEL_CON_8 = 0xFFFF400F; // dclk_vop = pll_clk_src(15+1) ???
    unsigned int*       CRU_CLKSEL_CON_9 = (unsigned int*)CRU_CLKSEL_CON9;
    *(unsigned int *)   CRU_CLKSEL_CON_9 = 0x00010002; // 1/2 ?
    // ↑これだー

    // 1. VOP init
    // first
    unsigned int*       VOP_SYS_CTRL1 = (unsigned int*)VOP_LITE_SYS_CTRL1;
    *(unsigned int *)   VOP_SYS_CTRL1 = 0x1F1000; // AXI ???
    //unsigned int*       VOP_SYS_CTRL2 = (unsigned int*)VOP_LITE_SYS_CTRL2;
    //*(unsigned int *)   VOP_SYS_CTRL2 = 0x00; // ???

    // HP
    unsigned int*       VOP_DSP_HTOTAL_HS_END = (unsigned int*)VOP_LITE_DSP_HTOTAL_HS_END;
    *(unsigned int *)   VOP_DSP_HTOTAL_HS_END = 0x02800028; // h_total: 640, hs_end: 40
    unsigned int*       VOP_DSP_HACT_ST_END = (unsigned int*)VOP_LITE_DSP_HACT_ST_END;
    *(unsigned int *)   VOP_DSP_HACT_ST_END = 0x0050027E; // hact_st: 80, hact_end: 560
    // VP
    unsigned int*       VOP_DSP_VTOTAL_VS_END = (unsigned int*)VOP_LITE_DSP_VTOTAL_VS_END;
    *(unsigned int *)   VOP_DSP_VTOTAL_VS_END = 0x02800028; // v_total: , vs_end: 
    //*(unsigned int *)   VOP_DSP_VTOTAL_VS_END = 0x01FB0002; // v_total: 507, vs_end: 2
    //*(unsigned int *)   VOP_DSP_VTOTAL_VS_END = 0x01FE0003; // v_total: 510, vs_end: 3
    unsigned int*       VOP_DSP_VACT_ST_END = (unsigned int*)VOP_LITE_DSP_VACT_ST_END;
    *(unsigned int *)   VOP_DSP_VACT_ST_END = 0x0050027E; // vact_st: , vact_end: 
    //*(unsigned int *)   VOP_DSP_VACT_ST_END = 0x000F01EF; // vact_st: 15, vact_end: 495
    //*(unsigned int *)   VOP_DSP_VACT_ST_END = 0x001201F2; // vact_st: 18, vact_end: 498

    //unsigned int*       VOP_DBG_REG_SCAN_LINE = (unsigned int*)VOP_LITE_DBG_REG_SCAN_LINE;
    //*(unsigned int *)   VOP_DBG_REG_SCAN_LINE = 0x1FB; // 507

    // 2. Background Display
    unsigned int*       VOP_DSP_CTRL0 = (unsigned int*)VOP_LITE_DSP_CTRL0;
    *(unsigned int *)   VOP_DSP_CTRL0 = 0x00002001; // なんとなく???
    //unsigned int*       VOP_DSP_CTRL1 = (unsigned int*)VOP_LITE_DSP_CTRL1;
    //*(unsigned int *)   VOP_DSP_CTRL1 = 0x0001; // [31:0] Reserved
    unsigned int*       VOP_DSP_CTRL2 = (unsigned int*)VOP_LITE_DSP_CTRL2;
    *(unsigned int *)   VOP_DSP_CTRL2 = 0x00010040; // なんとなく???
    unsigned int*       VOP_DSP_BG = (unsigned int*)VOP_LITE_DSP_BG;
    *(unsigned int *)   VOP_DSP_BG = 0x00FFFFFF; // 白
    // Done!
    unsigned int*       VOP_REG_CFG_DONE = (unsigned int*)VOP_LITE_REG_CFG_DONE;
    *(unsigned int *)   VOP_REG_CFG_DONE = 0xFFFF0027; // なんとなく???

    // 1. Set GPIO direction
    // -------------------------------------------------------------------------

    // LED (GPIO0_A1) and LCD RESETSX (GPIO0_C4) ... OUT
    unsigned int*       GPIO_0_DIR = (unsigned int*)GPIO0_DDR;
    *(unsigned int *)   GPIO_0_DIR = 0x100002;      // 010000 00000000 00000010

    // GPIO1 ... MISO以外はOUT
    unsigned int*       GPIO_1_DIR = (unsigned int*)GPIO1_DDR;
    *(unsigned int *)   GPIO_1_DIR = 0x3800000;     // 11 10xxxxxx xxxxxxxx xxxxxxxx

    // 2. Set GPIO_0 level (ON!)
    // -------------------------------------------------------------------------

    // LED and LCD RESETSX High
    unsigned int*       GPIO_0_DAT = (unsigned int*)GPIO0_DR;
    *(unsigned int *)   GPIO_0_DAT = 0x00100002;
    
    // LCD HWReset
    zatsuDelay(1000);
    *(unsigned int *)   GPIO_0_DAT = 0x00000002;
    zatsuDelay(1000);
    *(unsigned int *)   GPIO_0_DAT = 0x00100002;
    zatsuDelay(1000); 

    // 3. Set GPIO_1 Software SPI
    // -------------------------------------------------------------------------

    // Panel Name : HSD4.0IPS(HSD040BPN1-A00)
    // Resulation : 480x480
    // Inversion  : 2dot
    // Porch      : vbp=15 , vfp=12
    // Line Time  : 32us
    // Frame Rate : 60hz

    // memo: 32us ... 31.25 kHz DOTCLK?（33usでは周波数のキリが悪いからか？）

    unsigned int*       GPIO_1_DAT = (unsigned int*)GPIO1_DR;

    // CSX Init (High to Low)
    *(unsigned int *)   GPIO_1_DAT = 0b10000000000000000000000000; // 10 00000000 00000000 00000000
    zatsuDelay(1000);
    *(unsigned int *)   GPIO_1_DAT = 0b0;
    zatsuDelay(1000);

    sspi_9bit(COMM, 0x01); // Software Reset
    sspi_9bit(COMM, 0x11); // Sleep Out

    //sspi_9bit(COMM, 0x3A); // COLMOD
    // param
    //sspi_9bit(DATA, 0x70); // 24bit color

    zatsuDelay(1000);

    // コマンドモード変更
    sspi_9bit(COMM, 0xFF); // CND2BKxSEL: Command2 BKx Selection
    sspi_9bit(DATA, 0x77); // Default
    sspi_9bit(DATA, 0x01); // Default
    sspi_9bit(DATA, 0x00); // Default
    sspi_9bit(DATA, 0x00); // Default
    sspi_9bit(DATA, 0x10); // Select BK0 | 0b00010000
    
    sspi_9bit(COMM, 0xC0); // LNESET: Display Line Setting
    sspi_9bit(DATA, 0x3B); // NL == (59+1) * 8 == 480px
    sspi_9bit(DATA, 0x00); // no extra line

    sspi_9bit(COMM, 0xC1); // PORCTRL: Porch Control
    sspi_9bit(DATA, 0x0F); // VBP: 15
    sspi_9bit(DATA, 0x0C); // VFP: 12
    //sspi_9bit(DATA, 0x0D); // VBP: 13 ... 15なのでは???
    //sspi_9bit(DATA, 0x02); // VFP: 2 ... 12なのでは???

    // SCNL == NL + VBP + VFP == 480 + 80 + 80 == 640

    sspi_9bit(COMM, 0xC2); // INVSET: Inversion selection & Frame Rate Control
    sspi_9bit(DATA, 0x21); // NLINV[2:0] 0x21 == 0b00100001, 2dot
    sspi_9bit(DATA, 0x08); // RTNI[4:0] 0x8 == 0b1000, PCLK == (8 * 16) + 512 == 640
    // RTNI: Minimum number of pclk in each line

    //sspi_9bit(COMM, 0xC3); // RGBCTRL
    //sspi_9bit(DATA, 0x00); // 
    //sspi_9bit(DATA, 0x08); // 
    //sspi_9bit(DATA, 0x08); // 

    sspi_9bit(COMM, 0xB0); // PVGAMCTRL: Positive Voltage Gamma Control
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x18);
    sspi_9bit(DATA, 0x0E);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x06);
    sspi_9bit(DATA, 0x07);
    sspi_9bit(DATA, 0x08);
    sspi_9bit(DATA, 0x07);
    sspi_9bit(DATA, 0x22);
    sspi_9bit(DATA, 0x04);
    sspi_9bit(DATA, 0x12);
    sspi_9bit(DATA, 0x0F);
    sspi_9bit(DATA, 0xAA);
    sspi_9bit(DATA, 0x31);
    sspi_9bit(DATA, 0x18);

    sspi_9bit(COMM, 0xB1); // NVGAMCTRL: Negative Voltage Gamma Control
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x19);
    sspi_9bit(DATA, 0x0E);
    sspi_9bit(DATA, 0x12);
    sspi_9bit(DATA, 0x07);
    sspi_9bit(DATA, 0x08);
    sspi_9bit(DATA, 0x08);
    sspi_9bit(DATA, 0x08);
    sspi_9bit(DATA, 0x22);
    sspi_9bit(DATA, 0x04);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0xA9);
    sspi_9bit(DATA, 0x32);
    sspi_9bit(DATA, 0x18);

    sspi_9bit(COMM, 0xFF); // CND2BKxSEL: Command2 BKx Selection
    sspi_9bit(DATA, 0x77);
    sspi_9bit(DATA, 0x01);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x11); // select BK

    sspi_9bit(COMM, 0xB0); // VRHS: Vop Amplitude setting
    sspi_9bit(DATA, 0x60);
        
    sspi_9bit(COMM, 0xB1); // VCOMS: VCOM amplitude setting
    sspi_9bit(DATA, 0x30);
        
    sspi_9bit(COMM, 0xB2); // VGHSS: VGH Voltage setting
    sspi_9bit(DATA, 0x87);
        
    sspi_9bit(COMM, 0xB3); // TESTCMD: TEST Command Setting
    sspi_9bit(DATA, 0x80);
        
    sspi_9bit(COMM, 0xB5); // VGLS: VGL Voltage setting
    sspi_9bit(DATA, 0x49);
        
    sspi_9bit(COMM, 0xB7); // PWCTRL1: Power Control 1
    sspi_9bit(DATA, 0x85);
        
    sspi_9bit(COMM, 0xB8); // PWCTRL2: Power Control 2
    sspi_9bit(DATA, 0x21);
        
    sspi_9bit(COMM, 0xC1); // SPD1: Source pre_drive timing set1
    sspi_9bit(DATA, 0x78);
        
    sspi_9bit(COMM, 0xC2); // SPD2: Source EQ2 Setting
    sspi_9bit(DATA, 0x78);

    zatsuDelay(1000);

    sspi_9bit(COMM, 0xE0); // SECTRL: Sunlight Readable Enhancement
    sspi_9bit(DATA, 0x00); // ???
    sspi_9bit(DATA, 0x1B); // ???
    sspi_9bit(DATA, 0x02); // ???

    sspi_9bit(COMM, 0xE1); // NRCTRL: Noise Reduce Control
    sspi_9bit(DATA, 0x08);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x07);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x44);
    sspi_9bit(DATA, 0x44);

    sspi_9bit(COMM, 0xE2); // SECTRL: Sharpness Control
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x44);
    sspi_9bit(DATA, 0x44);
    sspi_9bit(DATA, 0xED);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0xEC);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);

    sspi_9bit(COMM, 0xE3); // CCCTRL: Color Calibration Control
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x11);

    sspi_9bit(COMM, 0xE4); // SKCTRL: Skin Tone Preservation Control
    sspi_9bit(DATA, 0x44);
    sspi_9bit(DATA, 0x44);
    
    sspi_9bit(COMM, 0xE5); // ???? 無い
    sspi_9bit(DATA, 0x0A);
    sspi_9bit(DATA, 0xE9);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x0C);
    sspi_9bit(DATA, 0xEB);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x0E);
    sspi_9bit(DATA, 0xED);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x10);
    sspi_9bit(DATA, 0xEF);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);

    sspi_9bit(COMM, 0xE6); // ???? 無い
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x11);
    sspi_9bit(DATA, 0x11);

    sspi_9bit(COMM, 0xE7); // ???? 無い
    sspi_9bit(DATA, 0x44);
    sspi_9bit(DATA, 0x44);

    sspi_9bit(COMM, 0xE8); // ???? 無い
    sspi_9bit(DATA, 0x09);
    sspi_9bit(DATA, 0xE8);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x0B);
    sspi_9bit(DATA, 0xEA);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x0D);
    sspi_9bit(DATA, 0xEC);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);
    sspi_9bit(DATA, 0x0F);
    sspi_9bit(DATA, 0xEE);
    sspi_9bit(DATA, 0xD8);
    sspi_9bit(DATA, 0xA0);

    sspi_9bit(COMM, 0xEB); // ???? 無い
    sspi_9bit(DATA, 0x02);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0xE4);
    sspi_9bit(DATA, 0xE4);
    sspi_9bit(DATA, 0x88);
    sspi_9bit(DATA, 0x00);
    sspi_9bit(DATA, 0x40);

    sspi_9bit(COMM, 0xEC); // ???? 無い
    sspi_9bit(DATA, 0x3C);
    sspi_9bit(DATA, 0x00);

    sspi_9bit(COMM, 0xED); // ???? 無い
    sspi_9bit(DATA, 0xAB);
    sspi_9bit(DATA, 0x89);
    sspi_9bit(DATA, 0x76);
    sspi_9bit(DATA, 0x54);
    sspi_9bit(DATA, 0x02);
    sspi_9bit(DATA, 0xFF);
    sspi_9bit(DATA, 0xFF);
    sspi_9bit(DATA, 0xFF);
    sspi_9bit(DATA, 0xFF);
    sspi_9bit(DATA, 0xFF);
    sspi_9bit(DATA, 0xFF);
    sspi_9bit(DATA, 0x20);
    sspi_9bit(DATA, 0x45);
    sspi_9bit(DATA, 0x67);
    sspi_9bit(DATA, 0x98);
    sspi_9bit(DATA, 0xBA);

    // コマンドモード戻す
    sspi_9bit(COMM, 0xFF); // CND2BKxSEL: Command2 BKx Selection
    sspi_9bit(DATA, 0x77); // default
    sspi_9bit(DATA, 0x01); // default
    sspi_9bit(DATA, 0x00); // default
    sspi_9bit(DATA, 0x00); // default
    sspi_9bit(DATA, 0x00); // disable BKx

    // 12.2.24 Display On
    sspi_9bit(COMM, 0x29);

    zatsuDelay(1000);

    // 12.2.21 All Pixel ON
    //sspi_9bit(COMM, 0x23);
    
    flag = 0;

    while (1)
    {
        if((flag%2)==0){
            *(unsigned int *)GPIO_0_DAT = 0x100002;    // ON
        }else{
            *(unsigned int *)GPIO_0_DAT = 0x100000;    // OFF
        }
        
        if(flag==0){
            *(unsigned int *)   VOP_DSP_BG = 0x00FFFFFF; // White
        }else if(flag==1){
            *(unsigned int *)   VOP_DSP_BG = 0x000000FF; // R
        }else if(flag==2){
            *(unsigned int *)   VOP_DSP_BG = 0x0000FF00; // G
        }else if(flag==3){
            *(unsigned int *)   VOP_DSP_BG = 0x00FF0000; // B
        }else if(flag==4){
            *(unsigned int *)   VOP_DSP_BG = 0x0000FFFF; // Yellow
        }else if(flag==5){
            *(unsigned int *)   VOP_DSP_BG = 0x00FF00FF; // Magenta
        }else if(flag==6){
            *(unsigned int *)   VOP_DSP_BG = 0x00FFFF00; // Cyan
        }else if(flag==7){
            *(unsigned int *)   VOP_DSP_BG = 0x00000000; // Black
        }

        flag++;

        if(flag==8){
            flag = 0;
        }

        zatsuDelay(100*MEGA);
    }

    return (0);
}

// 12.2.21 All Pixel On
//sspi_9bit(COMM, 0x23); // 0b00100011
// 12.2.20 All Pixel Off
//sspi_9bit(COMM, 0x22); // 0b00100010

// 12.2.19 Display Inverse On
//sspi_9bit(COMM, 0x21);
// 12.2.18 Display Inverse Off
//sspi_9bit(COMM, 0x20);

// 12.2.24 Display OFF
//sspi_9bit(COMM, 0x28);
