#include "usbd_report_if.h"
#include "string.h"


#define HID_INDEX_MOUSE             0
#define HID_INDEX_KEYBOARD          1
#define HID_INDEX_VENDOR            2

#define HID_MOUSE_REPORT_SIZE       16   /* unit: byte */
#define HID_KB_REPORT_SIZE          16   /* unit: byte */


enum{
    KB_INIT,
    KB_SEND_KEY,
    KB_SEND_RELEASE,
    KB_STOP,
};

typedef struct _MouseReport{
    union   {
        uint8_t Key;
        struct {
            uint8_t Btn1:1;
            uint8_t Btn2:1;
            uint8_t Btn3:1;
            uint8_t Btn4:1;
            uint8_t Btn5:1;
        }b;
    };
    uint8_t bX;
    uint8_t bY;
    uint8_t bWheel;
    uint16_t wX;
    uint16_t wY;
    uint8_t vendor[8];
}MouseReport_t;


typedef struct _KeyboardReport{
    uint8_t ReportID;
    union   {
        /* ReportID = 1 */
        struct {
            union {
                uint8_t MdfKey;
                struct {
                    uint8_t LeftCtrl:1;
                    uint8_t LeftShift:1;
                    uint8_t LeftAlt:1;
                    uint8_t LeftGUI:1;
                    uint8_t RightCtrl:1;
                    uint8_t RightShift:1;
                    uint8_t RightAlt:1;
                    uint8_t RightGUI:1;
                }MdfKey_b;
            };
            uint8_t bmKey[14];
        }kbw;
        
        /* ReportID = 2 */
        uint8_t CustomerCtrl[2];

        /* ReportID = 3 */
        union {
            uint8_t SysCtrl;
            struct {
                uint8_t PowerDone:1;
                uint8_t Sleep:1;
                uint8_t Wakeup:1;
            }SysCtrl_b;
        };
    };
}KeyboardReport_t;

static uint8_t TestString[] = "String For Test... ";
static MouseReport_t MouseReport;
static KeyboardReport_t KeyboardReport;

static uint8_t mouse_report_desc[]		= {
    0x05, 0x01,    		//Usage Page(Generic Desktop Controls )   
    0x09, 0x02,    		//Usage(Mouse)
    0xA1, 0x01,    		//Collection(Application )   
    0x09, 0x01,    		//Usage(Pointer)
    0xA1, 0x00,    		//Collection(Physical )    
    0x05, 0x09,    		//Usage Page(Button )  
    0x19, 0x01,    		//Usage Minimum(0x1 )     
    0x29, 0x05,    		//Usage Maximum(0x5 )    
    0x15, 0x00,    		//Logical Minimum(0x0 )   
    0x25, 0x01,    		//Logical Maximum(0x1 )     
    0x95, 0x05,    		//Report Count(0x5 )      
    0x75, 0x01,    		//Report Size(0x1 )       
    0x81, 0x02,    		//Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)   
    0x95, 0x01,    		//Report Count(0x1 )     
    0x75, 0x03,    		//Report Size(0x3 )      
    0x81, 0x01,    		//Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)  
    0x95, 0x08,    		//Report Count(0x8 )      
    0x75, 0x02,    		//Report Size(0x2 )       
    0x81, 0x01,    		//Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)  
    0x05, 0x01,    		//Usage Page(Generic Desktop Controls )     
    0x09, 0x38,    		//Usage(Wheel)     
    0x15, 0x81,    		//Logical Minimum(0x81 )     
    0x25, 0x7F,    		//Logical Maximum(0x7F )      
    0x75, 0x08,    		//Report Size(0x8 )       
    0x95, 0x01,    		//Report Count(0x1 )      
    0x81, 0x06,    		//Input(Data, Variable, Relative, No Wrap, Linear, Preferred State, No Null Position, Bit Field)   
    0x05, 0x01,    		//Usage Page(Generic Desktop Controls )       
    0x09, 0x30,    		//Usage(X)   
    0x09, 0x31,    		//Usage(Y)   
    0x16, 0x01, 0x80, 	//Logical Minimum(0x8001 )   
    0x26, 0xFF, 0x7F,   //Logical Maximum(0x7FFF )      
    0x75, 0x10,         //Report Size(0x10 )      
    0x95, 0x02,         //Report Count(0x2 )       
    0x81, 0x06,         //Input(Data, Variable, Relative, No Wrap, Linear, Preferred State, No Null Position, Bit Field) 
    0x95, 0x03,         //Report Count(0x3 )      
    0x75, 0x08,         //Report Size(0x8 )     
    0x81, 0x01,         //Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
    0x06, 0x00, 0xFF,   //Usage Page(Undefined )       
    0x09, 0xF1,         //Usage(241)      
    0x15, 0x00,         //Logical Minimum(0x0 )      
    0x26, 0xFF, 0x00,   //Logical Maximum(0xFF )       
    0x75, 0x08,         //Report Size(0x8 )     
    0x95, 0x05,         //Report Count(0x5 )     
    0x81, 0x00,         //Input(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)   
    0xC0,               //End Collection    
    0xC0                //End Collection 
};


