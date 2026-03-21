#ifndef __APP_USB_STORAGE_IF__H__
#define __APP_USB_STORAGE_IF__H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "Middleware_USBD.h"

extern USBD_Storage_t USBD_Storage_ops;
void MX_SRAM_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* __APP_USB_STORAGE_IF__H__ */
