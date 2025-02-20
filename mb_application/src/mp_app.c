
#include "xiic.h"            // For AXI IIC driver
#include "xparameters.h"     // For device IDs, base addresses
#include "xil_types.h"
#include "xstatus.h"
#include "xil_printf.h"      // For xil_printf
#include <stdio.h>
#include "platform.h"
#include "bram.h"

#define AXI_BRAM_BASE (0x400000U)

int main()
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran MB application\r\n");
    bram_Init();
    Xil_Out32(AXI_BRAM_BASE, 0xDEADBEEF);
    uint32_t val = Xil_In32(AXI_BRAM_BASE);
    xil_printf("Value read from AXI BRAM: 0x%08X\r\n", val);
    cleanup_platform();
    return 0;
}