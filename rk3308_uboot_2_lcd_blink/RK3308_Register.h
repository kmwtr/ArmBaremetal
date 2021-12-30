// RK3308 Registers

//
// TRM1 | C.02 | CRU
// ===================================================================

// Operational Base
// -------------------------------------------------------------------
#define CRU_BASE            0xff500000

// Internal clock select and divide register
// -------------------------------------------------------------------
#define CRU_CLKSEL_CON0_S   (CRU_BASE + 0x00F8)
#define CRU_CLKSEL_CON0     (CRU_BASE + 0x0100)
#define CRU_CLKSEL_CON1     (CRU_BASE + 0x0104)
#define CRU_CLKSEL_CON2     (CRU_BASE + 0x0108)
#define CRU_CLKSEL_CON3     (CRU_BASE + 0x010c)
#define CRU_CLKSEL_CON4     (CRU_BASE + 0x0110)
#define CRU_CLKSEL_CON5     (CRU_BASE + 0x0114)
#define CRU_CLKSEL_CON6     (CRU_BASE + 0x0118)
#define CRU_CLKSEL_CON7     (CRU_BASE + 0x011c)
#define CRU_CLKSEL_CON8     (CRU_BASE + 0x0120)
#define CRU_CLKSEL_CON9     (CRU_BASE + 0x0124)

//
// TRM1 |C.22 | GPIO
// ===================================================================
// [注意] Port A > GPIO > [0:3] > [A:D] ... GPIOのPortはすべてAで、その中にピンA~Dがある。

// Operational Base
// -------------------------------------------------------------------
#define GPIO0_BASE          0xff220000
#define GPIO1_BASE          0xff230000
#define GPIO2_BASE          0xff240000
#define GPIO3_BASE          0xff250000
#define GPIO4_BASE          0xff260000

// DataRegister and DirectionRegister
// -------------------------------------------------------------------
#define GPIO_SWPORTA_DR     0x0000      // Port A data register 
#define GPIO_SWPORTA_DDR    0x0004      // Port A data direction register
// GPIO 0
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GPIO0_DR            (GPIO0_BASE + GPIO_SWPORTA_DR)
#define GPIO0_DDR           (GPIO0_BASE + GPIO_SWPORTA_DDR)
// GPIO 1
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GPIO1_DR            (GPIO1_BASE + GPIO_SWPORTA_DR)
#define GPIO1_DDR           (GPIO1_BASE + GPIO_SWPORTA_DDR)
// GPIO 2
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GPIO2_DR            (GPIO2_BASE + GPIO_SWPORTA_DR)
#define GPIO2_DDR           (GPIO2_BASE + GPIO_SWPORTA_DDR)
// GPIO 3
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GPIO3_DR            (GPIO3_BASE + GPIO_SWPORTA_DR)
#define GPIO3_DDR           (GPIO3_BASE + GPIO_SWPORTA_DDR)
// GPIO4
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GPIO4_DR            (GPIO4_BASE + GPIO_SWPORTA_DR)
#define GPIO4_DDR           (GPIO4_BASE + GPIO_SWPORTA_DDR)


// TRM1 | C.30 | General Register Files (GRF)
// ===================================================================

// Operational Base
// -------------------------------------------------------------------
#define GRF_BASE            0xFF000000

// GPIO iomux Function Select
// -------------------------------------------------------------------
// GPIO 0
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GRF_GPIO0A_IOMUX    (GRF_BASE + 0x00)
#define GRF_GPIO0B_IOMUX    (GRF_BASE + 0x08)
#define GRF_GPIO0C_IOMUX    (GRF_BASE + 0x10)
// GPIO 1
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define GRF_GPIO1A_IOMUX    (GRF_BASE + 0x20)
#define GRF_GPIO1B_IOMUX_L  (GRF_BASE + 0x28)
#define GRF_GPIO1B_IOMUX_H  (GRF_BASE + 0x2c)
#define GRF_GPIO1C_IOMUX_L  (GRF_BASE + 0x30)
#define GRF_GPIO1C_IOMUX_H  (GRF_BASE + 0x34)
#define GRF_GPIO1D_IOMUX    (GRF_BASE + 0x38)
// GRF_GPIO1C_IOMUX_H は 0b'0100'0100'0000 (UART2_TX_M0, UART2_RX_M0) でリセットされている。
// そのためこれを編集しないとGPIO1_C7,C6が使えない。write_enable ビットを忘れずに。

