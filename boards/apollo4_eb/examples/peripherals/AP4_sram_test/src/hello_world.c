//*****************************************************************************
//
//! @file hello_world.c
//!
//! @brief A simple "Hello World" example.
//!
//! This example prints a "Hello World" message with some device info
//! over SWO at 1M baud. To see the output of this program, run AMFlash,
//! and configure the console for SWO. The example sleeps after it is done
//! printing.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2020, Ambiq Micro, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision SBL-AP4A-v1-RC-25-g74e0ec548 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

//*****************************************************************************
//
// Insert compiler version at compile time.
//
//*****************************************************************************
#define STRINGIZE_VAL(n)                    STRINGIZE_VAL2(n)
#define STRINGIZE_VAL2(n)                   #n

#ifdef __GNUC__
#define COMPILER_VERSION                    ("GCC " __VERSION__)
#elif defined(__ARMCC_VERSION)
#define COMPILER_VERSION                    ("ARMCC " STRINGIZE_VAL(__ARMCC_VERSION))
#elif defined(__KEIL__)
#define COMPILER_VERSION                    "KEIL_CARM " STRINGIZE_VAL(__CA__)
#elif defined(__IAR_SYSTEMS_ICC__)
#define COMPILER_VERSION                    __VERSION__
#else
#define COMPILER_VERSION                    "Compiler unknown"
#endif

#ifdef __GNUC__
// GCC optimizes this call away preventing a stack overflow
// so we disable optimizations for this test case
__attribute__((optimize("O0")))
#endif
uint32_t sum(uint32_t n) {
    if (n != 0)
        // sum() function calls itself
        return n + sum(n-1);
    else
        return n;
}


uint32_t test_sram(void)
{
	volatile uint32_t *ptr = (uint32_t *)0x10060000;
	volatile uint32_t temp = 0;
	uint32_t err = 0;

	for(int i=0; i < (0x00100000/4)-1; i++)
	{
		*ptr=0xaaaaaaaa;
		ptr++;
	}

	ptr = (uint32_t *)0x10060000;
	for(int i=0; i < (0x00100000/4)-1; i++)
	{
		temp = *ptr;
		if(temp != 0xaaaaaaaa)
		{
			err++;
			am_util_stdio_printf("0x%x=0x%x expected: 0x%x\n", ptr, temp, 0xaaaaaaaa);
			//return err;
		}
		
		ptr++;
	}
	
	ptr = (uint32_t *)0x10060000;
	for(int i=0; i < (0x00100000/4)-1; i++)
	{
		*ptr=0x55555555;
		ptr++;
	}

	ptr = (uint32_t *)0x10060000;
	for(int i=0; i < (0x00100000/4)-1; i++)
	{
		temp = *ptr;
		if(temp != 0x55555555)
		{
			err++;
			am_util_stdio_printf("0x%x=0x%x expected: 0x%x\n", ptr, temp, 0x55555555);
			//return err;
		}
		
		ptr++;
	}

	return err;

}

//*****************************************************************************
//
// Main
//
//*****************************************************************************
int
main(void)
{
    am_util_id_t sIdDevice;
    uint32_t ui32StrBuf;
	uint32_t temp = 0;
	
	 am_util_stdio_printf("Before cache enabled\n");
	
	    //
    // Initialize the printf interface for ITM output
    //
    am_bsp_debug_printf_enable();
    
    

	temp = test_sram();
	
	am_util_stdio_printf("am_hal_cachectrl_enable\n");

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    //
    // Configure the board for low power operation.
    //
    //am_bsp_low_power_init();



    //
    // Print the banner.
    //
    am_util_stdio_terminal_clear();
    am_util_stdio_printf("Hello World(test SRAM%d)!\n\n", temp);

	temp = test_sram();

	am_util_stdio_printf("(test SRAM again%d)!\n\n", temp);

    //
    // Print the device info.
    //
    am_util_id_device(&sIdDevice);
    am_util_stdio_printf("Vendor Name: %s\n", sIdDevice.pui8VendorName);
    am_util_stdio_printf("Device type: %s\n", sIdDevice.pui8DeviceName);

    am_util_stdio_printf("Qualified: %s\n",
                         sIdDevice.sMcuCtrlDevice.ui32Qualified ?
                         "Yes" : "No");
    am_util_stdio_printf("Reset Status:  0x%08X\n", RSTGEN->STAT);
    am_util_stdio_printf("Device Info:\n"
                         "\tPart number: 0x%08X\n"
                         "\tChip ID0:    0x%08X\n"
                         "\tChip ID1:    0x%08X\n"
                         "\tRevision:    0x%08X (Rev%c%c)\n",
                         sIdDevice.sMcuCtrlDevice.ui32ChipPN,
                         sIdDevice.sMcuCtrlDevice.ui32ChipID0,
                         sIdDevice.sMcuCtrlDevice.ui32ChipID1,
                         sIdDevice.sMcuCtrlDevice.ui32ChipRev,
                         sIdDevice.ui8ChipRevMaj, sIdDevice.ui8ChipRevMin );

    //
    // If not a multiple of 1024 bytes, append a plus sign to the KB.
    //
    ui32StrBuf = ( sIdDevice.sMcuCtrlDevice.ui32MRAMSize % 1024 ) ? '+' : 0;
    am_util_stdio_printf("\tMRAM size:   %7d (%d KB%s)\n",
                         sIdDevice.sMcuCtrlDevice.ui32MRAMSize,
                         sIdDevice.sMcuCtrlDevice.ui32MRAMSize / 1024,
                         &ui32StrBuf);

    ui32StrBuf = ( sIdDevice.sMcuCtrlDevice.ui32DTCMSize % 1024 ) ? '+' : 0;
    am_util_stdio_printf("\tDTCM size:   %7d (%d KB%s)\n",
                         sIdDevice.sMcuCtrlDevice.ui32DTCMSize,
                         sIdDevice.sMcuCtrlDevice.ui32DTCMSize / 1024,
                         &ui32StrBuf);

    ui32StrBuf = ( sIdDevice.sMcuCtrlDevice.ui32SSRAMSize % 1024 ) ? '+' : 0;
    am_util_stdio_printf("\tSSRAM size:  %7d (%d KB%s)\n\n",
                         sIdDevice.sMcuCtrlDevice.ui32SSRAMSize,
                         sIdDevice.sMcuCtrlDevice.ui32SSRAMSize / 1024,
                         &ui32StrBuf);

    //
    // Print the compiler version.
    //
    am_util_stdio_printf("App Compiler:    %s\n", COMPILER_VERSION);
    am_util_stdio_printf("HAL Compiler:    %s\n", g_ui8HALcompiler);
    am_util_stdio_printf("HAL SDK version: %d.%d.%d\n",
                         g_ui32HALversion.s.Major,
                         g_ui32HALversion.s.Minor,
                         g_ui32HALversion.s.Revision);
    am_util_stdio_printf("HAL compiled with %s-style registers\n",
                         g_ui32HALversion.s.bAMREGS ? "AM_REG" : "CMSIS");

    //
    // We are done printing.
    // Disable debug printf messages on ITM.
    //
    //am_bsp_debug_printf_disable();
    
    //
    // Loop forever while sleeping.
    //
    while (1)
    {
        //
        // Go to Deep Sleep.
        //
        //am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
				sum(0xF);
    }
}
