/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#include "LoRaTesterActivity.h"

#include <SPI.h>
#include <lmic.h>
#include <hal/hal.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <utils/ByteStack.h>
#include <ui/TextUtils.h>
#include "LoRaConstants.h"
#include "loraConfig.h"

/**
 *  This implementation makes use of the library arduino-lmic by Thomas Telkamp and Matthijs Kooijman
 *  https://github.com/matthijskooijman/arduino-lmic
 */ 



volatile int LoRaWAN_Rx_Payload = 0 ;


// -------- LoRa Event 
void onEvent (ev_t event) { 
    // print out the current os_time and event text
    Serial.print(os_getTime());
    Serial.print(": ");
    Serial.println(LoRaConstants::getEventString(event));

    switch(event) {
        case EV_JOINED:
            // Disable link check validation 
            LMIC_setLinkCheckMode(0);
            break;
        case EV_TXCOMPLETE:
            if (LMIC.txrxFlags & TXRX_ACK)
                Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
                Serial.println(F("Received "));
                Serial.println(LMIC.dataLen);
                Serial.println(F(" bytes of payload"));
                LoRaWAN_Rx_Payload = 0; 
                for (int i = 0; i < LMIC.dataLen; i++) { 
                    Serial.println(LMIC.frame[i + LMIC.dataBeg], HEX);
                    LoRaWAN_Rx_Payload = 256 * LoRaWAN_Rx_Payload + LMIC.frame[i + LMIC.dataBeg];
                }
            }
            break;
    }
}



// uart 2 rxPin = 16; txPin = 17;
const uint32_t GPSBaud = 9600;
HardwareSerial Serial_2(2);
TinyGPSPlus gps;

ByteStack byteStack(12); 



LoRaTesterActivity::LoRaTesterActivity(uint8_t mode, uint8_t dataRate, uint8_t txPower, uint32_t interval, int8_t payload)
:Activity("OTAA", true, 1, true), selectedMode(mode), dataRate(dataRate), txPower(txPower), interval(interval * 1000), payload(payload), bytes(12) {

}


void LoRaTesterActivity::drawLayout() {
    clearActivity(BLACK, false);
    Activity::drawLayout();
    display.setTextColor(WHITE);

    // print dataRate and txPower on the display
    display.setCursor(8, titleBarHeight + 4);
    display.printf("Dr: %s  Pw: %d", LoRaConstants::getDataRateString(LMIC.datarate).c_str(), LMIC.adrTxPow);
    
    // print seconds since last LoRaTx on the display
    display.setCursor(8, titleBarHeight + 14);
    display.printf("LastMsg: %d s", (millis() - lastLoRaTx) / 1000);

    // print seconds till nextLoRaTx on the display
    display.setCursor(8, titleBarHeight + 24);
    display.printf("NextMsg: %d s", ((lastLoRaTx + interval) - millis()) / 1000);

    // print latitude on the display
    display.setCursor(8, titleBarHeight + 34);
    display.printf("lat: %.6f", gps.location.lat());

    // print longitude on the display
    display.setCursor(8, titleBarHeight + 44);
    display.printf("lng: %.6f", gps.location.lng());

    display.display();
}


void LoRaTesterActivity::onClick(){
    // skip interval pause
    lastLoRaTx = millis() - interval;
}



