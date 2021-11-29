#include <common.h>
#include <exports.h>

// Operational Base
// =======================================
#define GPIO0   0xff220000
#define GPIO1   0xff230000
#define GPIO2   0xff240000
#define GPIO3   0xff250000
#define GPIO4   0xff260000

// Chapter 22 GPIO
// =======================================
#define GPIO_SWPORTA_DR     0x0000      // Port A data register 
#define GPIO_SWPORTA_DDR    0x0004      // Port A data direction register
// Port A > GPIO > [0:3] > [A:D] という階層。GPIOのPortはすべてAで、その中にピンA~Dがある。

// Software SPI 作るぞ～
// =======================================
// 雑Delay用
#define Kiro    1000
#define Mega    1000000

#define SPI_MISO        6       // GPIO1_C6 ... JTAG TCK
#define SPI_MOSI        7       // GPIO1_C7 ... JTAG TMS
#define SPI_CLK         0       // GPIO1_D0
#define SPI_CSN         1       // GPIO1_D1

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

    // 1. Set GPIO direction (Output)
    unsigned int* GPIO0A_DIR = (unsigned int*)0xff220004;
    *(unsigned int *)GPIO0A_DIR = 0b10;

    // 2. Set GPIO level (ON!)
    unsigned int* GPIO0A_DAT = (unsigned int*)0xff220000;
    *(unsigned int *)GPIO0A_DAT = 0b10;

    // 3. Blink!
    volatile unsigned int d;

    printf ("Hit any key to exit ... ");
    while (!tstc())
    {
        for(d = 0; d < (102*Mega); d++);       // 無理やりDelay
        *(unsigned int *)GPIO0A_DAT = 0b10;     // ON
        for(d = 0; d < (102*Mega); d++);       // 無理やりDelay
        *(unsigned int *)GPIO0A_DAT = 0b00;     // OFF
    }
    
    /* consume input */
    (void) getc();

    printf ("\n\n");
    return (0);
}