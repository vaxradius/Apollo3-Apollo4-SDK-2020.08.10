/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Quan Zhang for Ambiqmicro Apollo4
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#include "tusb_option.h"

#if TUSB_OPT_DEVICE_ENABLED && CFG_TUSB_MCU == OPT_MCU_APOLLO4

#include "device/dcd.h"
#include "am_hal_usb.h"

/*------------------------------------------------------------------*/
/* MACRO TYPEDEF CONSTANT ENUM
 *------------------------------------------------------------------*/

static void *pUSBHandle = NULL;

// mapping&injecting the ambiq USB HAL event to TinyUSB USB stack
static void dcd_usb_dev_evt_callback(am_hal_usb_dev_event_e eDevState)
{
  switch(eDevState)
  {
    case AM_HAL_USB_DEV_EVT_BUS_RESET:
      am_hal_usb_intr_usb_enable(pUSBHandle, USB_CFG2_SOFE_Msk|USB_CFG2_ResumeE_Msk|USB_CFG2_SuspendE_Msk|USB_CFG2_ResetE_Msk);
      am_hal_usb_ep_init(pUSBHandle, 0, 0, 64);
      // am_hal_usb_set_dev_speed(pUSBHandle, AM_HAL_USB_SPEED_FULL);
      dcd_event_bus_signal(0, DCD_EVENT_BUS_RESET, true);
      break;
    case AM_HAL_USB_DEV_EVT_RESUME:
      dcd_event_bus_signal(0, DCD_EVENT_RESUME, true);
      //do something for resuming
      //then set the device state to active
      am_hal_usb_set_dev_state(pUSBHandle, AM_HAL_USB_DEV_STATE_ACTIVE);
      break;
    case AM_HAL_USB_DEV_EVT_SOF:
      dcd_event_bus_signal(0, DCD_EVENT_SOF, true);
      break;
    case AM_HAL_USB_DEV_EVT_SUSPEND:
      dcd_event_bus_signal(0, DCD_EVENT_SUSPEND, true);
      //do something for suspending
      //then set the device state to suspended
      am_hal_usb_set_dev_state(pUSBHandle, AM_HAL_USB_DEV_STATE_SUSPENDED);
      break;
    default:
      //not reachable case
      //add to suppress the compiling warning
      break;
  }
}

// setup request is received and pass it to upper layer TinyUSB
// stack to handle
static void dcd_usb_ep0_setup_callback(uint8_t *setup)
{
  dcd_event_setup_received(0, setup, true);
}

static void dcd_usb_ep_xfer_complete_callback(const uint8_t ep_addr, const uint16_t xfer_len, am_hal_usb_xfer_code_e code, void *param)
{
  switch(code)
  {
    case USB_XFER_DONE:
      dcd_event_xfer_complete(0, ep_addr, xfer_len, XFER_RESULT_SUCCESS, true);
      break;
    case USB_XFER_STALL:
      dcd_event_xfer_complete(0, ep_addr, xfer_len, XFER_RESULT_STALLED, true);
      break;
    default:
      //TODO:
      dcd_event_xfer_complete(0, ep_addr, xfer_len, XFER_RESULT_FAILED, true);
      break;
  }
}

/*------------------------------------------------------------------*/
/* Controller API
 *------------------------------------------------------------------*/
void dcd_init (uint8_t rhport)
{
  (void) rhport;
  if (am_hal_usb_initialize(0, (void *)&pUSBHandle) == AM_HAL_STATUS_SUCCESS)
  {
      //
      // Turn on the USB power
      //
      am_hal_usb_power_control(pUSBHandle, AM_HAL_SYSCTRL_WAKE, false);

      //
      // Register the callback functions
      //
      am_hal_usb_register_dev_evt_callback(pUSBHandle, dcd_usb_dev_evt_callback);
      am_hal_usb_register_ep0_setup_received_callback(pUSBHandle, dcd_usb_ep0_setup_callback);
      am_hal_usb_register_ep_xfer_complete_callback(pUSBHandle, dcd_usb_ep_xfer_complete_callback);

      am_hal_usb_intr_usb_enable(pUSBHandle, USB_CFG2_ResetE_Msk);
      am_hal_usb_attach(pUSBHandle);
  }
}

void dcd_int_enable(uint8_t rhport)
{
  (void) rhport;
  am_hal_usb_intr_enable(USB0_IRQn);
}

void dcd_int_disable(uint8_t rhport)
{
  (void) rhport;
  am_hal_usb_intr_disable(USB0_IRQn);
}

void dcd_set_address (uint8_t rhport, uint8_t dev_addr)
{
  // Response with status first before changing device address
  dcd_edpt_xfer(rhport, tu_edpt_addr(0, TUSB_DIR_IN), NULL, 0);
  am_hal_usb_set_addr(pUSBHandle, dev_addr);
  am_hal_usb_set_dev_state(pUSBHandle, AM_HAL_USB_DEV_STATE_ADDRESSED);
}

void dcd_set_config (uint8_t rhport, uint8_t config_num)
{
  (void) rhport;
  (void) config_num;
  am_hal_usb_set_dev_state(pUSBHandle, AM_HAL_USB_DEV_STATE_CONFIGED);
}

void dcd_remote_wakeup(uint8_t rhport)
{
  (void) rhport;
  am_hal_usb_start_remote_wakeup(pUSBHandle);
  //TODO: need to start a ~10ms timer
  //      when ~10ms elapsed, in the callback function
  //      to end the remote wakeup by calling
  //      'am_hal_usb_end_remote_wakeup'
}

/*------------------------------------------------------------------*/
/* DCD Endpoint port
 *------------------------------------------------------------------*/

bool dcd_edpt_open (uint8_t rhport, tusb_desc_endpoint_t const * desc_edpt)
{
  (void) rhport;

  am_hal_usb_ep_init((void *)pUSBHandle, desc_edpt->bEndpointAddress, (uint8_t)(desc_edpt->bmAttributes.xfer), (uint16_t)(desc_edpt->wMaxPacketSize.size));

  return true;
}

bool dcd_edpt_xfer (uint8_t rhport, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes)
{
  (void) rhport;
  
  am_hal_usb_ep_xfer(pUSBHandle, ep_addr, buffer, total_bytes);

  return true;
}

void dcd_edpt_stall (uint8_t rhport, uint8_t ep_addr)
{
  (void) rhport;

  am_hal_usb_ep_stall(pUSBHandle, ep_addr);
}

void dcd_edpt_clear_stall (uint8_t rhport, uint8_t ep_addr)
{
  am_hal_usb_ep_clear_stall(pUSBHandle, ep_addr);
}

/*------------------------------------------------------------------*/

void am_usb_isr(void)
{
    uint32_t ui32IntStatus[3];
    am_hal_usb_intr_status_get(pUSBHandle, &ui32IntStatus[0], &ui32IntStatus[1], &ui32IntStatus[2]);
    am_hal_usb_interrupt_service(pUSBHandle, ui32IntStatus[0], ui32IntStatus[1], ui32IntStatus[2]);
}

#endif
