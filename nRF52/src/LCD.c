#include "LCD.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#define LCD_RS_PIN   3
#define LCD_EN_PIN   4
#define LCD_D4_PIN   28
#define LCD_D5_PIN   29
#define LCD_D6_PIN   30
#define LCD_D7_PIN   31

#define LCD_NUM_ROWS     2
#define LCD_NUM_COLUMNS  16
void lcd_pin_init(void)
{
    nrf_gpio_cfg_output(LCD_RS_PIN);
    nrf_gpio_cfg_output(LCD_EN_PIN);
    nrf_gpio_cfg_output(LCD_D4_PIN);
    nrf_gpio_cfg_output(LCD_D5_PIN);
    nrf_gpio_cfg_output(LCD_D6_PIN);
    nrf_gpio_cfg_output(LCD_D7_PIN);
}

void lcd_send_nibble(uint8_t data)
{
    nrf_gpio_pin_write(LCD_D4_PIN, (data & 0x01) ? 1 : 0);
    nrf_gpio_pin_write(LCD_D5_PIN, (data & 0x02) ? 1 : 0);
    nrf_gpio_pin_write(LCD_D6_PIN, (data & 0x04) ? 1 : 0);
    nrf_gpio_pin_write(LCD_D7_PIN, (data & 0x08) ? 1 : 0);
}

void lcd_send_byte(uint8_t data, bool is_data)
{
    nrf_gpio_pin_write(LCD_RS_PIN, is_data ? 1 : 0);

    // Send the high nibble
    lcd_send_nibble(data >> 4);
    nrf_gpio_pin_set(LCD_EN_PIN);
    nrf_delay_us(1);
    nrf_gpio_pin_clear(LCD_EN_PIN);
    nrf_delay_us(100);

    // Send the low nibble
    lcd_send_nibble(data);
    nrf_gpio_pin_set(LCD_EN_PIN);
    nrf_delay_us(1);
    nrf_gpio_pin_clear(LCD_EN_PIN);
    nrf_delay_us(100);
}

void lcd_init(void)
{
    lcd_pin_init();
    nrf_delay_ms(50);

    // Initialization sequence
    lcd_send_nibble(0x03);
    nrf_gpio_pin_set(LCD_EN_PIN);
    nrf_delay_us(1);
    nrf_gpio_pin_clear(LCD_EN_PIN);
    nrf_delay_ms(5);

    lcd_send_nibble(0x03);
    nrf_gpio_pin_set(LCD_EN_PIN);
    nrf_delay_us(1);
    nrf_gpio_pin_clear(LCD_EN_PIN);
    nrf_delay_us(100);

    lcd_send_nibble(0x03);
    nrf_gpio_pin_set(LCD_EN_PIN);
    nrf_delay_us(1);
    nrf_gpio_pin_clear(LCD_EN_PIN);
    nrf_delay_us(100);

    lcd_send_nibble(0x02);
    nrf_gpio_pin_set(LCD_EN_PIN);
    nrf_delay_us(1);
    nrf_gpio_pin_clear(LCD_EN_PIN);
    nrf_delay_us(100);

    // Function Set: 2 lines, 5x8 font
    lcd_send_byte(0x28, false);
    nrf_delay_us(40);

    // Display ON/OFF Control: Display ON, Cursor OFF, Blink OFF
    lcd_send_byte(0x0C, false);
    nrf_delay_us(40);

    // Clear Display
    lcd_send_byte(0x01, false);
    nrf_delay_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address = 0x80;
    if (row == 1)
        address |= 0x40;
    address += col;

    lcd_send_byte(address, false);
    nrf_delay_us(40);
}

void lcd_print(const char *str)
{
    while (*str != '\0')
    {
        lcd_send_byte(*str, true);
        str++;
    }
}