static uint8_t keyboard_report_desc[]		= {
    0x05, 0x01,          //Usage Page(Generic Desktop Controls )      
    0x09, 0x06,          //Usage(Keyboard)       
    0xA1, 0x01,          //Collection(Application )       
    0x85, 0x01,          //Report ID(0x1 )    
    0x05, 0x07,          //Usage Page(Key )       
    0x19, 0xE0,          //Usage Minimum(0xE0 )        
    0x29, 0xE7,          //Usage Maximum(0xE7 )      
    0x15, 0x00,          //Logical Minimum(0x0 )       
    0x25, 0x01,          //Logical Maximum(0x1 )     
    0x75, 0x01,          //Report Size(0x1 )      
    0x95, 0x08,          //Report Count(0x8 )      
    0x81, 0x02,          //Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)  
    0x19, 0x00,          //Usage Minimum(0x0 )      
    0x29, 0x6F,          //Usage Maximum(0x6F )       
    0x15, 0x00,          //Logical Minimum(0x0 )     
    0x25, 0x01,          //Logical Maximum(0x1 )       
    0x75, 0x01,          //Report Size(0x1 )      
    0x95, 0x70,          //Report Count(0x70 )      
    0x81, 0x02,          //Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)  
    0xC0,                //End Collection    
    0x05, 0x0C,          //Usage Page(Consumer )    
    0x09, 0x01,          //Usage(Consumer Control)      
    0xA1, 0x01,          //Collection(Application )       
    0x85, 0x02,          //Report ID(0x2 )   
    0x15, 0x00,          //Logical Minimum(0x0 )       
    0x26, 0x2A, 0x02,    //Logical Maximum(0x22A )     
    0x19, 0x00,          //Usage Minimum(0x0 )      
    0x2A, 0x2A, 0x02,    //Usage Maximum(0x22A )       
    0x75, 0x10,          //Report Size(0x10 )      
    0x95, 0x01,          //Report Count(0x1 )   
    0x81, 0x00,          //Input(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)   
    0xC0,                //End Collection        
    0x05, 0x01,          //Usage Page(Generic Desktop Controls )      
    0x09, 0x80,          //Usage(System Control)      
    0xA1, 0x01,          //Collection(Application )      
    0x85, 0x03,          //Report ID(0x3 )     
    0x19, 0x81,          //Usage Minimum(0x81 )     
    0x29, 0x83,          //Usage Maximum(0x83 )   
    0x15, 0x00,          //Logical Minimum(0x0 )      
    0x25, 0x01,          //Logical Maximum(0x1 )       
    0x75, 0x01,          //Report Size(0x1 )       
    0x95, 0x03,          //Report Count(0x3 )     
    0x81, 0x02,          //Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)  
    0x75, 0x01,          //Report Size(0x1 )      
    0x95, 0x05,          //Report Count(0x5 )      
    0x81, 0x01,          //Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) 
    0xC0,                //End Collection  
};

