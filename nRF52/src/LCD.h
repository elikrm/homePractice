#ifndef LCD_H__
#define LCD_H__
#include <stdint.h>
#include <stdbool.h>

void lcd_init(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);

#endif