#ifndef GW_TYPE_H
#define GW_TYPE_H
#include <stdint.h>
#include <stdlib.h>

#include "gw_hal.h"

#define DISABLE         0
#define ENABLE          1

#define GW_RESULT		int8_t
#define GW_ERROR		-1
#define GW_SUCCESS		 1

#define GW_TRUE			 1
#define GW_FALSE		 0

#define DATA_TYPE       uint32_t

#define GW_ENABLE_INTERRUPTS	HAL_ENABLE_IRQ
#define GW_DISABLE_INTERRUPTS	HAL_DISABLE_IRQ

#define GW_ENTER_CRITICAL_AREA	HAL_DISABLE_IRQ
#define GW_EXIT_CRITICAL_AREA	HAL_ENABLE_IRQ

//#define GW_MALLOC((x))			malloc((x))
//#define GW_FREE((x))			free((x))

#define GW_MALLOC(x)			malloc(x)
#define GW_FREE(x)      		free(x)

#endif
