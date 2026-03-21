#ifndef __APP_USB_DEVICE__H__
#define __APP_USB_DEVICE__H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "Middleware_USBD.h"
#include "usbd_desc.h"

void MX_USB_DEVICE_Init(void);
void MX_USB_DEVICE_UnInit(void);
void MX_USB_DEVICE_Process(void);
extern void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_USB_DEVICE__H__ */
