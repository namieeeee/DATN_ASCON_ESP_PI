#include "usb_device.h"
__INCLUDE_USBD__

/* USBD instance */
USBD_Handle_t hUsbDevice;

__USBD_MSC_BUFFER__
void MX_USB_DEVICE_Init(void)
{
	if ( USBD_Init(&hUsbDevice, (USBD_Descriptors_t *)&USBD_Desc) != HAL_OK)  {
		Error_Handler();
	}
__USBD_CLASS_HID____USBD_OPERATOR_HID____USBD_CLASS_MSC____USBD_OPERATOR_MSC____USBD_CLASS_CDC__
	if ( USBD_ForceFS(&hUsbDevice, __USBD_FORCE_FS__) != HAL_OK)  {
		Error_Handler();
	}
	
	if (USBD_Start(&hUsbDevice) != HAL_OK)  {
         Error_Handler();
    }
}

void MX_USB_DEVICE_UnInit(void)
{
	USBD_DeInit(&hUsbDevice);

}

void MX_USB_DEVICE_Process(void)
{
	__USBD_MSC_TASK__
}
