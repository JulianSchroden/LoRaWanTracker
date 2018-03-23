/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#ifndef _LORA_CONSTANTS_h
#define _LORA_CONSTANTS_h

#include <Arduino.h>
#include <lmic.h>

class LoRaConstants{

public:

    static const uint8_t OTAA_MODE = 0;
    static const uint8_t  ABP_MODE = 1;


    /** 
     *  #define osticks2ms(os)   ((s4_t)(((os)*(int64_t)1000    ) / OSTICKS_PER_SEC))
     *  @see oslmic.h:112
     */ 

    static int64_t convertTicksToMicroSeconds(int64_t ticks){
        return ((ticks * (int64_t)1000)/ OSTICKS_PER_SEC); 
    }


    //enum _dr_eu868_t { DR_SF12=0, DR_SF11, DR_SF10, DR_SF9, DR_SF8, DR_SF7, DR_SF7B, DR_FSK, DR_NONE };
    static String getDataRateString(uint8_t dataRate){
        switch(dataRate){
            case DR_SF12:
                return "SF12";
            case DR_SF11:
                return "SF11";
            case DR_SF10:
                return "SF10";
            case DR_SF9:
                return "SF9";
            case DR_SF8:
                return "SF8";
            case DR_SF7:
                return "SF7";
            case DR_SF7B:
                return "SF7B";
            case DR_FSK:
                return "FSK";
            case DR_NONE:
                return "NONE";
        }
    }

    static String getEventString(ev_t event){
        switch(event) {
            case EV_SCAN_TIMEOUT:
                return F("EV_SCAN_TIMEOUT");
            case EV_BEACON_FOUND:
                return F("EV_BEACON_FOUND");
            case EV_BEACON_MISSED:
                return F("EV_BEACON_MISSED");
            case EV_BEACON_TRACKED:
                return F("EV_BEACON_TRACKED");
            case EV_JOINING:
                return F("EV_JOINING");
            case EV_JOINED:
                return F("EV_JOINED");
            case EV_RFU1:
                return F("EV_RFU1");
            case EV_JOIN_FAILED:
            return F("EV_JOIN_FAILED");
            case EV_REJOIN_FAILED:
                return F("EV_REJOIN_FAILED");
            case EV_TXCOMPLETE:
                return F("EV_TXCOMPLETE (includes waiting for RX windows)");
            case EV_LOST_TSYNC:
                return F("EV_LOST_TSYNC");
            case EV_RESET:
                return F("EV_RESET");
            case EV_RXCOMPLETE:
                return F("EV_RXCOMPLETE");
            case EV_LINK_DEAD:
                return F("EV_LINK_DEAD");
            case EV_LINK_ALIVE:
                return F("EV_LINK_ALIVE");
            default:
                return F("Unknown event");
        }
    }
};


#endif