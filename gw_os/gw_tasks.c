#include "gw_tasks.h"
#include "gw_list.h"
#include "gw_timer.h"
static gw_list* ptask_list = NULL;
void gw_task_list_init(void){
    ptask_list = gw_list_init();
    ptask_list->event.g_timer = &global_timer;
}

void gw_task_create(const char *name, uint8_t type, uint8_t status, uint32_t poll_time,
                    p_init_func init_func,
                    p_exec_func exec_task,
                    p_exec_args_func exec_args_task){
    uint32_t task_id = global_timer.timestamp + ptask_list->data;
    gw_list_node *pnode = gw_list_node_init(task_id);
    pnode->event.id = task_id;
    pnode->event.name = name;
    pnode->event.status = status;
    pnode->event.type = type;
    pnode->event.poll_time = poll_time;
    pnode->event.init_task = init_func;
    pnode->event.exec_task = exec_task;
    pnode->event.exec_args_task = exec_args_task;
    pnode->event.timestamp = global_timer.timestamp;
    pnode->event.g_timer = &global_timer;
    gw_list_insert_node_first(ptask_list, pnode);

}

void gw_task_void_create(const char *name, uint8_t type, uint8_t status, uint32_t poll_time,
                    p_init_func init_func,
                    p_exec_func exec_func){
    gw_task_create(name,type,status,poll_time,init_func,exec_func, NULL);
}

void gw_task_args_create(const char *name, uint8_t type, uint8_t status, uint32_t poll_time,
                         p_init_func init_func,
                         p_exec_args_func exec_args_func){

    gw_task_create(name,type,status,poll_time,init_func, NULL, exec_args_func);
}

void gw_task_init_process(void){
    gw_list* plist_tmp = NULL;
    struct gw_event *p_event = NULL;
    if(ptask_list->data < 1){
        return;
    }
    //GW_ENTER_CRITICAL_AREA;
    plist_tmp = ptask_list->next;
    while(plist_tmp != NULL){
        p_event = &plist_tmp->event;
        if(p_event->init_task != NULL){
            p_event->init_task();
        }
        plist_tmp = plist_tmp->next;
    //GW_EXIT_CRITICAL_AREA;
    }
}

void gw_task_process(void){
    gw_list* plist_tmp = NULL;
    struct gw_event *p_event = NULL;
    if(ptask_list->data < 1){
        return;
    }
    //GW_ENTER_CRITICAL_AREA;
    plist_tmp = ptask_list->next;
    while(plist_tmp != NULL){
        p_event = &plist_tmp->event;
        if(p_event->status == GW_ENABLE ){
            if( p_event->exec_task != NULL){
                p_event->exec_task();
            }
            if(p_event->exec_args_task != NULL){
                p_event->exec_args_task((struct gw_event *)p_event);
            }
            p_event->status = GW_DISABLE;
        }
        plist_tmp = plist_tmp->next;
    //GW_EXIT_CRITICAL_AREA;
    }
}

void gw_task_schedule(void){
    gw_list* plist_tmp = NULL;
    struct gw_event *p_event = NULL;
    if(ptask_list->data < 1){
        return;
    }
    GW_ENTER_CRITICAL_AREA;
    plist_tmp = ptask_list->next;
    while(plist_tmp != NULL){
        p_event = &plist_tmp->event;
        if(p_event->poll_time + p_event->timestamp < p_event->g_timer->timestamp ){
            p_event->timestamp = p_event->g_timer->timestamp;
            p_event->status = GW_ENABLE;
        }
        plist_tmp = plist_tmp->next;
    }
    GW_EXIT_CRITICAL_AREA;
}
