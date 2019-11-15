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
gw_msg_t msg_fifo;

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
    printf("        %s is %d\n",pev->name,pev->id);

    if(gw_msg_receive(pev->id, pmsg_fifo, &pev->msg) == GW_TRUE){

    }
    if(gw_msg_send(pev->id, pmsg_fifo, &pev->msg) == GW_TRUE){

    }
}

void task_05(void* args){
    struct gw_event *pevent = (struct gw_event *)args;
    printf("    %s is %d\n",pevent->name,pevent->id);

    if(gw_msg_fifo_is_full(&msg_fifo) ==  GW_FALSE){

    }

}

void task_06(void* args){
    struct gw_event *pevent = (struct gw_event *)args;
    printf("%s is %d\n",pevent->name,pevent->id);

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
    gw_task_create("task01",TYPE_IRQ, ENABLE,10000,
                   task_01, task_01, NULL);
    gw_task_create("task02",TYPE_IRQ, ENABLE,50000,
                   task_02, task_02, NULL);
    gw_task_create("task03",TYPE_IRQ, ENABLE,10000,
                   task_03, task_03, NULL);
    gw_task_args_create("task04",TYPE_POLL, ENABLE, 1000,
                        task_01, task_04);
    gw_task_args_create("task05",TYPE_POLL, ENABLE, 2000,
                        task_01, task_05);
    sleep(10);
    gw_task_args_create("task06",TYPE_POLL, ENABLE, 4000,
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
