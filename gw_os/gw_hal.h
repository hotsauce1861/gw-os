/**
************************************************************************************************
 * @file    : gw_hal.h
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
