/**
************************************************************************************************
 * @file    : gw_event.h
 * @brief   : Interface to manage events
 * @details : None
 * @date    : 11-09-2018
 * @version : v1.0.0.0
 * @author  : UncleMac
 * @email   : zhaojunhui1861@163.com
 *
 *      @license    : GNU General Public License, version 3 (GPL-3.0)
 *
 *      Copyright (C)2019 UncleMac.
 *
 *      This code is open source: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This dll is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.If not, see < https://www.gnu.org/licenses/>.
*************************************************************************************************
*/

#ifndef GW_EVENT_H
#define GW_EVENT_H
#include <stdint.h>

#include "gw_timer.h"
#include "gw_msgs.h"
#include "gw_type.h"

#define GW_ENABLE 	1
#define GW_DISABLE 	0

typedef void (*p_init_func)(void);
typedef void (*p_exec_func)(void);

typedef void (*p_exec_args_func)(void* args);

struct gw_event {
	const char* name;				//事件名称
	uint32_t id;					//时间ID
	uint8_t type;					//事件类型
	uint8_t status;					//事件状态
    uint32_t priority;              //事件优先级
	uint32_t timestamp;				//时间戳
	uint32_t poll_time;				//轮询执行时间
    gw_msg_t msg;                   //消息
    p_init_func init_task;          //任务初始化函数
    p_exec_func exec_task;          //轮询任务回调函数
    p_exec_args_func exec_args_task;//带参数的回调函数
	struct gw_timer* g_timer;		//全局定时器	
};

typedef struct gw_event gw_event_typedef;

#endif
