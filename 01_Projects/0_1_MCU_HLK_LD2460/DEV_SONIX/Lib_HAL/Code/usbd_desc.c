#include "Middleware_USBD.h"

#define USBD_LANGID_STRING              0x0409
#define USBD_CONFIGURATION_STRING       "USB Config"
#define USBD_MAX_STR_DESC_SIZ           512U
#define LOBYTE(x)  ((uint8_t)((x) & 0x00FFU))
#define HIBYTE(x)  ((uint8_t)(((x) & 0xFF00U) >> 8U))


USB_DeviceDesc_t* USBD_DeviceDescriptor(USBD_Speed_t speed, uint16_t *length);
uint8_t* USBD_LangIDStrDescriptor(USBD_Speed_t speed, uint16_t *length);
uint8_t* USBD_ManufacturerStrDescriptor(USBD_Speed_t speed, uint16_t *length);
uint8_t* USBD_ProductStrDescriptor(USBD_Speed_t speed, uint16_t *length);
uint8_t* USBD_SerialStrDescriptor(USBD_Speed_t speed, uint16_t *length);
uint8_t* USBD_ConfigStrDescriptor(USBD_Speed_t speed, uint16_t *length);

/* HID Descriptor operator structure */
USBD_Descriptors_t USBD_Desc =
{
  .bmAttributes                     = __USBD_ATTR_D5__ << 5|__USBD_ATTR_D6__ << 6,
  .bMaxPower                        = __USBD_MAXPOWER__,  
  .GetDeviceDescriptor              = USBD_DeviceDescriptor,
  .GetLangIDStrDescriptor           = USBD_LangIDStrDescriptor,
  .GetManufacturerStrDescriptor     = USBD_ManufacturerStrDescriptor,
  .GetProductStrDescriptor          = USBD_ProductStrDescriptor,
  .GetSerialStrDescriptor           = USBD_SerialStrDescriptor,
  .GetConfigurationStrDescriptor    = USBD_ConfigStrDescriptor,
};



USB_DeviceDesc_t USBD_DeviceDesc =  {
    0x12,                                 /*bLength */
    1,                                    /*bDescriptorType = USB_DT_DEVICE */
    0x0200,                               /*bcdUSB */
    0x00,                                 /*bDeviceClass*/
    0x00,                                 /*bDeviceSubClass*/
    0x00,                                 /*bDeviceProtocol*/
    64,                                   /*bMaxPacketSize*/
    __USBD_VID__,          				  /*idVendor*/
    __USBD_PID__,          				  /*idProduct*/
    __USBD_VERSION__,      /*bcdDevice*/
    USBD_IDX_MFC_STR,                     /*Index of manufacturer  string*/
    USBD_IDX_PRODUCT_STR,                 /*Index of product string*/
    USBD_IDX_SERIAL_STR,                  /*Index of serial number string*/
    1                                     /*bNumConfigurations*/
};

uint8_t USBD_LangIDDesc[4]  = {
    4,
    3,                                 /* USB_DT_STRING */
    LOBYTE(USBD_LANGID_STRING),
    HIBYTE(USBD_LANGID_STRING)
};
uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ];


USB_DeviceDesc_t * USBD_DeviceDescriptor(USBD_Speed_t speed, uint16_t *length)
{
	*length = sizeof(USBD_DeviceDesc);
	return &USBD_DeviceDesc;
}


uint8_t * USBD_LangIDStrDescriptor(USBD_Speed_t speed, uint16_t *length)
{
	*length = sizeof(USBD_LangIDDesc);
	return USBD_LangIDDesc;
}


uint8_t * USBD_ProductStrDescriptor(USBD_Speed_t speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)"__USBD_PROD_STRING__", USBD_StrDesc, length);
	return USBD_StrDesc;
}

uint8_t * USBD_ManufacturerStrDescriptor(USBD_Speed_t speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)"__USBD_MFG_STRING__", USBD_StrDesc, length);
	return USBD_StrDesc;    
}


uint8_t * USBD_SerialStrDescriptor(USBD_Speed_t speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)"__USBD_SN_STRING__", USBD_StrDesc, length);
	return USBD_StrDesc;   
}

uint8_t * USBD_ConfigStrDescriptor(USBD_Speed_t speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING, USBD_StrDesc, length);
	return USBD_StrDesc;
}