// GPIO Slew Rate Control
// -------------------------------------------------------------------
#define GRF_GPIO1A_SR       (GRF_BASE + 0x0160)
#define GRF_GPIO1B_SR       (GRF_BASE + 0x0164)
#define GRF_GPIO1C_SR       (GRF_BASE + 0x0168)
#define GRF_GPIO1D_SR       (GRF_BASE + 0x016c)

// GPIO Driver disabled state control
// -------------------------------------------------------------------
//#define GRF_GPIO1C_P        0xFF0000b8
// プルアップは直さなくてもいけた。



// TRM2 | C.07 | Video Output Processor (VOP)
// ===================================================================

// Operational Base
// -------------------------------------------------------------------
#define VOP_BASE                    0xFF2E0000

// Registers
// -------------------------------------------------------------------
#define VOP_LITE_REG_CFG_DONE       (VOP_BASE)         

#define VOP_LITE_VERSION            (VOP_BASE + 0x0004)
#define VOP_LITE_DSP_BG             (VOP_BASE + 0x0008)
#define VOP_LITE_MCU                (VOP_BASE + 0x000c)
#define VOP_LITE_SYS_CTRL0          (VOP_BASE + 0x0010)
#define VOP_LITE_SYS_CTRL1          (VOP_BASE + 0x0014)
#define VOP_LITE_SYS_CTRL2          (VOP_BASE + 0x0018)
#define VOP_LITE_DSP_CTRL0          (VOP_BASE + 0x0020)
#define VOP_LITE_DSP_CTRL1          (VOP_BASE + 0x0024)
#define VOP_LITE_DSP_CTRL2          (VOP_BASE + 0x0028)

#define VOP_LITE_WIN0_CTRL0         (VOP_BASE + 0x0050)
#define VOP_LITE_WIN0_CTRL1         (VOP_BASE + 0x0054)
#define VOP_LITE_WIN0_COLOR_KEY     (VOP_BASE + 0x0058)
#define VOP_LITE_WIN0_VIR           (VOP_BASE + 0x005c)
#define VOP_LITE_WIN0_YRGB_MST0     (VOP_BASE + 0x0060)
#define VOP_LITE_WIN0_CBR_MST0      (VOP_BASE + 0x0064)
#define VOP_LITE_WIN0_ACT_INFO      (VOP_BASE + 0x0068)
#define VOP_LITE_WIN0_DSP_INFO      (VOP_BASE + 0x006c)
#define VOP_LITE_WIN0_DSP_ST        (VOP_BASE + 0x0070)
#define VOP_LITE_WIN0_SCL_FACTOR_YRGB   (VOP_BASE + 0x0074)
#define VOP_LITE_WIN0_SCL_FACTOR_CBR    (VOP_BASE + 0x0078)


#define VOP_LITE_WIN1_CTRL0         (VOP_BASE + 0x0090)
#define VOP_LITE_WIN1_CTRL1         (VOP_BASE + 0x0094)
#define VOP_LITE_WIN1_VIR           (VOP_BASE + 0x0098)
#define VOP_LITE_WIN1_MST           (VOP_BASE + 0x00a0)
#define VOP_LITE_WIN1_DSP_INFO      (VOP_BASE + 0x00a4)
#define VOP_LITE_WIN1_DSP_ST        (VOP_BASE + 0x00a8)
#define VOP_LITE_WIN1_COLOR_KEY     (VOP_BASE + 0x00ac)
#define VOP_LITE_WIN1_ALPHA_CTRL    (VOP_BASE + 0x00bc)

#define VOP_LITE_DSP_HTOTAL_HS_END  (VOP_BASE + 0x0100)
#define VOP_LITE_DSP_HACT_ST_END    (VOP_BASE + 0x0104)
#define VOP_LITE_DSP_VTOTAL_VS_END  (VOP_BASE + 0x0108)
#define VOP_LITE_DSP_VACT_ST_END    (VOP_BASE + 0x010C)
#define VOP_LITE_DSP_VS_ST_END_F1   (VOP_BASE + 0x0110)
#define VOP_LITE_DSP_VACT_ST_END_F1 (VOP_BASE + 0x0114)

#define VOP_LITE_BCSH_CTRL          (VOP_BASE + 0x0160)

#define VOP_LITE_DBG_REG_SCAN_LINE  (VOP_BASE + 0x0190)
