/* Board Support Package (BSP) for the EK-TM4C123GXL board */
#include <stdint.h>  /* Standard integers. WG14/N843 C99 Standard */

#include "bsp.h"
#include "miros.h"
#include "cmsis_gcc.h"
#include "nrf.h"
#include "nrf_rtc.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
//#include "portmacro_cmsis.h"

#ifndef configSYSTICK_CLOCK_HZ
    #define configCPU_CLOCK_HZ                      60000000
    #define configTICK_RATE_HZ                      250
    #define configSYSTICK_CLOCK_HZ configCPU_CLOCK_HZ
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #define portNVIC_SYSTICK_CLK_BIT    ( SysTick_CTRL_CLKSOURCE_Msk )
#else
    /* The way the SysTick is clocked is not modified in case it is not the same
    as the core. */
    #define portNVIC_SYSTICK_CLK_BIT    ( 0 )
#endif


#if configUSE_TICKLESS_IDLE == 1
    #error SysTick port for RF52 does not support tickless idle. Use RTC mode instead.
#endif /* configUSE_TICKLESS_IDLE */

#define NRF_RTC1                    ((NRF_RTC_Type*)           NRF_RTC1_BASE)
/* RTC register */
#define portNRF_RTC_REG        NRF_RTC1
/*
 * Setup the RTC time to generate the tick interrupts at the required
 * frequency.
 */
//void vPortSetupTimerInterrupt( void )
//{
//    /* Request LF clock */
//    nrf_drv_clock_lfclk_request(NULL);

//    /* Configure SysTick to interrupt at the requested rate. */
//    nrf_rtc_prescaler_set(portNRF_RTC_REG, portNRF_RTC_PRESCALER);
//    nrf_rtc_int_enable   (portNRF_RTC_REG, RTC_INTENSET_TICK_Msk);
//    nrf_rtc_task_trigger (portNRF_RTC_REG, NRF_RTC_TASK_CLEAR);
//    nrf_rtc_task_trigger (portNRF_RTC_REG, NRF_RTC_TASK_START);
//    nrf_rtc_event_enable(portNRF_RTC_REG, RTC_EVTEN_OVRFLW_Msk);

//    NVIC_SetPriority(portNRF_RTC_IRQn, configKERNEL_INTERRUPT_PRIORITY);
//    NVIC_EnableIRQ(portNRF_RTC_IRQn);
//}
static uint32_t volatile l_tickCtr;

void SysTick_Handler(void) {
    //++l_tickCtr;
    OS_tick();
    __disable_irq();
    OS_sched();
    __enable_irq();
}

void BSP_init(void) {

    /*
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    //set the SysTick interrupt priority (highest)
    NVIC_SetPriority(SysTick_IRQn, 0);
    //Configure SysTick to interrupt at the requested rate.
    //SysTick->LOAD = (configSYSTICK_CLOCK_HZ/configTICK_RATE_HZ) - 1UL;
    //SysTick->CTRL = ( portNVIC_SYSTICK_CLK_BIT | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk );

    __enable_irq();
    */
}
void OS_onStartup(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    /* set the SysTick interrupt priority (highest) */
    NVIC_SetPriority(SysTick_IRQn, 0U);
    /* Configure SysTick to interrupt at the requested rate. */
    //SysTick->LOAD = (configSYSTICK_CLOCK_HZ/configTICK_RATE_HZ) - 1UL;
    //SysTick->CTRL = ( portNVIC_SYSTICK_CLK_BIT | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk );
}
/*
uint32_t BSP_tickCtr(void) {
    uint32_t tickCtr;

    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();

    return tickCtr;
}

void BSP_delay(uint32_t ticks) {
    uint32_t start = BSP_tickCtr();
    while ((BSP_tickCtr() - start) < ticks) {
    }
}
*/

void OS_onIdle(void) 
{
//Idle thread is the best place to apply low power sleep mode
//toggle a pin up and down
  nrf_gpio_pin_toggle(3);
    __WFI(); /* stop the CPU and Wait for Interrupt */
}
void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}
