
// C. VOP
// ===============================================

// Operational Base
// -----------------------------------------------
#define GRF_BASE            0xFF000000

// GPIO iomux Function Select
// -----------------------------------------------
// GPIO 0
// - - - - - - - - - - - - - - - - - - - - - - - -
#define GRF_GPIO0A_IOMUX    (GRF_BASE + 0x00)
#define GRF_GPIO0B_IOMUX    (GRF_BASE + 0x08)
#define GRF_GPIO0C_IOMUX    (GRF_BASE + 0x10)
// GPIO 1
// - - - - - - - - - - - - - - - - - - - - - - - -
#define GRF_GPIO1A_IOMUX    (GRF_BASE + 0x20)
#define GRF_GPIO1B_IOMUX_L  (GRF_BASE + 0x28)
#define GRF_GPIO1B_IOMUX_H  (GRF_BASE + 0x2c)
#define GRF_GPIO1C_IOMUX_L  (GRF_BASE + 0x30)
#define GRF_GPIO1C_IOMUX_H  (GRF_BASE + 0x34)
#define GRF_GPIO1D_IOMUX    (GRF_BASE + 0x38)
// GRF_GPIO1C_IOMUX_H は 0b'0100'0100'0000 (UART2_TX_M0, UART2_RX_M0) でリセットされている。
// そのためこれを編集しないとGPIO1_C7,C6が使えない。write_enable ビットを忘れずに。

// GPIO Slew Rate Control
// -----------------------------------------------
#define GRF_GPIO1A_SR       (GRF_BASE + 0x0160)
#define GRF_GPIO1B_SR       (GRF_BASE + 0x0164)
#define GRF_GPIO1C_SR       (GRF_BASE + 0x0168)
#define GRF_GPIO1D_SR       (GRF_BASE + 0x016c)


//#define GRF_GPIO1C_P        0xFF0000b8
// プルアップは直さなくてもいけた。

// C.22 GPIO
// ===============================================
// [注意] Port A > GPIO > [0:3] > [A:D] ... GPIOのPortはすべてAで、その中にピンA~Dがある。

// Operational Base
// -----------------------------------------------
#define GPIO0_BASE          0xff220000
#define GPIO1_BASE          0xff230000
#define GPIO2_BASE          0xff240000
#define GPIO3_BASE          0xff250000
#define GPIO4_BASE          0xff260000

// DataRegister and DirectionRegister
// -----------------------------------------------
#define GPIO_SWPORTA_DR     0x0000      // Port A data register 
#define GPIO_SWPORTA_DDR    0x0004      // Port A data direction register

// GPIO 0
// -----------------------------------------------
#define GPIO0_DR            (GPIO0_BASE + GPIO_SWPORTA_DR)
#define GPIO0_DDR           (GPIO0_BASE + GPIO_SWPORTA_DDR)
// GPIO 1
// -----------------------------------------------
#define GPIO1_DR            (GPIO1_BASE + GPIO_SWPORTA_DR)
#define GPIO1_DDR           (GPIO1_BASE + GPIO_SWPORTA_DDR)
// GPIO 2
// -----------------------------------------------
#define GPIO2_DR            (GPIO2_BASE + GPIO_SWPORTA_DR)
#define GPIO2_DDR           (GPIO2_BASE + GPIO_SWPORTA_DDR)
// GPIO 3
// -----------------------------------------------
#define GPIO3_DR            (GPIO3_BASE + GPIO_SWPORTA_DR)
#define GPIO3_DDR           (GPIO3_BASE + GPIO_SWPORTA_DDR)
// GPIO4
// -----------------------------------------------
#define GPIO4_DR            (GPIO4_BASE + GPIO_SWPORTA_DR)
#define GPIO4_DDR           (GPIO4_BASE + GPIO_SWPORTA_DDR)


// TRMにあるものは原則そのままの名前にする。（_BASEは例外）

// C. VOP
// ===============================================

// Operational Base
// -----------------------------------------------
#define VOP_BASE            0xFF2E0000

#define VOP_LITE_REG_CFG_DONE       (VOP_BASE)
#define VOP_LITE_DSP_BG     (VOP_BASE + 0x0008)

// Axi Bus interface control register
#define VOP_LITE_SYS_CTRL0  (VOP_BASE + 0x0010)
#define VOP_LITE_SYS_CTRL1  (VOP_BASE + 0x0014)
#define VOP_LITE_SYS_CTRL2  (VOP_BASE + 0x0018)

#define VOP_LITE_DSP_CTRL0  (VOP_BASE + 0x0020)
#define VOP_LITE_DSP_CTRL1  (VOP_BASE + 0x0024)
#define VOP_LITE_DSP_CTRL2  (VOP_BASE + 0x0028)

#define VOP_LITE_DSP_HTOTAL_HS_END  (VOP_BASE + 0x0100)
#define VOP_LITE_DSP_HACT_ST_END    (VOP_BASE + 0x0104)
#define VOP_LITE_DSP_VTOTAL_VS_END  (VOP_BASE + 0x0108)
#define VOP_LITE_DSP_VACT_ST_END    (VOP_BASE + 0x010C)
#define VOP_LITE_DSP_VS_ST_END_F1   (VOP_BASE + 0x0110)
#define VOP_LITE_DSP_VACT_ST_END_F1 (VOP_BASE + 0x0114)

#define VOP_LITE_DBG_REG_SCAN_LINE  (VOP_BASE + 0x0190)

#define VOP_LITE_WIN0_YRGB_MST0     (VOP_BASE + 0x0060)

#define VOP_LITE_WIN1_CTRL0         (VOP_BASE + 0x0090)
#define VOP_LITE_WIN1_CTRL1         (VOP_BASE + 0x0094)
#define VOP_LITE_WIN1_VIR           (VOP_BASE + 0x0098)
#define VOP_LITE_WIN1_MST           (VOP_BASE + 0x00a0)
#define VOP_LITE_WIN1_DSP_INFO      (VOP_BASE + 0x00a4)

// CRU
// ===============================================

#define CRU_BASE            0xff500000

#define CRU_CLKSEL_CON8     (CRU_BASE + 0x0120)
#define CRU_CLKSEL_CON9     (CRU_BASE + 0x0124)

// Software SPI 
// ===============================================

#define SPI_MISO        6       // GPIO1_C6 ... JTAG TCK
#define SPI_MOSI        7       // GPIO1_C7 ... JTAG TMS
#define SPI_CLK         0       // GPIO1_D0
#define SPI_CSN         1       // GPIO1_D1


