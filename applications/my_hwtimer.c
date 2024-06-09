/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-08     22169       the first version
 */

#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>

#define hwtimer_0 "timer3"

rt_device_t hwtimer = RT_NULL;

rt_hwtimerval_t mytimerout_t;
rt_hwtimerval_t mytimercur_t;
rt_hwtimer_mode_t hw_mode;
rt_uint32_t hw_frq = 1000000;

static rt_err_t timerout_handler(rt_device_t dev, rt_size_t size){
    rt_kprintf("timer out\n");
    return 0;
}

int hwtimer_init(int argc, char *argv[]){

    hwtimer = rt_device_find(hwtimer_0);

    if(hwtimer==RT_NULL){
        rt_kprintf("rt_device_find failed\n");
        return 0;
    }

    if(rt_device_open(hwtimer, RT_DEVICE_OFLAG_RDWR)!=RT_EOK){
        rt_kprintf("rt_device_open failed\n");
    }
    rt_device_set_rx_indicate(hwtimer, timerout_handler);

    hw_mode = HWTIMER_MODE_PERIOD;

    rt_device_control(hwtimer, HWTIMER_CTRL_FREQ_SET, &hw_frq);
    rt_device_control(hwtimer, HWTIMER_CTRL_MODE_SET, &hw_mode);

    mytimerout_t.sec = 1;
    mytimerout_t.usec = 0;

    rt_device_write(hwtimer, 0, &mytimerout_t, sizeof(mytimerout_t));

    rt_device_read(hwtimer, 0, &mytimercur_t, sizeof(mytimercur_t));


    return 0;
}

MSH_CMD_EXPORT(hwtimer_init,hwtimer_work)
