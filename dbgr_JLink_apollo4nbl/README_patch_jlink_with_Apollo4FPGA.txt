Feb 1, 2020

This brief installation procedure will update an existing J-Link installation
with support for use with the Apollo4 FPGA.

Note: This procedure assumes J-Link v6.62a is installed.  Substitute your own
      installed version anywhere "662a" appears below.

1. Exit from all usage of all J-Link tools.

2. This step will require administrator privileges.
   a. Copy
      C:\Program Files (x86)\SEGGER\JLink_V662a\JLinkDevices.xml
      to a convenient location for editing.

   b. Add the following as the first entry in the AmbiqMicro section.  If there
      is no AmbiqMicro section, add the following section.

  <Device>
    <ChipInfo Vendor="AmbiqMicro" Name="Apollo4_FPGA" WorkRAMAddr="0x10000000" WorkRAMSize="0x60000" Core="JLINK_CORE_CORTEX_M4" />
    <FlashBankInfo Name="Apollo4 FPGA" BaseAddr="0x00000000" MaxSize="0x200000" Loader="Devices\AmbiqMicro\Apollo4_nbl.FLM" LoaderType="FLASH_ALGO_TYPE_OPEN" AlwaysPresent="1" />
  </Device>

   c. Copy JLinkDevices.xml back to its original location.

3. Copy the contents of 'Devices/AmbiqMicro/' from this install directory to 
   C:\Program Files (x86)\SEGGER\JLink_V662a\Devices\AmbiqMicro\

4. Start J-Flash Lite.
   You should be able to select Apollo4_FPGA as the device.
   You should further be able to erase the device.

5. Now you should be able to run J-Link in any debugger environment as usual.