static uint8_t vendor_report_desc[]		= {
    0x06, 0x90, 0xFF,       //Usage Page(Undefined )     
    0x0A, 0x00, 0xFF,       //Usage(65280)    
    0xA1, 0x01,             //Collection(Application )   
    0x85, 0x10,             //Report ID(0x10 )   
    0x09, 0x01,             //Usage(1)     
    0x15, 0x00,             //Logical Minimum(0x0 )      
    0x26, 0xFF, 0x00,       //Logical Maximum(0xFF )      
    0x75, 0x08,             //Report Size(0x8 )       
    0x95, 0x3F,             //Report Count(0x3F )   
    0xB1, 0x82,             //Feature(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, VolatileBit Field) 
    0x85, 0x10,             //Report ID(0x10 )    
    0x09, 0x01,             //Usage(1)       
    0x91, 0x82,             //Output(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, VolatileBit Field)  
    0x85, 0x12,             //Report ID(0x12 )     
    0x09, 0x02,             //Usage(2)   
    0x15, 0x00,             //Logical Minimum(0x0 )     
    0x26, 0xFF, 0x00,       //Logical Maximum(0xFF )      
    0x75, 0x08,             //Report Size(0x8 )      
    0x95, 0x3F,             //Report Count(0x3F )     
    0xB1, 0x82,             //Feature(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, VolatileBit Field)
    0x85, 0x12,             //Report ID(0x12 )      
    0x09, 0x02,             //Usage(2)      
    0x91, 0x82,             //Output(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, VolatileBit Field) 
    0x85, 0x11,             //Report ID(0x11 )   
    0x09, 0x14,             //Usage(20)   
    0x75, 0x08,             //Report Size(0x8 )   
    0x95, 0x3F,             //Report Count(0x3F )   
    0x81, 0x82,             //Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)   
    0x85, 0x13,             //Report ID(0x13 )   
    0x09, 0x15,             //Usage(21)   
    0x75, 0x08,             //Report Size(0x8 )   
    0x95, 0x3F,             //Report Count(0x3F )   
    0x81, 0x82,             //Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)   
    0xC0                    //End Collection   
};



void mouse_set_report(MouseReport_t *rpo, int idx)
{
    memset(rpo, 0, sizeof(MouseReport_t));
    switch((idx/1000)%4) {
    //switch((idx)%4) {
        case 0:
            rpo->bX = 0x01;
            rpo->wX = 0x01;
            break;
        case 1:
            rpo->bY = 0x01;
            rpo->wY = 0x01;
            break;
        case 2:
            rpo->bX = 0xFF;
            rpo->wX = 0xFFFF;
            break;
        case 3:
            rpo->bY = 0xFF;
            rpo->wY = 0xFFFF;
            break;    
    
    }
}

    
    
int32_t Mouse_Test(void)
{
    int32_t ret = HAL_ERROR;
    static uint32_t idx = 0; 

    /* send one report */
    mouse_set_report(&MouseReport, idx);
    ret = USBD_HID_SendReport(HID_INDEX_MOUSE, (uint8_t*)&MouseReport, sizeof(MouseReport));
    if(ret == HAL_OK)  { 
        idx++;
        if(idx >= 0x80000000)
            idx = 0;
    }   

    return ret;

}

void keyboard_set_key(KeyboardReport_t* rpo, char c)
{
    uint16_t shift_bit;
    memset(rpo, 0, sizeof(KeyboardReport_t));
    rpo->ReportID = 0x01;
    
    if(c==0x00)	{                         //button up
        return;
    }else if(c>=0x41 && c<=0x5a)  {       //A-Z
        shift_bit = c-0x41+4;
        rpo->kbw.MdfKey_b.LeftShift = 1;
        rpo->kbw.bmKey[shift_bit>>3] = 1<<(shift_bit&0x7);
    }else if(c>=0x61 && c<=0x7a)  {       //a-z
        shift_bit = c-0x61+4;
        rpo->kbw.bmKey[shift_bit>>3] = 1<<(shift_bit&0x7);
    }else if(c==0x2e) {                   //dot 
        shift_bit = 0x37;
        rpo->kbw.bmKey[shift_bit>>3] = 1<<(shift_bit&0x7);
    }else if(c==0x20) {                   //SpaceBar 
        shift_bit = 0x2c;
        rpo->kbw.bmKey[shift_bit>>3] = 1<<(shift_bit&0x7);
    }else if(c==0x0a) {                   //newline 
        shift_bit = 0x28;
        rpo->kbw.bmKey[shift_bit>>3] = 1<<(shift_bit&0x7);
        shift_bit = 0x53;                      //NumLock 
        rpo->kbw.bmKey[shift_bit>>3] = 1<<(shift_bit&0x7);
    }
}

void keyboard_Test(void)
{
    uint8_t ret; 
    static uint8_t state = KB_INIT;
    static unsigned char *c;  

    switch(state)
    {
        case KB_INIT:
            c = TestString;
            TestString[sizeof(TestString)-1] = 0x0a;	//set newline
            state = KB_SEND_KEY;
            break;
        case KB_SEND_KEY:
            keyboard_set_key(&KeyboardReport, *c);
            ret = USBD_HID_SendReport(HID_INDEX_KEYBOARD, (uint8_t*)&KeyboardReport, sizeof(KeyboardReport));
            if(ret == HAL_OK)  {
                c = ((*c)==0xa)?TestString:(c+1);
                state = KB_SEND_RELEASE;
            }
            break;
        case KB_SEND_RELEASE:
            keyboard_set_key(&KeyboardReport, 0);
            ret = USBD_HID_SendReport(HID_INDEX_KEYBOARD, (uint8_t*)&KeyboardReport, sizeof(KeyboardReport));    
            if(ret == HAL_OK)  {
                state = KB_SEND_KEY;
            }
            break;
    }

}




HAL_Status_T get_feature_report_ctrl_isr(uint8_t idx, uint8_t ReportID, uint8_t *Data, uint16_t *Length)
{
    /* check interface index which supports feature report */
    if(idx!= HID_INDEX_VENDOR)
        return HAL_ERROR;
    
//    switch ( ReportID )    {
//        case HID_ASIC_REPORT_ID:            
//            *Length = MIN(sizeof(asic_id), 0x40);
//            memcpy(Data, &asic_id, *Length);
//            return HAL_OK;
//        default:
//            break;
//    }
    return HAL_ERROR;
}

HAL_Status_T set_feature_report_ctrl_isr(uint8_t idx, uint8_t ReportID, uint8_t *Data, uint16_t Length)
{
    /* check interface index which supports feature report */
    if(idx!= HID_INDEX_VENDOR)
        return HAL_ERROR;
    
//    switch ( ReportID )    {
//        case HID_FW_UPGRADE_REPORT_ID:
//            /* system reset and fw upgrade*/
//            //printf("set_rpo len 0x%02x, %02x %02x %02x %02x\r\n", Length, Data[0], Data[1], Data[2], Data[3]);
//            return HAL_OK;
//        default:
//            break;
//    }
    return HAL_ERROR;    
}

/* HID paramters */

USBD_ReportInfo_t USBD_Report_Info = {
    .intf_num = 3,
    .intf_param[HID_INDEX_MOUSE] = {
        .subclass               = 1,   //(boot interface)            
        .protocol               = 2,   //(mouse)
        .bInEp                  = 1,             
        .bOutEp                 = 0,            
        .in_report_length       = 0x40,    
        .out_report_length      = 0,   
        .feature_report_length  = 0,
        .report_desc_length     = sizeof(mouse_report_desc),
        .report_desc            = mouse_report_desc,        
        .hs_Interval            = 1,         
    },  
    .intf_param[HID_INDEX_KEYBOARD] = {   
       .subclass                = 1,    //(boot interface)
       .protocol                = 1,    //Keyboard
       .bInEp                   = 1,
       .bOutEp                  = 0,
       .in_report_length        = 0x40,
       .out_report_length       = 0,
       .feature_report_length   = 0, 
       .report_desc_length      = sizeof(keyboard_report_desc),
       .report_desc             = keyboard_report_desc,
       .hs_Interval = 1,    
    },
    .intf_param[HID_INDEX_VENDOR] = {   
       .subclass                = 0,    
       .protocol                = 0,
       .bInEp                   = 1,
       .bOutEp                  = 1,
       .in_report_length        = 0x40,
       .out_report_length       = 0x40,
       .feature_report_length   = 0x40, 
       .report_desc_length      = sizeof(vendor_report_desc),
       .report_desc             = vendor_report_desc,
       .hs_Interval = 1,    
    },    
    .GetFeatureReport_isr_cb = get_feature_report_ctrl_isr,
    .SetFeatureReport_isr_cb = set_feature_report_ctrl_isr,
};
