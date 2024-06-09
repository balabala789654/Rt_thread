#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

rt_device_t* hwtimer1 = RT_NULL;
int device_init(){
    *hwtimer1 = rt_device_create(RT_Device_Class_Timer, 12);
    if(rt_device_hwtimer_register((rt_timer_t*)&hwtimer1, "timer1", 10)!=RT_EOK){
        rt_kprintf("rt_device_hwtimer_register failed\n");
    }
    return 0;
}

MSH_CMD_EXPORT(device_init,device_init);
