/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-07     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <inc/my_PIN.h>

int main(void)
{
    PIN_init();
    while (RT_TRUE)
    {
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
