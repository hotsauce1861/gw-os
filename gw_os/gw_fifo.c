#include <stdio.h>

#include "gw_fifo.h"
#include "gw_event.h"
#include "gw_timer.h"
#include "gw_tasks.h"
#include "gw_type.h"

#define EVENT_MAX	30
/*
	const char* name;				//事件名称
	uint8_t type;					//事件类型
	uint8_t status; 				//事件状态
	uint32_t timestamp; 			//时间戳
	void* (CALLBACK)(void*) task;	//回调函数
	static struct gw_timer* timer;	//全局定时器	
*/

extern struct gw_event event_table[EVENT_SIZE];
#if 0
static struct gw_event event_table[EVENT_SIZE] = 
{
#if 0
	{	
		.name = "event1",
		.type = TYPE_IRQ, 
		.status = ENABLE,
		.exec_task = task_svpwm,
		.poll_time = 20,
		.g_timer = &global_timer,		
	},
	
	{
		.name = "event2",
		.type = TYPE_IRQ, 
		.status = DISABLE,
		.exec_task = task_idle,
		.poll_time = 10,
		.g_timer = &global_timer,
	},	
	
	{
		.name = "get_rpm",
		.type = TYPE_IRQ, 
		.status = DISABLE,
		.exec_task = task_get_rpm,
		.poll_time = 10,
		.g_timer = &global_timer,
    },
#endif
};
#endif
//#define EVENT_SIZE gw_get_event_list_size()

uint8_t gw_get_event_list_size(void){
	return sizeof(event_table)/sizeof(struct gw_event);
}

uint8_t gw_is_event_empty(void){
	if(gw_get_event_list_size() == 0){
		return 1;
	}
	return 0;
}

void gw_event_fifo_init(void){

	uint8_t i = 0;
	uint8_t size = EVENT_SIZE;	
	struct gw_event *p_event;
	for(; i<size; i++){
		p_event = &event_table[i%size];
		p_event->status = DISABLE;
		p_event->timestamp = 0;
	}
	global_timer.timestamp = 0;
}

void gw_reset_event_status(void){
	uint8_t i = 0;
	uint8_t size = EVENT_SIZE;	
	for(; i<size; i++){
		if(event_table[i%size].status == ENABLE){
			event_table[i%size].status = DISABLE;			
		}
	}
}

void gw_poll_event_task(void){

	uint8_t i = 0;
	uint8_t size = EVENT_SIZE;
	struct gw_event *p_event;
	GW_ENTER_CRITICAL_AREA;
	for(; i<size; i++){
		p_event = &event_table[i%size];
		if( p_event->poll_time + p_event->timestamp < p_event->g_timer->timestamp){
			p_event->timestamp = p_event->g_timer->timestamp;
			p_event->status = ENABLE;
		}
	}
	GW_EXIT_CRITICAL_AREA;	
}

void gw_execute_event_task(void){
	uint8_t i = 0;
	uint8_t size = EVENT_SIZE;
	struct gw_event *p_event;
	GW_ENTER_CRITICAL_AREA;
	for(; i<size; i++){
		p_event = &event_table[i%size];
		if(p_event->status == ENABLE && p_event->exec_task != NULL){
			p_event->exec_task();
			p_event->status = DISABLE;
		}
	}
	GW_EXIT_CRITICAL_AREA;
}

void gw_global_timer_add(void){
	timer_add(&global_timer);
}

uint8_t gw_fifo_is_empty(gw_fifo_typedef *pfifo){

	if((pfifo->rear + 1) % GW_FIFO_SIZE == pfifo->front){
		return GW_TRUE;
	}
	return GW_FALSE;
}

uint8_t gw_fifo_is_full(gw_fifo_typedef *pfifo){

	if(pfifo->rear == pfifo->front){
		return GW_TRUE;
	}
	return GW_FALSE;
}

