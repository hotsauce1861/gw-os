/**
************************************************************************************************
 * @file    : gw_event.c
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

#include "gw_event.h"
#include "gw_type.h"

#define GLOBAL_TIMER global_timer	

#define EVENT_MAX	30
/*
	const char* name;				//事件名称
	uint8_t type;					//事件类型
	uint8_t status; 				//事件状态
	uint32_t timestamp; 			//时间戳
	void* (CALLBACK)(void*) task;	//回调函数
	static struct gw_timer* timer;	//全局定时器	
*/


void gw_event_init(struct gw_event *event){
	event->status = DISABLE;
	event->g_timer = &GLOBAL_TIMER;
}

void set_poll_time(void){
	
}

void update_poll_time(void){
	
}

