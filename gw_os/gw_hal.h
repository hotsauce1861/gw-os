#ifndef GW_HAL_H
#define GW_HAL_H

#if 0
#define HAL_ENABLE_IRQ 		__enable_irq
#define HAL_DISABLE_IRQ 	__disable_irq
#define HAL_SLEEP			__WFI()
#define HAL_WAKEUP			__WFE()	
#else
#define HAL_ENABLE_IRQ 		{}
#define HAL_DISABLE_IRQ 	{}
#define HAL_SLEEP			{}
#define HAL_WAKEUP			{}
#endif

#endif
