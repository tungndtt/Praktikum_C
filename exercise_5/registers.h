/*
 * Pseudo registers.
 */

#include <stdint.h>

#define EN_ADC_6_7 0x00c00000
#define NULL_24 0xfeffffff
#define DIV_60 0xbc000000
#define REFH_AVSS 0x0000d000

typedef uint32_t Register_t;

Register_t ADCCON3 = 0xa14c99f7;

struct RegisterManipulator {
    uint32_t : 12; 
    uint32_t refh_avss : 4; 
    uint32_t : 4;
    uint32_t adc_67 : 4; 
    uint32_t div_60: 8; 
};