void LoRaTesterActivity::onStart(){
    Activity::onStart();

    Serial_2.begin(GPSBaud);
    
    // (OTAA) Join if not already joined
    if(selectedMode == LoRaConstants::OTAA_MODE && LMIC.devaddr == 0){
        // LMIC init
        os_init();
        // set flag to draw indicator in titlebar
        areInterruptsEnbabled = false;
        drawLayout();
        // try to join the network for 10 times
        for(uint8_t i = 0; i < 10; i++){
            // Reset the MAC state. Session and pending data transfers will be discarded.
            LMIC_reset();

            // start joining procedure with the provided dataRate and txPower
            LMIC_startJoining(dataRate, txPower);
            uint32_t start = millis();
            uint32_t maxDuration = 20000; 
            Serial.printf("Trying to Join for about %d s\n", maxDuration/1000);
            while(LMIC.devaddr == 0 && start + maxDuration > millis()){
                os_runloop_once();
                yield();
            }

            if(LMIC.devaddr != 0){
                break;
            }
        }
        areInterruptsEnbabled = true;
        drawLayout();
    }
    // (OTTA) already joined
    else if(selectedMode == LoRaConstants::OTAA_MODE && LMIC.devaddr != 0){
        LMIC.adrTxPow = txPower;
        LMIC.datarate = dataRate;
    }

    // (ABP) init
    else if(selectedMode == LoRaConstants::ABP_MODE){
        // LMIC init
        os_init();
        // Reset the MAC state. Session and pending data transfers will be discarded.
        LMIC_reset();

        // Set static session parameters. Instead of dynamically establishing a session
        // by joining the network, precomputed session parameters are be provided.
        uint8_t appskey[sizeof(APPSKEY)];
        uint8_t nwkskey[sizeof(NWKSKEY)];
        memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
        memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
        LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);

        // Set up the channels used by the Things Network, which corresponds 
        // to the defaults of most gateways. Without this, only three base
        // channels from the LoRaWAN specification are used
        LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
        LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
        LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band

        LMIC_setLinkCheckMode(0);   // Disable link check validation
        LMIC.dn2Dr = DR_SF9;	       // TTN uses SF9 for its RX2 window.
        LMIC_setDrTxpow(dataRate, txPower); // Set data rate and transmit power for uplink
    }


    // start Worker
    Serial.println("Start the Worker");
    startWorker();
}

// Worker callback
void LoRaTesterActivity::runOnce(){
    static uint32_t lastDisplayUpdate = millis();
            uint8_t TTN_PORT          = 10;

    // parse data from gps sensor
    while (Serial_2.available() > 0){
        if(gps.encode(Serial_2.read())){
            break;
        }
    }

    // redraw diplay once a second
    if(lastDisplayUpdate + 1000 < millis()){
        drawLayout();
        lastDisplayUpdate = millis();
    }
    
    // send message every x seconds
    if(lastLoRaTx + interval < millis() && LMIC.globalDutyAvail < os_getTime()) { 
        // read gps values
        Serial.printf("\n%d: Prepare payload\n", os_getTime());
        int32_t latitude = 0, longitude = 0, alt = 0; 
        int factor    = 1000000; // 10^6
        int altFactor =    1000; // 10^3
        if(gps.location.isValid()){
            latitude  = (int32_t)(gps.location.lat() * factor);
            longitude = (int32_t)(gps.location.lng() * factor);
        }
        if(gps.altitude.isValid()){
            alt = (int32_t)(gps.altitude.meters() * altFactor);
        }
        Serial.printf("%d: lat = %d, lng = %d, alt = %d\n", os_getTime(), latitude, longitude, alt);

        if(latitude != 0 && longitude != 0 && alt != 0) {
            bytes.reset();
            bytes.push(latitude);
            bytes.push(longitude);
            bytes.push(alt);

             // set interrupt flag to draw indicator in titlebar
            areInterruptsEnbabled = false;
            drawLayout();

            // Check if there is not a current TX/RX job running
            if(!(LMIC.opmode & OP_TXRXPEND)) {
                // Prepare upstream data transmission at the next possible time. 
                LMIC_setTxData2(TTN_PORT, bytes.getBytes(), bytes.getSize(), 0);  
                // Packet queued
                while(LMIC.opmode & OP_TXRXPEND){
                    yield();
                    os_runloop_once();
                }
                lastLoRaTx = millis();   
            }
            
            // unset interrupt flag
            areInterruptsEnbabled = true;
            drawLayout();
        }   
    }
}



void LoRaTesterActivity::onPause(){
    Activity::onPause();
    pauseWorker();
}

void LoRaTesterActivity::onResume(){
    Activity::onResume();
    startWorker();
}

void LoRaTesterActivity::onDestroy(){
    Activity::onDestroy();
    terminateWorker();
}

