#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_drv_systick.h"
#include "boards.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "miros.h"
#include "bsp.h"
/**
 * @brief Function for application main entry.
 */

uint32_t stack_blinky1[40];
OSThread blinky1;
void main_blinky1() {
    while (1) {
        bsp_ledOneOn();
        //nrf_drv_systick_delay_ms(500);
        //BSP_delay(BSP_TICKS_PER_SEC / 2U);
        OS_delay(BSP_TICKS_PER_SEC / 2U);
        bsp_ledOneOff();
        //nrf_drv_systick_delay_ms(500*3);
        //BSP_delay(BSP_TICKS_PER_SEC / 3U);
        OS_delay(BSP_TICKS_PER_SEC / 3U);
    }
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void main_blinky2() {
    while (1) {
        bsp_ledTwoOn();
        //nrf_drv_systick_delay_ms(500);
        //BSP_delay(BSP_TICKS_PER_SEC / 4U);
        OS_delay(BSP_TICKS_PER_SEC / 4U);
        bsp_ledTwoOff();
        //nrf_drv_systick_delay_ms(500*3);
        //BSP_delay(BSP_TICKS_PER_SEC *3 / 4U);
        OS_delay(BSP_TICKS_PER_SEC *3 / 4U);
    }
}

uint32_t stack_blinky3[40];
OSThread blinky3;
void main_blinky3() {
    while (1) {
        bsp_ledThreeOn();
        //nrf_drv_systick_delay_ms(500);
        //BSP_delay(BSP_TICKS_PER_SEC / 3U);
        OS_delay(BSP_TICKS_PER_SEC / 3U);
        bsp_ledThreeOff();
        //nrf_drv_systick_delay_ms(500*3);
        //BSP_delay(BSP_TICKS_PER_SEC * 3U / 5U);
        OS_delay(BSP_TICKS_PER_SEC * 3U / 5U);
    }
}
uint32_t stack_idleThread[40];
int main(void)
{
    BSP_init();
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);
    
    /* Init systick driver */
    //nrf_drv_systick_init();

    OS_init(stack_idleThread, sizeof(stack_idleThread));

    /* fabricate Cortex-M ISR stack frame for blinky1 */
    OSThread_start(&blinky1,
                   &main_blinky1,
                   stack_blinky1, sizeof(stack_blinky1));

    /* fabricate Cortex-M ISR stack frame for blinky2 */
    OSThread_start(&blinky2,
                   &main_blinky2,
                   stack_blinky2, sizeof(stack_blinky2));
    /* fabricate Cortex-M ISR stack frame for blinky3 */
    OSThread_start(&blinky3,
                   &main_blinky3,
                   stack_blinky3, sizeof(stack_blinky3));
    //while (true)
    //{
    //  //main_blinky1();
    //  //main_blinky2();
    //}
    /* transfer control to the RTOS to run the threads */
    OS_run();
}
