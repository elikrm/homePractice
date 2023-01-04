#ifndef APP_CONFIG_H__
#define APP_CONFIG_H__
#include "util.h"
#include "m_board_device_class.h"

//deprecated in the new versioning scheme. But keep this number unmodified for backwards compatibility
#define APPLICATION_VERSION_NUM 33 /** Remember to increment this when incrementing the firmware version number, this is used by the phone to identify the version number */

#define COMPATIBLE_BOARD_DEVICE_CLASSES { BOARD_V2 }

#define INFINITE_WHITELIST_ADVERTISING  1 // Never go into idle mode when advertising with a whitelist (breaks bluetooth spec)
#define APP_WDT_ENABLED                 1

#if defined(HANDSET_SERIAL) /* Stops this from accidentally getting built */
  #define USE_SIMULATED_SYSTEM /* Set this to use all the simulated features, this includes the communication via the serial bus */
#else
/* Select the angular sensor to build with (AS5048, AS5601) Note the Handset serial implicitly chooses the simulated system */
/* #define USE_AS5048 - OLD SENSOR (DO NOT USE UNLESS WORKING WITH LEGACY HARDWARE) */
#define USE_AS5601
#endif

#define ENABLE_DEBUG_SCREENS false /**< Enables the debug screens when we hold down the mode button */

//#define ENABLE_IMU   // enables the IMU driver code, 
//#define IMU_NO_CONF                     1 // Do not configure IMU, only put it in sleep mode

#ifdef DEBUG

    #define ANGLE_MEAS_IGNORE_CORDIC_ERROR  // ignore CORDIC errors when measuring throttle trigger angle
    //#define OUTPUT_RAW_ANGLE_VALUE        // do not scale or modify raw angle value before outputting it to BLE
    //#define RUN_UNIT_TESTS                  // run unit test functions after initialization

    #ifdef RUN_UNIT_TESTS
        #undef APP_WDT_ENABLED

        #define APP_WDT_ENABLED                 0
    #endif
#else

    #define ANGLE_MEAS_IGNORE_CORDIC_ERROR  // ignore CORDIC errors when measuring throttle trigger angle
    //#define OUTPUT_RAW_ANGLE_VALUE        // do not scale or modify raw angle value before outputting it to BLE

#endif // DEBUG

#endif //APP_CONFIG_H__

