# Microblaze_V_App


This repository provides a reference **MicroBlaze V** application targeting **Xilinx Vivado & Vitis 2024**. The core examples cover:
- **Memory Read** operations (e.g., from BRAM or DDR),
- **Interrupt Handling** with a simple ISR workflow,
- **AXI IIC** (I2C) communication to interface with external I2C devices.



## Overview

This example project demonstrates typical use cases in a MicroBlaze V embedded system:

1. **Reading from memory**: Access data from BRAM or DDR memory spaces.  
2. **Handling interrupts**: Configure and manage interrupt routines via the MicroBlaze interrupt controller.  
3. **AXI IIC communication**: Set up and use the AXI IIC IP to communicate over the I2C bus.

By following this guide, you can:
- Generate the Vivado hardware design (2024 or newer).
- Import the hardware into Vitis 2024 for software development.
- Program the FPGA and run the application on the MicroBlaze V core.

---

## Requirements

- **Vivado 2024** (or newer) and **Vitis 2024** (or newer).  
- A Xilinx FPGA development board supporting **MicroBlaze V**.  
- (Optional) A **serial terminal** (e.g., PuTTY, TeraTerm) to view UART output.  
- (Optional) An **I2C slave device** (e.g., EEPROM, sensor) to test AXI IIC functionality.

> **Note**: The version numbers assume you have access to a future (or prerelease) Vivado/Vitis 2024. If you are using an older or different version, adjust accordingly.

---

## Project Structure

Below is an example directory layout for reference:

