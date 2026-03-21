#include "Middleware_USBD.h"


static HAL_Status_T Storage_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int32_t Storage_IsReady(uint8_t lun);
static int32_t Storage_IsWriteProtected(uint8_t lun);
static void Storage_NotifyEject(uint8_t lun);
static int32_t Storage_GetMaxLun(void);
static HAL_Status_T Storage_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static HAL_Status_T Storage_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);

USBD_Storage_t USBD_Storage_ops =
{
    .GetCapacity         = Storage_GetCapacity,
    .IsReady             = Storage_IsReady,
    .IsWriteProtected    = Storage_IsWriteProtected,
    .NotifyEject         = Storage_NotifyEject,
    .GetMaxLun           = Storage_GetMaxLun,
    .Read                = Storage_Read,
    .Write               = Storage_Write,

};

uint8_t MSC_Buf[32768]__attribute__((aligned)) = {0};

void MX_SRAM_Init(void)
{
    memset(MSC_Buf, 0, sizeof(MSC_Buf));
}


static HAL_Status_T Storage_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
	/* provide storage capacity and size of a block(in byte unit) for specified lun */
    *block_num = sizeof(MSC_Buf)>>9;
    *block_size = 512U;
	return HAL_OK;
}

static int32_t Storage_IsReady(uint8_t lun)
{
	/* return storage is ready(0) or not ready(1) for specified lun */
	return 0;
}

static int32_t Storage_IsWriteProtected(uint8_t lun)
{
	/* return storage is Write protect(1) or No Wrote proect(1) for specified lun */
	return 0;
}

static void Storage_NotifyEject(uint8_t lun)
{
	/* Process of eject */
}

static int32_t Storage_GetMaxLun(void)
{
	/* return max_lun - 1 */
	return 0; //support 1 Lun
}

static HAL_Status_T Storage_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
	/* execute read procedure for specified lun and don't return until procedure is completed */
    memcpy(buf, MSC_Buf+(blk_addr<<9),  blk_len<<9);
    return HAL_OK;
}

static HAL_Status_T Storage_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
	/* execute write procedure for specified lun and don't return until procedure is completed */
    memcpy(MSC_Buf+(blk_addr<<9), buf, blk_len<<9);
    return HAL_OK;
}
