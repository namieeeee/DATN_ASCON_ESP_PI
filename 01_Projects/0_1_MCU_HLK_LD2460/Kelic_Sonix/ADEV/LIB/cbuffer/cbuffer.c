/**
* @file       cbuffer.c
* @version    1.0.0
* @date       2023-12-29
* @author     MinhLCN
* @brief      
*/

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"


/* Private defines ---------------------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private function definitions --------------------------------------- */
/* Function definitions ----------------------------------------------- */
ERROR_CODE_T_T cbuffer_init(cbuffer_t *cb, void *buf, uint16_t size)
{
    ERROR_CODE_T_T ret    = R_OK_;

    cb->index_read  = 0;
    cb->index_write = 0;
    cb->overflow    = 0;
    cb->size        = size;
    cb->data        = (uint8_t *)buf;

    return ret;
}

ERROR_CODE_T_T cbuffer_read(cbuffer_t *cb, uint8_t *buf, uint16_t bytes)
{
    ERROR_CODE_T_T ret = R_OK_;  // Assume successful read unless buffer is empty
    uint16_t i;

    // Loop to read the requested number of bytes from the buffer
    for (i = 0; i < bytes; i++)
    {
        /* Check if the read index is different from the write index,
           which means there is data to read. */
        if (cb->index_read != cb->index_write)
        {
            // Copy the byte at the current read index into the destination buffer
            *buf = cb->data[cb->index_read];
            buf++;  // Increment the destination buffer pointer

            /* Check if the read index has reached the end of the buffer.
               If so, wrap around to the start (circular buffer behavior). */
            if ((cb->index_read + 1) == (cb->size))
            {
                cb->index_read = 0;  // Wrap around to the beginning of the buffer
            }
            else
            {
                cb->index_read++;  // Move to the next byte in the buffer
            }
        }
        else
        {
            // No more data to read, exit the loop
            ret = R_NG_;  // Set return status to indicate no data available
            break;
        }
    }

    // Return the status of the read operation
    return ret;
}


ERROR_CODE_T_T cbuffer_only_read(cbuffer_t *cb, uint16_t idx, uint8_t *data)
{
    ERROR_CODE_T_T ret = R_OK_;

    if(cb->index_read != cb->index_write)
    {
        *data = cb->data[cb->index_read + idx];
    }
    else
    {
        ret = R_ERROR_;
    }

    return ret;
}

ERROR_CODE_T_T cbuffer_clear(cbuffer_t *cb)
{
    ERROR_CODE_T_T ret = R_OK_;

    cb->index_read  = 0;
    cb->index_write = 0;
    cb->overflow    = 0;

   // memset(cb->data, 0x00, sizeof(*(cb->data)));
	   memset(cb->data, 0x00, cb->size);

    return ret;
}

ERROR_CODE_T_T cbuffer_write(cbuffer_t *cb, uint8_t *buf, uint16_t bytes)
{
    ERROR_CODE_T_T ret = R_OK_;  // Assume write successful
    uint16_t i;

    // Loop to write the requested number of bytes to the buffer
    for (i = 0; i < bytes; i++)
    {
        /* Check if the next write position would overwrite the read position,
           which would indicate a buffer overflow. */
        if ((cb->index_write + 1 == cb->index_read) ||  // Write next byte would overwrite the read position
            ((cb->index_write + 1 == cb->size) &&      // Write next byte would go beyond the end of the buffer
             (cb->index_read == 0)))                    // Wrap around to the start of the buffer
        {
            // If overflow condition occurs, increase the overflow count and break out of the loop
            cb->overflow += (bytes - i);  // Increment the overflow count by the number of unwritten bytes
            ret = R_ERROR_;              // Set return status to indicate memory overflow
            break;  // Stop writing, buffer is full
        }
        else
        {
            // Write the byte at the current write index to the buffer
            cb->data[cb->index_write] = *buf;
            buf++;  // Move to the next byte in the input buffer

            /* If the write index has reached the end of the buffer,
               wrap around to the beginning (circular buffer behavior). */
            if (cb->index_write + 1 == cb->size)
            {
                cb->index_write = 0;  // Reset the write index to the beginning
            }
            else
            {
                cb->index_write++;  // Move to the next position in the buffer
            }
        }
    }
    // Return the status of the read operation
    return ret;
}

uint16_t cbuffer_data_count(cbuffer_t *cb)
{
    uint16_t ret                = 0;
    uint16_t tmp_index_write    = cb->index_write;
    uint16_t tmp_index_read     = cb->index_read;
    
    if (tmp_index_read <= tmp_index_write)
    {
        ret = tmp_index_write - tmp_index_read;
    }
    else
    {
        ret = tmp_index_write + (cb->size - tmp_index_read);
    }

    return ret;
}

uint16_t cbuffer_space_count(cbuffer_t *cb)
{
    uint16_t ret                = 0;
    uint16_t tmp_index_write = cb->index_write;
    uint16_t tmp_index_read = cb->index_read;
    
    if (tmp_index_read <= tmp_index_write)
    {
        ret = (cb->size - tmp_index_write) + tmp_index_read;
    }
    else
    {
        ret = tmp_index_read - tmp_index_write;
    }

    return ret;
}

void Print_cbuffer_debug(cbuffer_t *cb)
{
    uint16_t idx_start = 0;
    uint16_t idx_stop = 0;

    idx_start = cb->index_read;
    idx_stop = cb->index_write;

    if (idx_start <= idx_stop)
    {
        for(idx_start = cb->index_read; idx_start < idx_stop; idx_start++)
        {
         //   DEBUG_PRINT("%.2X\t", cb->data[idx_start]);
        }
    }
    else
    {
        for(idx_start = cb->index_read; idx_start < cb->size; idx_start++)
        {
            //DEBUG_PRINT("%.2X\t", cb->data[idx_start]);
        }

        for(idx_start = 0; idx_start < idx_stop; idx_start++)
        {
           // DEBUG_PRINT("%.2X\t", cb->data[idx_start]);
        }
    }

}
/* End of file -------------------------------------------------------- */
