================================================================================
                                PROJECT
================================================================================

Function descriptions:
This sample demonstrates the USB Udisk functionality.
USB Udisk is mainly implemented by USB MSC class, the MCU flash is divided into 
two region, 0x08000000~0x08007FFF as the user code area, 0x08008000~0x8020000 
simulated into a 96Kbytes USB flash drive

================================================================================

Test environment:
Test board: STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10

================================================================================

Example execution steps:
1. Download and run the program;
2. Connect the STK board to the PC computer using the USB cable;
3. A 96Kbytes USB Udisk is displayed on the PC. Data can be stored on the 
USB Udisk.

================================================================================

1. When you use the USB flash drive for the first time, format the USB Udisk as
prompted. 
2. This example uses the MCU of 96Kbytes flash. If you want to apply other 
sizes of flash, you need to modify the code. 
3. In this example, the MCU flash reserves only 32Kbytes for the user program. 
If the user program exceeds 32KBytes, the code needs to be modified

================================================================================