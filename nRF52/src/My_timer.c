/*#include "nrf.h"
#include "nrf_delay.h"

void My_timer_init(void) 
{
    // Initialize the timer
    NRF_TIMER_Type * p_timer = NRF_TIMER0;
   
    // Match Value = Timer Clock Frequency * Desired Delay (in seconds) / Prescaler
    // Match Value = 16,000,000 * 1 / (2 power PRESCALER) = 16000000

    // Prescaler = Input Clock Frequency / Desired Timer Clock Frequency
    // Prescaler = 16 MHz / 1 MHz = 16
    
    p_timer->MODE      = TIMER_MODE_MODE_Timer; // Timer mode
    p_timer->PRESCALER = 4; // Prescaler: 2^4 = 16 (to achieve 1 MHz timer clock)
    p_timer->BITMODE   = TIMER_BITMODE_BITMODE_32Bit; // 32-bit mode

    // Set the compare value for a 1-second delay
    uint32_t timer_clock_frequency = 16000000; // 16 MHz
    uint32_t desired_delay_sec = 1; // 1 second
    uint32_t match_value = (timer_clock_frequency * desired_delay_sec) / (1 << p_timer->PRESCALER);
    p_timer->CC[0] = match_value;

    // Configure and enable the compare interrupt
    p_timer->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;

    // Enable the timer
    p_timer->TASKS_START = 1;

    while (1) 
    {
        // Wait for the timer to reach the compare value
        while (!p_timer->EVENTS_COMPARE[0]);

        // Clear the compare event
        p_timer->EVENTS_COMPARE[0] = 0;

        // Timer has reached the compare value, take necessary actions here
        // Add break statement to exit the loop
        break;
    }
}

uint32_t Clock_Alarm_curr_time;

uint32_t Clock_Alarm_get_curr_time(void) 
{
    NRF_TIMER_Type * p_timer = NRF_TIMER0;
    uint32_t temp;
    
    // Disable interrupts
    __disable_irq();
    p_timer->TASKS_CAPTURE[0];
    temp = p_timer->CC[0];
    //temp = Clock_Alarm_curr_time;
    
    // Re-enable interrupts
    __enable_irq();
    
    return temp;
}*/


