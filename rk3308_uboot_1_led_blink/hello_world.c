#include <common.h>
#include <exports.h>

// Chapter 30 General Register Files (GRF)
// =======================================
// Operational Base
#define GRF_BASE    0xFF000000
// GRF_GPIO1C_IOMUX_H は 0b'0100'0100'0000 (UART2_TX_M0, UART2_RX_M0) でリセットされている。
// そのためこれを編集しないとGPIO1_C7,C6が使えない。
#define GRF_GPIO1C_IOMUX_L  0xFF000030
#define GRF_GPIO1C_IOMUX_H  0xFF000034
// プルアップは直さなくてもいけた。
//#define GRF_GPIO1C_P        0xFF0000b8

// Operational Base
// =======================================
#define GPIO0_BASE  0xff220000
#define GPIO1_BASE  0xff230000
#define GPIO2_BASE  0xff240000
#define GPIO3_BASE  0xff250000
#define GPIO4_BASE  0xff260000

// Chapter 22 GPIO
// =======================================
#define GPIO_SWPORTA_DR     0x0000      // Port A data register 
#define GPIO_SWPORTA_DDR    0x0004      // Port A data direction register
// [注意] Port A > GPIO > [0:3] > [A:D] ... GPIOのPortはすべてAで、その中にピンA~Dがある。

// これでいいんだっけ
#define GPIO0_DR    0xff220000
#define GPIO0_DDR   0xff220004

#define GPIO1_DR    0xff230000
#define GPIO1_DDR   0xff230004

// Software SPI 作るぞ～
// =======================================

#define SPI_MISO        6       // GPIO1_C6 ... JTAG TCK
#define SPI_MOSI        7       // GPIO1_C7 ... JTAG TMS
#define SPI_CLK         0       // GPIO1_D0
#define SPI_CSN         1       // GPIO1_D1

// 雑Delay用
#define Kilo    1000
#define Mega    1000000

int hello_world (int argc, char * const argv[])
{
    int i;

    /* Print the ABI version */
    app_startup(argv);
    printf ("Example expects ABI version %d\n", XF_VERSION);
    printf ("Actual U-Boot ABI version %d\n", (int)get_version());
    printf ("Hello World\n");
    printf ("argc = %d\n", argc);

    for (i=0; i<=argc; ++i) {
        printf ("argv[%d] = \"%s\"\n", i, argv[i] ? argv[i] : "<NULL>");
    }

    // -----------------------------------

    // 0. GRF Settings
    unsigned int* GPIO1_C_IOMUX_H = (unsigned int*)GRF_GPIO1C_IOMUX_H;
    *(unsigned int *)GPIO1_C_IOMUX_H =  0b11111111111111110000000000000000; // [31:16] write_enable ビットを忘れずに。
    //unsigned int* GPIO1_C_STATE = (unsigned int*)GRF_GPIO1C_P;
    //*(unsigned int *)GPIO1_C_STATE =    0b11111111111111110000000000000000; 

    // 1. Set GPIO direction (Output)
    // LED
    unsigned int* GPIO0_A_DIR = (unsigned int*)GPIO0_DDR;
    *(unsigned int *)GPIO0_A_DIR = 0b10;

    // テスト Software SPI 予定ピン
    unsigned int* GPIO1_C_DIR = (unsigned int*)GPIO1_DDR;
    *(unsigned int *)GPIO1_C_DIR = 0b11110000000000000000000000; // 0b 11 10000000 00000000 00000000

    // 2. Set GPIO level (ON!)
    // LED
    unsigned int* GPIO0_A_DAT = (unsigned int*)GPIO0_DR;
    *(unsigned int *)GPIO0_A_DAT = 0b10;

    // テスト Software SPI 予定ピン
    unsigned int* GPIO1_C_DAT = (unsigned int*)GPIO1_DR;
    *(unsigned int *)GPIO1_C_DAT = 0b11110000000000000000000000;

    // 3. Blink!
    volatile unsigned int d;

    printf ("Hit any key to exit ... ");

    while (!tstc())
    {
        for(d = 0; d < (102*Mega); d++);       // 無理やりDelay
        *(unsigned int *)GPIO0_A_DAT = 0b10;     // ON
        *(unsigned int *)GPIO1_C_DAT = 0b11110000000000000000000000;     // ON
        for(d = 0; d < (102*Mega); d++);       // 無理やりDelay
        *(unsigned int *)GPIO0_A_DAT = 0b00;     // OFF
        *(unsigned int *)GPIO1_C_DAT = 0b00000000000000000000000000;     // OFF
    }
    
    /* consume input */
    (void) getc();

    printf ("\n\n");
    return (0);
}