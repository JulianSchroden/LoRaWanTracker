/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#ifndef _SETUP_ACTIVITY_h
#define _SETUP_ACTIVITY_h

#include "Arduino.h"
#include <ui/ListActivity.h>
#include <utils/AttributeChoice.h>
#include <lmic.h>
#include "LoRaConstants.h"
#include <vector>


class SetupActivity: public ListActivity {

private: 
    uint8_t selectedMode = LoRaConstants::OTAA_MODE;

	// keys to associate onActivityResult data
	static const int8_t DATA_RATES_KEY = 0; 
	static const int8_t   TX_POWER_KEY = 1;
	static const int8_t   INTERVAL_KEY = 2;
	static const int8_t    PAYLOAD_KEY = 3;

	// list items of SetupActivity
	std::list<String> listItems = { "Datarate: SF7","TxPower : 14dBm","Interval: 10s","Payload: Location","start" };

	// standard params
	int8_t   selectedDataRateIndex =  0;
	int8_t   selectedTxPowerIndex  = 12;
	int8_t   selectedPayloadIndex  =  1;
	uint32_t intervalDuration      = 10; // interval in seconds

	std::vector<AttributeChoice> dataRates = {{"SF7", DR_SF7}, {"SF8", DR_SF8}, {"SF9", DR_SF9}, {"SF10", DR_SF10}, {"SF11", DR_SF11}, {"SF12", DR_SF12} };
	std::vector<AttributeChoice> txPowers  = {{"2 dBm", 2}, {"3 dBm", 3}, {"4 dBm", 4}, {"5 dBm", 5}, {"6 dBm", 6}, {"7 dBm", 7}, {"8 dBm", 8}, {"9 dBm", 9}, {"10 dBm", 10}, {"11 dBm", 11}, {"12 dBm", 12}, {"13 dBm", 13}, {"14 dBm",14}};
	std::vector<AttributeChoice> payloads  = {{"None", 0}, {"Location", 1}};
	
public:
	/**
	 *  SetupActivity
	 *  @param mode  the authentification mode (@see system>lora>LoRaConstants.h)
	 */ 
	SetupActivity(uint8_t mode);
	virtual void onItemClick(int index);

	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onDestroy();

	virtual void onActivityResult(ByteStack &result, int8_t key);
};


#endif