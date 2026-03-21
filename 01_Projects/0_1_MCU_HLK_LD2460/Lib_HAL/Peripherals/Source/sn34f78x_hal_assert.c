/**
 * @file hal_sn34f7_assert.c
 * @author PD
 * @brief Enable configUSE_ASSERT in sn34f7_hal_conf.h of current project
 *        User could re-write this function in app project if necessary
 *        the printf should be replace as printf_uart or printf_swo in C/C++ page of IDE Compiler.
 * @version 1.0
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "sn34f78x_hal.h"

#if (configUSE_ASSERT == 1)
__weak void AssertParaFalse(uint8_t *file, uint32_t line)
{
    // printf("Error: file@ $s, line@ %d", file, line);
    while (1)
    {
        /* Delay 1ms */
    }
}

#endif
