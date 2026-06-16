/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#include <cr_section_macros.h>
#include "target.h"
#include "hal_gpio.h"
#include "hal_systick.h"
#include "soft_timers.h"
#include <stdio.h>
// TODO: insert other include files here

// TODO: insert other definitions and declarations here
//#define USR_DEBUG

#define GPIO_LED_RED         ((hal_gpio_pin_t){1u, 2u})
#define GPIO_LED_BLUE         ((hal_gpio_pin_t){1u, 1u})
#define GPIO_LED_GREEN         ((hal_gpio_pin_t){1u, 0u})
#define GPIO_BUTTON         ((hal_gpio_pin_t){0u, 4u})

void toggle_led(void)
{
	hal_gpio_pin_toggle(GPIO_LED_RED);
}

int main(void) {

	#if defined(USR_DEBUG)
    printf("Inicializando sistema en modo desarrollo...\n");
	#endif
    //hal_systick_init(CLK_HZ, 1);
    soft_timers_init(CLK_HZ, 1000);
    soft_timers_process_on_tick(1);
	hal_gpio_level_t button_state, button_state_prev;
	hal_gpio_pin_configure(GPIO_LED_RED, HAL_GPIO_MODE_OUTPUT_PUSHPULL);
	hal_gpio_pin_configure(GPIO_LED_BLUE, HAL_GPIO_MODE_OUTPUT_PUSHPULL);
	hal_gpio_pin_configure(GPIO_LED_GREEN, HAL_GPIO_MODE_OUTPUT_PUSHPULL);
	hal_gpio_pin_configure(GPIO_BUTTON, HAL_GPIO_MODE_INPUT_PULLUP);

	hal_gpio_pin_write(GPIO_LED_RED, 1);
	hal_gpio_pin_write(GPIO_LED_BLUE, 1);
	hal_gpio_pin_write(GPIO_LED_GREEN, 1);
	hal_gpio_pin_read(GPIO_BUTTON, &button_state);
	button_state_prev = button_state;
    // TODO: insert code here

    while(1) {
    	static uint8_t i=0;
    	hal_gpio_pin_read(GPIO_BUTTON, &button_state);
    	if(button_state_prev && !button_state)
    	{
    		i++;
    		if(i>4)
    		{
    			i=0;
    		}
			#if defined(USR_DEBUG)
    		printf("¡BOTON PRESIONADO!, i=%d\n",i);
			#endif
    	}
    	button_state_prev = button_state;
    	switch(i)
		{
    		case 0:
    			hal_gpio_pin_write(GPIO_LED_RED, 0);
				hal_gpio_pin_write(GPIO_LED_BLUE, 1);
				hal_gpio_pin_write(GPIO_LED_GREEN, 1);
				break;
    		case 1:
    			hal_gpio_pin_write(GPIO_LED_RED, 1);
    			hal_gpio_pin_write(GPIO_LED_BLUE, 1);
    			hal_gpio_pin_write(GPIO_LED_GREEN, 0);
    			break;
    		case 2:
    			hal_gpio_pin_write(GPIO_LED_RED, 1);
    			hal_gpio_pin_write(GPIO_LED_BLUE, 0);
    			hal_gpio_pin_write(GPIO_LED_GREEN, 1);
    			break;
    		case 3:
    			hal_gpio_pin_write(GPIO_LED_RED, 0);
				hal_gpio_pin_write(GPIO_LED_BLUE, 1);
				hal_gpio_pin_write(GPIO_LED_GREEN, 1);
				hal_systick_delay_ms(1000);
				hal_gpio_pin_write(GPIO_LED_RED, 1);
				hal_systick_delay_ms(1000);
				break;
    		case 4:
    			if(!soft_timer_is_running(1))
    			{
    				soft_timer_start(1, 100, &toggle_led);
    			}
    			break;
		}
    	//soft_timers_process();
    }
    return 0 ;
}
