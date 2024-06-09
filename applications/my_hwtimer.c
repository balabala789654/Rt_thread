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
#include <inc/my_PIN.h>

/*
 *  rt时代的硬件定时器很麻烦
 *  具体操作方法见drivers/board.h文件
 *  但是board.h文件中提供的硬件定时器很有限
 *  如果需要使用其他定时器需要在drivers/include/config/tim_config.h文件中做相应的增添
 *  增添的定时器需要符合drivers/drv_hwtimer.c文件中提供的定时器 例如定时器1无法使用
 *
 *  在完成board.h文件中提供的操作步骤后 按照以下代码即可使用硬件定时器
 *  在终端中输入list device即可查看硬件定时器是否被注册
 *
 *  anyway 如果想查看硬件定时器设备的接口函数 在rt-thread\components\drivers\hwtimer\hwtimer.c文件中查看
 *
 *  md 研究了我一天 :(
 * */
#define hwtimer_0 "timer3"

rt_device_t hwtimer = RT_NULL;

rt_hwtimerval_t mytimerout_t;
rt_hwtimerval_t mytimercur_t;
rt_hwtimer_mode_t hw_mode;
rt_uint32_t hw_frq = 1000000;

rt_thread_t hwtimer_thread = RT_NULL;

void hwtimer_sentry(void *p){
    while(1){

        //读取硬件定时器实时时间
        rt_device_read(hwtimer, 0, &mytimercur_t, sizeof(mytimercur_t));
        rt_kprintf("current time sec: %d usec: %d\n", mytimercur_t.sec, mytimercur_t.usec);
        rt_thread_mdelay(100);
    }
}

static rt_err_t timerout_handler(rt_device_t dev, rt_size_t size){
    rt_pin_write(Led1, !rt_pin_read(Led1));
    return 0;
}

int hwtimer_init(int argc, char *argv[]){

    //查找定时器设备
    hwtimer = rt_device_find(hwtimer_0);

    if(hwtimer==RT_NULL){
        rt_kprintf("rt_device_find failed\n");
        return 0;
    }

    //打开定时器
    if(rt_device_open(hwtimer, RT_DEVICE_OFLAG_RDWR)!=RT_EOK){
        rt_kprintf("rt_device_open failed\n");
    }

    //接入定时器中断溢出函数
    rt_device_set_rx_indicate(hwtimer, timerout_handler);

    hw_mode = HWTIMER_MODE_PERIOD;

    //定时器改变频率
    rt_device_control(hwtimer, HWTIMER_CTRL_FREQ_SET, &hw_frq);

    //对定时器设置模式
    rt_device_control(hwtimer, HWTIMER_CTRL_MODE_SET, &hw_mode);

    mytimerout_t.sec = 1;
    mytimerout_t.usec = 0;

    //对定时器写入溢出时间
    rt_device_write(hwtimer, 0, &mytimerout_t, sizeof(mytimerout_t));

    hwtimer_thread = rt_thread_create("hwtimer_thread", hwtimer_sentry, RT_NULL, 512, 15, 10);

    if(hwtimer_thread != RT_NULL){
        rt_thread_startup(hwtimer_thread);
    }
    return 0;
}

int hwtimer_read(void){
    rt_device_read(hwtimer, 0, &mytimercur_t, sizeof(mytimercur_t));
    rt_kprintf("current time sec: %d usec: %d\n", mytimercur_t.sec, mytimercur_t.usec);
    return 0;
}
MSH_CMD_EXPORT(hwtimer_init,hwtimer_work)
MSH_CMD_EXPORT(hwtimer_read,hwtimer_read)





