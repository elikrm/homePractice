#include "i2c.h"

static i2c_state_t tetrapack_i2c_state = state_i2c_init; //read only

i2c_state_t get_i2c_state()
{
    return tetrapack_i2c_state;
}

void i2c_state_machine()
{
    static i2c_state_t i2c_state = state_i2c_init;

    switch (i2c_state)
    {
    case state_i2c_init:
        set_gpio_ouput(VDDSW_CTRL);
        ng_gpio_clear(VDDSW_CTRL); // this line is inverted
        wait_us(200); //wait for voltage to get stabilised. todo Is this enough?
        i2c_initialise();

        i2c_state = state_i2c_idle;
        break;

    case state_i2c_idle:
        //other modules can use i2c read/write functions
        if (get_lpm_state() == state_lpm_prepare_to_sleep || get_lpm_state() == state_lpm_sleep) //second condition is needed for going back to sleep from button wake up and tamper detect
        {
            i2c_state = state_i2c_deinit;
        }
        break;

    case state_i2c_deinit:
        if (get_display_state() != state_display_lpm) // all i2c dependent modules must be deinitialised first
        {
            break;
        }

        i2c_deinitialise();
        ng_gpio_set(VDDSW_CTRL); // this line is inverted
        ng_gpio_set_default_mode(VDDSW_CTRL);

        i2c_state = state_i2c_lpm;
        break;

    case state_i2c_lpm:
        if (get_lpm_state() == state_lpm_prepare_to_meter_wakeup || get_lpm_state() == state_lpm_prepare_to_button_wakeup
                || get_lpm_state() == state_lpm_prepare_to_tamper_detect_wakeup) // free run here until lpm wakeup or powered mode
        {
            i2c_state = state_i2c_init;
        }
        break;

    default:
        break;
    }

    g_i2c_state = i2c_state;
}
