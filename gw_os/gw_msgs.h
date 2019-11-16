/**
************************************************************************************************
 * @file    : gw_msgs.h
 * @brief   :
 * @details :
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

#ifndef GW_MSGS_H
#define GW_MSGS_H

#define MSGS_FIFO_SIZE 10
#include "gw_type.h"

struct gw_msg_mod{
    DATA_TYPE task_id;
	void* pstr;
};
typedef struct gw_msg_mod gw_msg_t;

struct gw_msg_fifo_mod{
	uint8_t size;
    gw_msg_t msgs[MSGS_FIFO_SIZE];
	uint8_t front;
	uint8_t rear;
};

typedef struct gw_msg_fifo_mod gw_msg_fifo_t;

void gw_msg_fifo_init(gw_msg_fifo_t * const pfifo);
void gw_msg_fifo_clear(gw_msg_fifo_t * const pfifo);
void gw_msg_init(gw_msg_t* const pmsg, DATA_TYPE id);
GW_RESULT gw_msg_fifo_is_full(gw_msg_fifo_t* const pfifo);
GW_RESULT gw_msg_fifo_is_empty(gw_msg_fifo_t* const pfifo);
GW_RESULT gw_msg_fifo_enqueue(gw_msg_fifo_t* const pfifo,
                                gw_msg_t* const pmsg);

GW_RESULT gw_msg_fifo_dequeue(gw_msg_fifo_t* const pfifo,
                                gw_msg_t* const pmsg);

GW_RESULT gw_msg_send_msg(uint32_t taskid, gw_msg_fifo_t* const pfifo,
                      gw_msg_t* const pmsg);

GW_RESULT gw_msg_send_str(uint32_t taskid, gw_msg_fifo_t* const pfifo,
                      const char *pstr);

GW_RESULT gw_msg_receive(uint32_t taskid, gw_msg_fifo_t* const pfifo,
                         gw_msg_t* const pmsg);

#endif
