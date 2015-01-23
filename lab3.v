module lab3test(
	CLOCK_50,
	CLOCK2_50,

	//SDRAM
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

	//VGA
	VGA_B,
	VGA_BLANK_N,
	VGA_CLK,
	VGA_G,
	VGA_HS,
	VGA_R,
	VGA_SYNC_N,
	VGA_VS,

	//DDR3 SDRAM
	HPS_DDR3_ADDR,
	HPS_DDR3_BA,
	HPS_DDR3_CAS_N,
	HPS_DDR3_CKE,
	HPS_DDR3_CK_N,
	HPS_DDR3_CK_p,
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

input	CLOCK_50;
input	CLOCK2_50;

//SDRAM
output	[12:0]	DRAM_ADDR,
output	[1:0]	DRAM_BA,
output		DRAM_CAS_N,
output		DRAM_CKE,
output		DRAM_CLK,
output		DRAM_CS_N,
inout		DRAM_DQ,
output		DRAM_LDQM,
output		DRAM_RAS_N,
output		DRAM_UDQM,
output		DRAM_WE_N,

//VGA
output		VGA_B,
output		VGA_BLANK_N,
output		VGA_CLK,
output		VGA_G,
output		VGA_HS,
output		VGA_R,
output		VGA_SYNC_N,
output		VGA_VS,

//DDR3_SDRAM
output	[14:0]	HPS_DDR3_ADDR,
output	[2:0]	HPS_DDR3_BA,
output		HPS_DDR3_CAS_N,
output		HPS_DDR3_CKE,
output		HPS_DDR3_CK_N,
output		HPS_DDR3_CK_p,
output		HPS_DDR3_CS_N,
output	[3:0]	HPS_DDR3_DM,
inout	[31:0]	HPS_DDR3_DQ,
inout	[3:0]	HPS_DDR3_DQS_N,
inout	[3:0]	HPS_DDR3_DQS_P,
output		HPS_DDR3_ODT,
output		HPS_DDR3_RAS_N,
output		HPS_DDR3_RESET_N,
input		HPS_DDR3_RZQ,
output		HPS_DDR3_WE_N,

//mysystem U0 (
//...
//...
//...
//);

endmodule
