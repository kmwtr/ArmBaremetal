/* start.s */

.section .start
.global _start
// -------------------------------
_start:
    
    .word   0x33334B52  // "RK33"
    B       init


// ここが .bin ではごっそり消えてしまうので、objcopyで予め作っといたバイナリと合体させる方式にする。

.section .init
// -------------------------------
init:
    
    // General purpose registers
    
    MOV     X0,  XZR
    MOV     X1,  XZR
    MOV     X2,  XZR
    MOV     X3,  XZR
    MOV     X4,  XZR
    MOV     X5,  XZR
    MOV     X6,  XZR
    MOV     X7,  XZR
    MOV     X8,  XZR
    MOV     X9,  XZR
    MOV     X10, XZR
    MOV     X11, XZR
    MOV     X12, XZR
    MOV     X13, XZR
    MOV     X14, XZR
    MOV     X15, XZR
    MOV     X16, XZR
    MOV     X17, XZR
    MOV     X18, XZR
    MOV     X19, XZR
    MOV     X20, XZR
    MOV     X21, XZR
    MOV     X22, XZR
    MOV     X23, XZR
    MOV     X24, XZR
    MOV     X25, XZR
    MOV     X26, XZR
    MOV     X27, XZR
    MOV     X28, XZR
    MOV     X29, XZR
    MOV     X30, XZR

    // NEON FP registers
    
    MSR     CPTR_EL3, XZR
    MSR     CPTR_EL2, XZR
    FMOV    D0, XZR
    FMOV    D1, XZR
    FMOV    D2, XZR
    FMOV    D3, XZR
    FMOV    D4, XZR
    FMOV    D5, XZR
    FMOV    D6, XZR
    FMOV    D7, XZR
    FMOV    D8, XZR
    FMOV    D9, XZR
    FMOV    D10, XZR
    FMOV    D11, XZR
    FMOV    D12, XZR
    FMOV    D13, XZR
    FMOV    D14, XZR
    FMOV    D15, XZR
    FMOV    D16, XZR
    FMOV    D17, XZR
    FMOV    D18, XZR
    FMOV    D19, XZR
    FMOV    D20, XZR
    FMOV    D21, XZR
    FMOV    D22, XZR
    FMOV    D23, XZR
    FMOV    D24, XZR
    FMOV    D25, XZR
    FMOV    D26, XZR
    FMOV    D27, XZR
    FMOV    D28, XZR
    FMOV    D29, XZR
    FMOV    D30, XZR
    FMOV    D31, XZR

    // Branch

    B       main

// メモ・命令
// --------------------
// LDR: メモリからレジスタに読み出し 
// STR: レジスタからメモリに読み出し 
// MOV: レジスタに格納されているデータを別のレジスタへコピーする命令
// MSR: 汎用レジスタの内容をPSRへ書き込む
// B:   プログラムカウンタの値にオフセットを加えたメモリアドレスに 分岐（ジャンプ）
// BL:  プログラムカウンタに4を加えた値(次の命令のアドレス)を、 汎用レジスタのX30 (リンクレジスタ) に設定した後に分岐（ジャンプ）
// RET: サブルーチンからの復帰

// メモ・レジスタ
// --------------------
// NZCV レジスタ (フラグレジスタ)
// 演算命令の結果の状態を保持するフラグ
