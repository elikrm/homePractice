#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum i2c_state
{
    state_i2c_init,
    state_i2c_idle,
    state_i2c_deinit,
    state_i2c_lpm
} i2c_state_t;


i2c_state_t get_i2c_state();
void i2c_state_machine();


#ifdef __cplusplus
}
#endif
