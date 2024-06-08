/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-07     22169       the first version
 */

#include <rtthread.h>
#include <board.h>

static rt_thread_t thread_1;

void thread_1_entry(void *p){
    while(1){
        rt_kprintf("working\n");
        rt_thread_mdelay(1000);

    }
}

void thread_work(void){
    thread_1 = rt_thread_create("thread1", thread_1_entry, RT_NULL, 512, 12, 5);

    if(thread_1 != RT_NULL){
        rt_thread_startup(thread_1);
    }
}

void thread_stop(void){
    rt_thread_delete(thread_1);
    rt_kprintf("stop thread\n");

}
MSH_CMD_EXPORT(thread_work, thread_work);
MSH_CMD_EXPORT(thread_stop, thread_stop);
