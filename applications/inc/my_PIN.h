/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-09     22169       the first version
 */
#ifndef APPLICATIONS_INC_MY_PIN_H_
#define APPLICATIONS_INC_MY_PIN_H_

#include <rtthread.h>
#include <board.h>

#define Led1 GET_PIN(F, 9)
#define Led2 GET_PIN(F,10)
#define Key1 GET_PIN(E,4)
#define Key2 GET_PIN(A,0)

void PIN_init(void);

#endif /* APPLICATIONS_INC_MY_PIN_H_ */
