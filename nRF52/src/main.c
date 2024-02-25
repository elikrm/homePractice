#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_drv_systick.h"
#include "boards.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "LCD.h"
//#include "My_timer.h"

#include <stdbool.h>

#define UART_TX_PIN     2
#define UART_RX_PIN     18
#define BAUD_RATE       9600


#include "nrf_gpio.h"
#include "nrf.h"
#include <nrf_drv_clock.h>
#include <nrf_drv_rtc.h>





void uart_init()
{
    // Configure UART pins
    NRF_UART0->PSELTXD = UART_TX_PIN;
    NRF_UART0->PSELRXD = UART_RX_PIN;
    
    // Set baud rate and enable UART
    NRF_UART0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud9600;
    NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Enabled;
    NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;
}

void uart_print(const char *str)
{
    while (*str != '\0')
    {
        NRF_UART0->TXD = *str;
        while (NRF_UART0->EVENTS_TXDRDY != 1);
        NRF_UART0->EVENTS_TXDRDY = 0;
        str++;
    }
}


// Function to initialize the RTC peripheral
void rtc_config(void)
{
    // Configure the RTC
    NRF_RTC1->PRESCALER = 0;  // No prescaling
    NRF_RTC1->EVTENSET = RTC_EVTENSET_COMPARE0_Msk;  // Enable COMPARE0 event
    NRF_RTC1->INTENSET = RTC_INTENSET_COMPARE0_Msk;  // Enable COMPARE0 interrupt

    // Start the RTC
    NRF_RTC1->TASKS_START = 1;
}

// Function to display the current time (for example, using logs)
uint32_t display_time(uint32_t time)
{
    //NRF_LOG_INFO("Current time: %u", time);
    return time;
}
uint32_t curr_time;
char buffer[20];  // Assuming a 32-bit integer won't exceed 20 digits
// RTC1 interrupt handler
void RTC1_IRQHandler(void)
{
    // Check if the COMPARE0 event triggered the interrupt
    if (NRF_RTC1->EVENTS_COMPARE[0] != 0)
    {
        NRF_RTC1->EVENTS_COMPARE[0] = 0;  // Clear the event
        NRF_RTC1->TASKS_CLEAR = 1;
        //uint32_t current_time = NRF_RTC1->COUNTER;  // Read the current time
        //curr_time = display_time(current_time);  // Display the time (replace this with your display logic)
        curr_time++;

    }
}

int main(void)
{
    //My_timer_init();
    
    // Initialize the clock
    nrf_drv_clock_init();
    nrf_drv_clock_lfclk_request(NULL);

    // Wait for the clock to be ready
    while (!nrf_drv_clock_lfclk_is_running())
    {
        // Wait for the clock
    }

    // Initialize the logging module
    NRF_LOG_INIT(NULL);
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    // Initialize the RTC
    rtc_config();

    // Set a periodic timer for every second (adjust as needed)
    NRF_RTC1->CC[0] = 32768;  // 1 Hz

    // Enable the RTC interrupt
    NVIC_EnableIRQ(RTC1_IRQn);

    uart_init();
    lcd_init();

    lcd_set_cursor(1, 0);
    lcd_print("I am Happy");

    while (true)
    {
        lcd_set_cursor(0, 0);
        sprintf(buffer, "%lu", curr_time);  // Convert uint32_t to string
        lcd_print(buffer);  // Call your lcd_print function

        uart_print("Hello, world!\r\n");
        nrf_delay_ms(1000); // Add a delay to control the printing frequency
        //curr_time = Clock_Alarm_get_curr_time();
        // Enter low-power mode or do other tasks as needed
        __WFE();
    }
}
