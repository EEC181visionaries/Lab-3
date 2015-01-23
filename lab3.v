module lab3test(
CLOCK_50,
CLOCK2_50,
// SDRAM
DRAM_ADDR,
DRAM_BA,
DRAM_CAS_N,
DRAM_CKE,
DRAM_CLK,
DRAM_CS_N,
DRAM_DQ,
DRAM_LDQM,
DRAM_RAS_N,
DRAM_UDQM,
DRAM_WE_N,
// VGA
VGA_B,
VGA_BLANK_N,
VGA_CLK,
VGA_G,
VGA_HS,
VGA_R,
VGA_SYNC_N,
VGA_VS,
// DDR3 SDRAM
HPS_DDR3_ADDR,
HPS_DDR3_BA,
HPS_DDR3_CAS_N,
HPS_DDR3_CKE,
HPS_DDR3_CK_N,
HPS_DDR3_CK_P,
HPS_DDR3_CS_N,
HPS_DDR3_DM,
HPS_DDR3_DQ,
HPS_DDR3_DQS_N,
HPS_DDR3_DQS_P,
HPS_DDR3_ODT,
HPS_DDR3_RAS_N,
HPS_DDR3_RESET_N,
HPS_DDR3_RZQ,
HPS_DDR3_WE_N,
);
input CLOCK_50;
input CLOCK2_50;
// SDRAM
output [12: 0] DRAM_ADDR;
output [ 1: 0] DRAM_BA;
output DRAM_CAS_N;
output DRAM_CKE;
output DRAM_CLK;
output DRAM_CS_N;
inout DRAM_DQ;
output DRAM_LDQM;
output DRAM_RAS_N;
output DRAM_UDQM;
output DRAM_WE_N;
// VGA
output [ 7: 0] VGA_B;
output VGA_BLANK_N;
output VGA_CLK;
output [ 7: 0] VGA_G;
output VGA_HS;
output [ 7: 0] VGA_R;
output VGA_SYNC_N;
output VGA_VS;
// DDR3 SDRAM
output [14:0] HPS_DDR3_ADDR;
output [2:0] HPS_DDR3_BA;
output HPS_DDR3_CAS_N;
output HPS_DDR3_CKE;
output HPS_DDR3_CK_N;
output HPS_DDR3_CK_P;
output HPS_DDR3_CS_N;
output [3:0] HPS_DDR3_DM;
inout [31:0] HPS_DDR3_DQ;
inout [3:0] HPS_DDR3_DQS_N;
inout [3:0] HPS_DDR3_DQS_P;
output HPS_DDR3_ODT;
output HPS_DDR3_RAS_N;
output HPS_DDR3_RESET_N;
input HPS_DDR3_RZQ;
output HPS_DDR3_WE_N;
lab3system u0 (
.system_ref_clk_clk (CLOCK_50),
.system_ref_reset_reset (1'b0),
// VGA Subsystem
.vga_pll_ref_clk_clk (CLOCK2_50),
.vga_pll_ref_reset_reset (1'b0),
.vga_CLK (VGA_CLK),
.vga_BLANK (VGA_BLANK_N),
.vga_SYNC (VGA_SYNC_N),
.vga_HS (VGA_HS),
.vga_VS (VGA_VS),
.vga_R (VGA_R),
.vga_G (VGA_G),
.vga_B (VGA_B),
// DDR3 SDRAM
.memory_mem_a (HPS_DDR3_ADDR),
.memory_mem_ba (HPS_DDR3_BA),
.memory_mem_ck (HPS_DDR3_CK_P),
.memory_mem_ck_n (HPS_DDR3_CK_N),
.memory_mem_cke (HPS_DDR3_CKE),
.memory_mem_cs_n (HPS_DDR3_CS_N),
.memory_mem_ras_n (HPS_DDR3_RAS_N),
.memory_mem_cas_n (HPS_DDR3_CAS_N),
.memory_mem_we_n (HPS_DDR3_WE_N),
.memory_mem_reset_n (HPS_DDR3_RESET_N),
.memory_mem_dq (HPS_DDR3_DQ),
.memory_mem_dqs (HPS_DDR3_DQS_P),
.memory_mem_dqs_n (HPS_DDR3_DQS_N),
.memory_mem_odt (HPS_DDR3_ODT),
.memory_mem_dm (HPS_DDR3_DM),
.memory_oct_rzqin (HPS_DDR3_RZQ),
// SDRAM
.sdram_clk_clk (DRAM_CLK),
.sdram_addr (DRAM_ADDR),
.sdram_ba (DRAM_BA),
.sdram_cas_n (DRAM_CAS_N),
.sdram_cke (DRAM_CKE),
.sdram_cs_n (DRAM_CS_N),
.sdram_dq (DRAM_DQ),
.sdram_dqm ({DRAM_UDQM,DRAM_LDQM}),
.sdram_ras_n (DRAM_RAS_N),
);
endmodule
