#define TESTAPP_GEN
/******************************************************************************
* Copyright (C) 2002 - 2021 Xilinx, Inc.  All rights reserved.
* Copyright (c) 2022 - 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/******************************************************************************/
/**
* @file xiic_selftest_example.c
*
* This file contains a example for using the IIC hardware device and
* XIic driver.
*
* @note
*
* None
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date	 Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a sv   05/09/05 Initial release for TestApp integration.
* 2.00a sdm  09/22/09 Updated to use the HAL APIs, replaced call to
*		      XIic_Initialize API with XIic_LookupConfig and
*		      XIic_CfgInitialize. Minor changes made as per
*		      coding guidelines.
* 3.4   ms   01/23/17 Added xil_printf statement in main function to
*                     ensure that "Successfully ran" and "Failed" strings
*                     are available in all examples. This is a fix for
*                     CR-965028.
* 3.10  gm   07/09/23 Added SDT support.
* </pre>
*
*******************************************************************************/

#include "xparameters.h"
#include "xiic.h"
#include "xil_printf.h"
// #include "iic_header.h"

/************************** Constant Definitions ******************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ifndef TESTAPP_GEN
#ifndef SDT
#define IIC_DEVICE_ID	   XPAR_IIC_0_DEVICE_ID
#else
#define	XIIC_BASEADDRESS	XPAR_XIIC_0_BASEADDR
#endif
#endif
static u8 ReadBuffer[16];
/**************************** Type Definitions ********************************/


/***************** Macros (Inline Functions) Definitions **********************/


/************************** Function Prototypes *******************************/
#ifndef SDT
int IicSelfTestExample(u16 DeviceId);
#else
int IicSelfTestExample(UINTPTR BaseAddress);
#endif
/************************** Variable Definitions ******************************/

/*
 * The following are declared globally so they are zeroed and so they are
 * easily accessible from a debugger.
 */
XIic Iic; /* The driver instance for IIC Device */


/******************************************************************************/
/**
* Main function to call the example. This function is not included if the
* example is generated from the TestAppGen test tool.
*
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful.
*
* @note		None.
*
******************************************************************************/
#ifndef TESTAPP_GEN
int main(void)
{
	int Status;

	/*
	 * Run the example, specify the device ID that is generated in
	 * xparameters.h.
	 */
#ifndef SDT
	Status = IicSelfTestExample(IIC_DEVICE_ID);
#else
	Status = IicSelfTestExample(XIIC_BASEADDRESS);
#endif
	if (Status != XST_SUCCESS) {
		xil_printf("IIC selftest Example Failed \r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran IIC selftest Example\r\n");
	return XST_SUCCESS;

}
#endif

/*****************************************************************************/
/**
*
* This function does a selftest on the IIC device and XIic driver as an
* example.
*
* @param	DeviceId is the XPAR_<IIC_instance>_DEVICE_ID value from
*		xparameters.h.
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful.
*
* @note		None.
*
****************************************************************************/
#ifndef SDT
int IicSelfTestExample(u16 DeviceId)
#else
int IicSelfTestExample(UINTPTR BaseAddress)
#endif
{
	int Status;
	XIic_Config *ConfigPtr;	/* Pointer to configuration data */

	/*
	 * Initialize the IIC driver so that it is ready to use.
	 */
#ifndef SDT
	ConfigPtr = XIic_LookupConfig(DeviceId);
#else
	ConfigPtr = XIic_LookupConfig(BaseAddress);
#endif
	if (ConfigPtr == NULL) {
		return XST_FAILURE;
	}

	Status = XIic_CfgInitialize(&Iic, ConfigPtr, ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Perform a self-test to ensure that the hardware was built
	 * correctly.
	 */
	Status = XIic_SelfTest(&Iic);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

    XIic_Reset(&Iic);
    print("working");
    XIic_SetAddress(&Iic, XII_ADDR_TO_RESPOND_TYPE, 0);

    // xil_printf("开始从 I2C 从机 0x20 读数据...\r\n");
    // Status = IicReadData(I2C_SLAVE_ADDR, ReadBuffer, 5);
    // if (Status != XST_SUCCESS) {
    //     xil_printf("IIC 读数据失败\r\n");
    //     return XST_FAILURE;
    // }

    u8 addr;
    int ByteCount;
    int found_count = 0;


    u8 testByte = 0x00;

    xil_printf("开始扫描 I2C 总线 (7-bit地址 0x00~0x7F)...\r\n");
    
    for (addr = 0x00; addr < 0x80; addr++) {

        ByteCount = XIic_Send(Iic.BaseAddress, 0x70, &testByte, 1, XIIC_STOP);
        ByteCount = XIic_Send(Iic.BaseAddress, addr, &testByte, 1, XIIC_STOP);

        if (ByteCount == 1) {
            xil_printf("发现 I2C 设备: 地址 0x%02X\r\n", addr);
            found_count++;
        }

    }

    if (found_count == 0) {
        xil_printf("未发现任何 I2C 设备!\r\n");
    } else {
        xil_printf("扫描结束, 共检测到 %d 个设备.\r\n", found_count);
    }
	return XST_SUCCESS;


    
}

int IicReadData(u8 SlaveAddress, u8 *Data, int ByteCount)
{
    int Status;

    XIic_SetAddress(&Iic, XII_ADDR_TO_RESPOND_TYPE, SlaveAddress);


    Status = XIic_Recv(Iic.BaseAddress, SlaveAddress, Data, ByteCount, XIIC_STOP);
    if (Status != ByteCount) {
        xil_printf("IicReadData: 期望读取 %d 字节, 实际读取 %d\r\n", ByteCount, Status);
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}
