/*
 * NVIC_CFG.h
 *
 *  Created on: Mar 25, 2024
 *      Author: Noha
 */

#ifndef MCAL_INCLUDES_NVIC_CFG_H_
#define MCAL_INCLUDES_NVIC_CFG_H_


#define FOUR_BIT_GROUP_NO_SUBGROUB   0x05FA0300
#define THREE_BIT_GROUP_ONE_SUBGROUB 0x05FA0400
#define TWO_BIT_GROUP_TWO_SUBGROUB   0x05FA0500
#define ONE_BIT_GROUP_THREE_SUBGROUB 0x05FA0600
//close nesting
#define NO_BIT_GROUP_FOUR_SUBGROUB   0x05FA0700


#define PRIORITY_CONFIGURATION		 THREE_BIT_GROUP_ONE_SUBGROUB


#endif /* MCAL_INCLUDES_NVIC_CFG_H_ */
