#ifndef __APP_USB_REPORT_IF__H__
#define __APP_USB_REPORT_IF__H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "Middleware_USBD.h"

extern USBD_ReportInfo_t USBD_Report_Info;
int32_t Mouse_Test(void);
void keyboard_Test(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_USB_REPORT_IF__H__ */
