#include "gw_msgs.h"



void gw_msg_fifo_init(gw_msg_fifo_t * const pfifo){
	pfifo->size = MSGS_FIFO_SIZE;
	pfifo->front = pfifo->rear = 0;
}

void gw_msg_fifo_clear(gw_msg_fifo_t * const pfifo){
	pfifo->front = pfifo->rear = 0;
}

GW_RESULT gw_msg_fifo_is_full(gw_msg_fifo_t* const pfifo){

	if( (pfifo->rear + 1) %pfifo->size ==  pfifo->front){
		return GW_TRUE;
	}
	return GW_FALSE;
}

GW_RESULT gw_msg_fifo_is_empty(gw_msg_fifo_t* const pfifo){
	if(pfifo->front == pfifo->rear){
		return GW_TRUE;
	}
	return GW_FALSE;
}

GW_RESULT gw_msg_fifo_enqueue(gw_msg_fifo_t* const pfifo,
                                gw_msg_t* const pmsg){
	//判断队列非满可入队
	if(gw_msg_fifo_is_full(pfifo) == GW_TRUE){
		return GW_ERROR;
	}
	pfifo->msgs[++pfifo->rear%pfifo->size] = *pmsg;
	return GW_SUCCESS;
}

GW_RESULT gw_msg_fifo_dequeue(gw_msg_fifo_t* const pfifo,
                                gw_msg_t* const pmsg){

	//判断队列非空可出队
	if(gw_msg_fifo_is_empty(pfifo) == GW_TRUE){
		return GW_ERROR;
	}
	*pmsg = pfifo->msgs[pfifo->front++ % pfifo->size];
	return GW_SUCCESS;
}

GW_RESULT gw_msg_send(uint32_t taskid, gw_msg_fifo_t* const pfifo,
                      gw_msg_t* const pmsg){

    if(gw_msg_fifo_is_full(pfifo) == GW_TRUE){
        return GW_ERROR;
    }
    pmsg->pstr = taskid;
    gw_msg_fifo_enqueue(pfifo, pmsg);

    return GW_SUCCESS;
}

GW_RESULT gw_msg_receive(uint32_t taskid, gw_msg_fifo_t* const pfifo,
                         gw_msg_t* const pmsg){

    gw_msg_t* pmsg_tmp = NULL;
    uint8_t front = 0;
    if(gw_msg_fifo_is_empty(pfifo) == GW_TRUE){
        return GW_ERROR;
    }
    front = pfifo->front%pfifo->size;

    pmsg_tmp = &(pfifo->msgs[front]);
    if(pmsg_tmp->task_id == taskid){
        *pmsg = pfifo->msgs[front];
    }
    return GW_SUCCESS;
}

