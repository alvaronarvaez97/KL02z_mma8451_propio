/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL02Z32xxx4_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"
#include "sdk_hal_gpio.h"
#include "sdk_hal_uart0.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	status_t status;
	uint8_t nuevo_byte_uart;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    (void)uart0Inicializar(115200); //iniciliaza uart

    PRINTF("utilizar teclado para encender los LEDs \r\n");
    PRINTF("R, r, para control del led rojo \r\n");
    PRINTF("B, b, para control del led azul \r\n");
    PRINTF("G, g, para control del led verde \r\n");
    gpioPutHigh(KPTB7);
while(1){
    if(uart0CuantosDatosHayEnBuffer() > 0){
    	status = uart0LeerByteDesdeBuffer(&nuevo_byte_uart);
    	if(status==kStatus_Success){
    		printf("dato: %c \r\n",nuevo_byte_uart);
    		switch(nuevo_byte_uart){
    		case 'a':
    		case 'A':
    			gpioPutToggle(KPTB10);
    			break;

    		case 'b':
    			gpioPutLow(KPTB7);
    		case 'B':
    			gpioPutHigh(KPTB7);
    		    break;

    		case 'g':
    			gpioPutValue(KPTB6, 1);
    		case 'G':
    			gpioPutValue(KPTB6, 0);
    			break;
    		}

    		}else{
    			printf("proceso fallido \r\n");
    	}
    }
    return 0;
 }
}
