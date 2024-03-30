/*
 * Systick.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Noha
 */


#include"../INCLUDES/Systick.h"


/*Counter enable*/
#define STK_CTRL_ENABLE    0
/*SysTick exception request enable*/
#define STK_CTRL_TICKINT   1
/*Clock source selection*/
#define STK_CTRL_CLKSOURCE 2
/*Returns 1 if timer counted to 0 since last time this was read.*/
#define STK_CTRL_COUNTFLAG 16


#define STK_CTRL_ENABLE_MASK    0x1
#define STK_CTRL_TICKINT_MASK   0x3
#define STK_CTRL_CLKSOURCE_MASK 0x4
#define STK_CTRL_COUNTFLAG_MASK 0x10000


#define STKclk_MASK 0xFFFFFFFB

#define STK_LOAD_CLR_MASK       0x00000000


typedef struct
{
    u32 STK_CTRL;
    u32 STK_LOAD;
    u32 STK_VAL ;
    u32 STK_CALIB;
}STK_t;



static volatile STK_t* const STK=(volatile STK_t* const) (0xE000E010);
static STK_CB_t AppCbF;
u8 G_STKmode=0;
f32 G_STK_freq=0;

u8 MSTK_init(u8 copy_STKmode)
{
	u8 error_status=STATUS_NOK;
	#if STK_CLK==STKclk_AHB
	/*systick clk source*/
	STK->STK_CTRL&=STKclk_MASK;
	STK->STK_CTRL|=STKclk_AHB;
	G_STK_freq=STK_CLKFREQ;
    #elif STK_CLK==STKclk_AHB8
    /*systick clk source*/
    STK->STK_CTRL&=STKclk_MASK;
    STK->STK_CTRL|=STKclk_AHB8;
    G_STK_freq=STK_CLKFREQ/8;
    #endif

    if(copy_STKmode>STK_MODE_PERIODIC)
	{
		error_status=INVALID_MODE;
	}
    else
    {
    	G_STKmode=copy_STKmode;
    	error_status=STATUS_OK;
    }
	//enable counter by setting bit 0 and raise COUNTFLAG
    //STK->STK_CTRL|=STK_CTRL_ENABLE_MASK;

    return error_status;

}
//asynchronous func as interrupt is enabled
void MSTK_start(void)
{
    //enable SYSTICK to detect COUNTFLAG
    STK->STK_CTRL|=STK_CTRL_TICKINT_MASK;
}

void MSTK_stop(void)
{
    //disable counter
    STK->STK_CTRL&=~(STK_CTRL_ENABLE_MASK);
    //disable SYSTICK
    STK->STK_CTRL&=~(STK_CTRL_TICKINT_MASK);
}
u8 MSTK_IsExpired(u8* Add_STKisExpired)
{
    u8 error_status=STATUS_NOK;
    if(Add_STKisExpired!=NULL)
    {
    	* Add_STKisExpired=(STK->STK_CTRL>>STK_CTRL_COUNTFLAG)&1;
    	error_status=STATUS_OK;
    }
    else
    {
    	error_status=STATUS_NOK;
    }

    return error_status;
}
void MSTK_setTime_ms(u16 copy_STKtime)
{
    u32 Loc_numOfTicks;
    Loc_numOfTicks=copy_STKtime/(1000/G_STK_freq);
    STK->STK_LOAD&=STK_LOAD_CLR_MASK;
    STK->STK_LOAD|=Loc_numOfTicks;
}

void MSTK_SetCallBack(STK_CB_t STK_CB)
{
    if(STK_CB!=NULL)
    {
        AppCbF=STK_CB;
    }
    else
    {
        //do nothing
    }

}

void SysTick_Handler(void)
{
    if(AppCbF)
    {
    	AppCbF();

    	if (G_STKmode==STK_MODE_SINGLE)
    	{
    	    //clear reload value and  count enable bits
    	    STK->STK_CTRL&=~(STK_CTRL_ENABLE_MASK);
            STK->STK_LOAD&=STK_LOAD_CLR_MASK;
   	    }
    	else
    	{
    		//do nothing
    	}
    }

    else
    {
        //do nothing
    }

}

