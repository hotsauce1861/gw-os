#ifndef GW_TASKS_H
#define GW_TASKS_H
#include "gw_event.h"

void gw_task_list_init(void);
void gw_task_create(const char *name, uint8_t type, uint8_t status, uint32_t poll_time,
                    p_init_func init_func,
                    p_exec_func exec_task,
                    p_exec_args_func exec_args_task);
void gw_task_void_create(const char *name, uint8_t type, uint8_t status, uint32_t poll_time,
                    p_init_func init_func,
                    p_exec_func exec_func);

void gw_task_args_create(const char *name, uint8_t type, uint8_t status, uint32_t poll_time,
                         p_init_func init_func,
                         p_exec_args_func exec_func);

void gw_task_schedule(void);
void gw_task_process(void);
void gw_task_init_process(void);

#endif

