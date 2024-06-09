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
#include <inc/my_PIN.h>

static rt_thread_t LED_thread;

void LED_thread_entry(void *p){
    while(1){
        rt_pin_write(Led1, !rt_pin_read(Led1));
        rt_thread_mdelay(1000);
    }
}

void KEY1_handler(void *p){
    rt_kprintf("Key1 pressed\n");

}

void KEY2_handler(void *p){
    rt_hw_us_delay(10000);
    rt_kprintf("Key2 pressed\n");
    rt_pin_write(Led2, !rt_pin_read(Led2));
}

void PIN_init(void){
    rt_pin_mode(Led1, PIN_MODE_OUTPUT);
    rt_pin_mode(Led2, PIN_MODE_OUTPUT);
    rt_pin_mode(Key1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(Key2, PIN_MODE_INPUT_PULLUP);

    rt_pin_write(Led1, 1);
    rt_pin_write(Led2, 1);

    LED_thread = rt_thread_create("LED_thread", LED_thread_entry, RT_NULL, 512, 10, 10);

    if(LED_thread != RT_NULL){
//        rt_thread_startup(LED_thread);
    }

    if(rt_pin_attach_irq(Key1, PIN_IRQ_MODE_RISING, KEY1_handler, RT_NULL) != RT_ERROR){
        rt_pin_irq_enable(Key1, PIN_IRQ_ENABLE);
    }else{
        rt_kprintf("Key1 attach error\n");
    }

    if(rt_pin_attach_irq(Key2, PIN_IRQ_MODE_RISING, KEY2_handler, RT_NULL) != RT_ERROR){
        rt_pin_irq_enable(Key2, PIN_IRQ_ENABLE);
    }else{
        rt_kprintf("Key2 attach error\n");
    }

}

MSH_CMD_EXPORT(PIN_init, PIN_init);

