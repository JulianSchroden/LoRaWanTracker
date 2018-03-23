/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#ifndef _LORA_CONFIG_h
#define _LORA_CONFIG_h

#include <lmic.h>
#include <hal/hal.h>
#include <Arduino.h>

const lmic_pinmap lmic_pins = {  
  .nss = 5,                            // CS, Slave select
  .rxtx = LMIC_UNUSED_PIN,             // For placeholder only, Do not connected on RFM92/RFM95
  .rst = LMIC_UNUSED_PIN,              // Needed on RFM92/RFM95? (probably not) D0/GPIO16 
  .dio = {
    2, 15, LMIC_UNUSED_PIN         } // .dio={ DIO0), DIO1, DIO2} DIO0= IRQ
};


// <OTAA Keys>
static const u1_t PROGMEM DEVEUI[8]={0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
void os_getDevEui (u1_t* buf) { 
    memcpy_P(buf, DEVEUI, 8);
}

static const u1_t PROGMEM APPEUI[8]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
void os_getArtEui (u1_t* buf) { 
    memcpy_P(buf, APPEUI, 8);
}

static const u1_t PROGMEM APPKEY[16]={0x00, 0x00, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
void os_getDevKey (u1_t* buf) {  
    memcpy_P(buf, APPKEY, 16);
};
// </OTAA Keys>


// <ABP Keys>
static const u4_t DEVADDR = 0x00000000;

static const u1_t PROGMEM APPSKEY[16]={
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static const u1_t PROGMEM NWKSKEY[16]={ 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// </ABP Keys>


#endif