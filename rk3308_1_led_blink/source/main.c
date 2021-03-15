// GPIO0_A1 でLチカしたい。

#define GPIO0 0xff220000
#define GPIO1 0xff230000
//#define GPIO2 0xff240000
//#define GPIO3 0xff250000
//#define GPIO4 0xff260000

// Chapter 22 GPIO
// =======================================

#define GPIO_SWPORTA_DR     0x0000 // Port A data register 
#define GPIO_SWPORTA_DDR    0x0004 // Port A data direction register 

/*
// Chapter 30 General Register Files (GRF)
// =======================================

// Base Address
// ---------------------------
#define GRF_BASE    0xff000000

// Offset
// ---------------------------
// GPIO0 iomux function select      // Reset Value
#define GRF_GPIO0A_IOMUX    0x0000  // 0x00000040 == 0x0100 0000 == SDMMC_DET
#define GRF_GPIO0B_IOMUX    0x0008  // 0x00000000
#define GRF_GPIO0C_IOMUX    0x0010  // 0x00000000

// GPIO0 driver disabled state control // Reset Value
#define GRF_GPIO0A_P        0x00a0  // 0x0000a96a
#define GRF_GPIO0B_P        0x00a4  // 0x0000a96a
#define GRF_GPIO0C_P        0x00a8  // 0x00000a2a

// GPIO0A output drive strength selection // Reset Value
#define GRF_GPIO0A_E        0x0100  // 0x00000000 == 2mA
#define GRF_GPIO0B_E        0x0104  // 0x00000000 == 2mA
#define GRF_GPIO0C_E        0x0108  // 0x00000000 == 2mA

// GPIO0A slew rate control 
#define GRF_GPIO0A_SR       0x0150  // 0x00000000 == Slow(half frequency) 
#define GRF_GPIO0B_SR       0x0154  // 0x00000000 == Slow(half frequency) 
#define GRF_GPIO0C_SR       0x0158  // 0x00000000 == Slow(half frequency) 

*/

__attribute__((section(".main")))
int main (void)
{
    // 1. Set GPIO direction (Output)
    unsigned int* GPIO0A_DIR = (unsigned int*)0xff220004;
    *(unsigned int *)GPIO0A_DIR = 0b10;

    // 2. Set GPIO level (ON!)
    unsigned int* GPIO0A_DAT = (unsigned int*)0xff220000;
    *(unsigned int *)GPIO0A_DAT = 0b10;

    // 3. Blink!
    volatile unsigned int i;
    while(1){
        for(i = 0; i < 1000000; i++);       // 無理やりDelay
        *(unsigned int *)GPIO0A_DAT = 0b10;     // ON
        for(i = 0; i < 1000000; i++);       // 無理やりDelay
        *(unsigned int *)GPIO0A_DAT = 0b00;     // OFF
    }

    return 0;
}
