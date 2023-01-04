#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_drv_systick.h"
#include "boards.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
/**
 * @brief Function for application main entry.
 */

uint32_t stack_blinky1[40] __attribute__ ((aligned (8)));
uint32_t *sp_blinky1 = &stack_blinky1[40];
void main_blinky1() {
    while (1) {
        bsp_ledOneOn();
        nrf_drv_systick_delay_ms(500);
        bsp_ledOneOff();
        nrf_drv_systick_delay_ms(500*3);
    }
}

uint32_t stack_blinky2[40] __attribute__ ((aligned (8)));
uint32_t *sp_blinky2 = &stack_blinky2[40];
void main_blinky2() {
    while (1) {
        bsp_ledTwoOn();
        nrf_drv_systick_delay_ms(500);
        bsp_ledTwoOff();
        nrf_drv_systick_delay_ms(500*3);
    }
}
int main(void)
{
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);
    
    /* Init systick driver */
    nrf_drv_systick_init();


    /* Toggle LEDs. */
    while (true)
    {
      //main_blinky1();
      main_blinky2();
    }
}