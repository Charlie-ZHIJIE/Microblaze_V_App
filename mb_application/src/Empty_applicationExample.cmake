set(DDR lmb_bram_0)
set(lmb_bram_0 "0x0;0x20000")
set(axi_bram_0 "0x400000;0x8000")
set(TOTAL_MEM_CONTROLLERS "lmb_bram_0;axi_bram_0")
set(MEMORY_SECTION "MEMORY
{
	lmb_bram_0 : ORIGIN = 0x0, LENGTH = 0x20000
	axi_bram_0 : ORIGIN = 0x400000, LENGTH = 0x8000
}")
set(STACK_SIZE 0x400)
set(HEAP_SIZE 0x800)
