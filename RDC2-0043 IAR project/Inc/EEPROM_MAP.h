/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#ifndef __EEPROM_MAP_H
#define __EEPROM_MAP_H



#define       EEPROM_PAGE_SIZE             32 //размер станицы EEPROM


#define       CONFIG_START_ADDRESS         (1 * EEPROM_PAGE_SIZE)

#define       MODE_SIZE                    1
#define       ACTIVE_LEVEL_SIZE            1
#define       THERMISTOR_R_NOMINAL_SIZE    4
#define       THERMISTOR_B_CONSTANT_SIZE   2
#define       TEMP_DELTA_LOW_SIZE          2
#define       TEMP_DELTA_HIGH_SIZE         TEMP_DELTA_LOW_SIZE
#define       TEMP_NOMINAL_SIZE            2
#define       PROTECTION_ACTIVE_SIZE       1
#define       MAXIMUM_ON_TIME_SIZE         2

#define       CONFIG_SIZE                  (MODE_SIZE + ACTIVE_LEVEL_SIZE + THERMISTOR_R_NOMINAL_SIZE + \
                                            THERMISTOR_B_CONSTANT_SIZE + TEMP_DELTA_LOW_SIZE + \
                                            TEMP_DELTA_HIGH_SIZE + TEMP_NOMINAL_SIZE + PROTECTION_ACTIVE_SIZE + MAXIMUM_ON_TIME_SIZE)


#define       MODE_OFFSET                  0
#define       ACTIVE_LEVEL_OFFSET          (MODE_OFFSET + MODE_SIZE)
#define       THERMISTOR_R_NOMINAL_OFFSET  (ACTIVE_LEVEL_OFFSET + ACTIVE_LEVEL_SIZE)
#define       THERMISTOR_B_CONSTANT_OFFSET (THERMISTOR_R_NOMINAL_OFFSET + THERMISTOR_R_NOMINAL_SIZE)
#define       TEMP_DELTA_LOW_OFFSET        (THERMISTOR_B_CONSTANT_OFFSET + THERMISTOR_B_CONSTANT_SIZE)
#define       TEMP_DELTA_HIGH_OFFSET       (TEMP_DELTA_LOW_OFFSET + TEMP_DELTA_LOW_SIZE)
#define       TEMP_NOMINAL_OFFSET          (TEMP_DELTA_HIGH_OFFSET + TEMP_DELTA_HIGH_SIZE)
#define       PROTECTION_ACTIVE_OFFSET     (TEMP_NOMINAL_OFFSET + TEMP_NOMINAL_SIZE)
#define       MAXIMUM_ON_TIME_OFFSET       (PROTECTION_ACTIVE_OFFSET + PROTECTION_ACTIVE_SIZE)


#endif //__EEPROM_MAP_H

