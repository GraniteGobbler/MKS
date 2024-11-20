/*

 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.

 * Copyright 2016-2017, 2024 NXP

 * All rights reserved.

 *

 * SPDX-License-Identifier: BSD-3-Clause

 */


#include "fsl_device_registers.h"

#include "fsl_debug_console.h"

#include "pin_mux.h"

#include "clock_config.h"

#include "board.h"


#include "fsl_power.h"

/*******************************************************************************

 * Definitions

 ******************************************************************************/



/*******************************************************************************

 * Prototypes

 ******************************************************************************/


/*******************************************************************************

 * Variables

 ******************************************************************************/


/*******************************************************************************

 * Code

 ******************************************************************************/
uint8_t strcmp_safe(const char *input, const char *password_stored, uint32_t pwd_len){

	uint32_t test1, test2 = 0;

	for(uint32_t i = 0; i < pwd_len; i++){

		if(input[i] == password_stored[i]){
			test1++;
		} else{
			test2++;
		}
	}

	return test2;
}

/*!

 * @brief Main function

 */

int main(void)

{

    char ch;

    uint32_t DWT1, DWT2;

    uint32_t x,y,Sum;

    /* Init board hardware. */

    /* set BOD VBAT level to 1.65V */

    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);

    /* attach main clock divide to FLEXCOMM0 (debug console) */

    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);


    BOARD_InitBootPins();

    BOARD_InitBootClocks();

    BOARD_InitDebugConsole();

#if !defined(DONT_ENABLE_FLASH_PREFETCH)

    /* enable flash prefetch for better performance */

    SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;

#endif


    PRINTF("hello world.\r\n");


    while (1)

    {

//        DWT1 = DWT ->CYCCNT;
//
//        SysTick_DelayTicks(1000U);
//
//        DWT2 = DWT ->CYCCNT;
//
//        Sum = DWT2 - DWT1;
//
//        PRINTF("hello world %d.\r\n", Sum);
        static char password_stored[20] = "12345678";
        static char input[20];
        static int8_t status;

        PRINTF("\r\nEnter password : ");
        SCANF("%s", input);
        DWT1 = DWT ->CYCCNT;

//        status = strcmp(input, password_stored);
//        status = strncmp(input, password_stored, sizeof(password_stored));
        status = strcmp_safe(input, password_stored, strlen(password_stored));
        DWT2 = DWT ->CYCCNT;
        PRINTF("\r\nPassword: %s", input);
        if(status == 0){
        	PRINTF("\r\nPassword correct");
        } else {
        	PRINTF("\r\nPassword invalid");
        }

        PRINTF("\r\nCycles for strcmp function: %d", DWT2-DWT1);
    }

}
