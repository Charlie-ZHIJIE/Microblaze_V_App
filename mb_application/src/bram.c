#include "xbram.h"
#include "xparameters.h" 
#include "bram.h"


XBram_Config *ConfigPtr;
XBram         BramInstance;
int           Status;

int bram_Init()
{
    XBram_Config *ConfigPtr;
    XBram         BramInstance;

    ConfigPtr = XBram_LookupConfig(XPAR_XBRAM_0_BASEADDR);
    if (!ConfigPtr) {
        return XST_FAILURE;
    }

    Status = XBram_CfgInitialize(&BramInstance, ConfigPtr, ConfigPtr->CtrlBaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

	return XST_SUCCESS;


    
}