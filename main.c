/**
************************************************************************************************
 * @file    : main.c
 * @brief   : none
 * @details : one
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


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "gw_list.h"
#include "gw_timer.h"
#include "gw_fifo.h"
#include "gw_tasks.h"
#include "gw_msgs.h"

pthread_mutex_t mutex_timer;
pthread_t pthread_timer;
gw_msg_fifo_t msg_fifo;

#define TASK_ID_04  4
#define TASK_ID_05  5
#define TASK_ID_06  6

void task_01(void){
    printf("task_01\r\n");
}

void task_02(void){
    printf("    task_02\r\n");
}

void task_03(void){
    printf("        task_03\r\n");
}

void task_04(void* args){
    struct gw_event *pev = (struct gw_event *)args;
    gw_msg_fifo_t * const pmsg_fifo = &msg_fifo;
    gw_msg_t msg;
    //printf("        %s is %d\n",pev->name,pev->id);
    pthread_mutex_lock(&mutex_timer);
    if(gw_msg_receive(pev->id, pmsg_fifo, &msg) == GW_TRUE){
        /**
            TODO
        */               
        printf("%016d: name:[%s] id:[%d] msg:[%s]\n", pev->g_timer->timestamp,
               pev->name, pev->id,(uint8_t*)msg.pstr);
    }
    pev->msg.pstr = (const char*)"MSG from task_04:Hello I am task 04";
    if(gw_msg_send_msg(TASK_ID_05, pmsg_fifo, &pev->msg) == GW_TRUE){
        /**
            TODO
        */
    }
    pthread_mutex_unlock(&mutex_timer);
}

void task_05(void* args){
    struct gw_event *pev = (struct gw_event *)args;
    gw_msg_fifo_t * const pmsg_fifo = &msg_fifo;
    gw_msg_t msg;
    //printf("        %s is %d\n",pev->name,pev->id);
    pthread_mutex_lock(&mutex_timer);
    if(gw_msg_receive(pev->id, pmsg_fifo, &msg) == GW_TRUE){
        /**
            TODO
        */
        printf("%016d: name:[%s] id:[%d] msg:[%s]\n", pev->g_timer->timestamp,
               pev->name, pev->id,(uint8_t*)msg.pstr);
    }
    pev->msg.pstr = (const char*)"MSG from task_05:Hello I am task 05";
    //if(gw_msg_send_msg(TASK_ID_06, pmsg_fifo, &pev->msg) == GW_TRUE){
      if(gw_msg_send_str(TASK_ID_06, pmsg_fifo,
            (const char*)"MSG from task_05:Hello I am task 05") == GW_TRUE){
        /**
            TODO
        */
    }
    pthread_mutex_unlock(&mutex_timer);   
}

void task_06(void* args){
    struct gw_event *pev = (struct gw_event *)args;
    gw_msg_fifo_t * const pmsg_fifo = &msg_fifo;
    gw_msg_t msg;
    //printf("        %s is %d\n",pev->name,pev->id);
    pthread_mutex_lock(&mutex_timer);
    if(gw_msg_receive(pev->id, pmsg_fifo, &msg) == GW_TRUE){
        /**
            TODO
        */        
        printf("%016d: name:[%s] id:[%d] msg:[%s]\n", pev->g_timer->timestamp,
               pev->name, pev->id,(uint8_t*)msg.pstr);
    }
    pev->msg.pstr = (const char*)"MSG from task_06:Hello I am task 06";
    if(gw_msg_send_msg(TASK_ID_04, pmsg_fifo, &pev->msg) == GW_TRUE){
        /**
            TODO
        */
    }
    pthread_mutex_unlock(&mutex_timer);    
}


struct gw_event event_table[EVENT_SIZE] =
{
    {
        .name = "event1",
        .type = TYPE_IRQ,
        .status = ENABLE,
        .exec_task = task_01,
        .poll_time = 5000,
        .g_timer = &global_timer,
    },

    {
        .name = "event2",
        .type = TYPE_IRQ,
        .status = DISABLE,
        .exec_task = task_02,
        .poll_time = 1000,
        .g_timer = &global_timer,
    },

    {
        .name = "get_rpm",
        .type = TYPE_IRQ,
        .status = DISABLE,
        .exec_task = task_03,
        .poll_time = 1000,
        .g_timer = &global_timer,
    },
};

void* pthread_timer_handler(void* args);
void* pthread_timer_handler(void* args){

    while(1){
        pthread_mutex_lock(&mutex_timer);
#if 0
        gw_poll_event_task();
#else
        gw_task_schedule();
#endif
        gw_global_timer_add();
        pthread_mutex_unlock(&mutex_timer);
        usleep(1000);
    }
}

int main()
{
    int ret = 0;
    pthread_mutex_init(&mutex_timer, NULL);
    ret = pthread_create(&pthread_timer,NULL,pthread_timer_handler,NULL);
#if 0
    timer_base_config();
    gw_event_fifo_init();
#else
    gw_task_list_init();
    gw_msg_fifo_init(&msg_fifo);
/*
    gw_task_create("task01",1,TYPE_IRQ, ENABLE,10000,0,
                   task_01, task_01, NULL);
    gw_task_create("task02",2,TYPE_IRQ, ENABLE,50000,0,
                   task_02, task_02, NULL);
    gw_task_create("task03",3,TYPE_IRQ, ENABLE,10000,0,
                   task_03, task_03, NULL);
*/

    gw_task_args_create("task04",TASK_ID_04, TYPE_POLL, ENABLE, 2000,
                        task_01, task_04);
    gw_task_args_create("task05",TASK_ID_05, TYPE_POLL, ENABLE, 2000,
                        task_01, task_05);
    gw_task_args_create("task06",TASK_ID_06, TYPE_POLL, ENABLE, 2000,
                        task_01, task_06);
    gw_task_init_process();
#endif
    printf("\r\ngw_os version 1.0\r\n");
    while(1){
#if 0
        gw_execute_event_task();
#else
        gw_task_process();
#endif
    }
}
