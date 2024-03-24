/*
 * Systick.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Noha
 */

#ifndef MCAL_INCLUDES_SYSTICK_H_
#define MCAL_INCLUDES_SYSTICK_H_

#include"stdio.h"
#include"../../LIB/std_types.h"
#include"systick_cfg.h"

#define STK_MODE_PERIODIC 1
#define STK_MODE_SINGLE   0



typedef void (*STK_CB_t) (void);

u8 MSTK_init(void);
u8 MSTK_init(u8 copy_STKmode);
u8 MSTK_stop(void);
u8 MSTK_setTime_ms(u16 copy_STKtime);
u8 MSTK_IsExpired(u8* Add_STKisExpired);
u8 MSTK_IsExpired(u8* Add_STKisExpired);
void MSTK_SetCallBack(STK_CB_t STK_CB);


#endif /* MCAL_INCLUDES_SYSTICK_H_ */
