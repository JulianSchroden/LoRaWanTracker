/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#ifndef _LORA_TESTER_ACTIVITY_H
#define _LORA_TESTER_ACTIVITY_H

#include <ui/Activity.h>
#include <Worker.h>
#include "utils/ByteStack.h"

class LoRaTesterActivity: public Activity, public Worker {

private:
    uint8_t dataRate;
    uint8_t txPower;
    int32_t interval;
    int8_t  payload;
	int8_t  selectedMode;
	ByteStack bytes;


	int32_t lastLoRaTx = millis();


protected:
	virtual void drawLayout();


public:
    /**
	 *  LoRaTesterActivity constructor
	 *  @param selectedMode   authentification mode (@see system>lora>LoRaConstants.h)
	 *  @param dataRate       dataRate which should be used for the LoRaWan communication
	 *  @param txPower        txPower which should be used for the LoRaWan communication
	 *  @param interval       interval between messages in seconds
	 *  @param payload        identifier for the payload type (Not implemented)
	 */ 
    LoRaTesterActivity(uint8_t selectedMode, uint8_t dataRate, uint8_t txPower, uint32_t interval, int8_t payload);

	virtual void onClick();

	/**
	 *  Worker callback
	 */ 
	virtual void runOnce();


	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onDestroy();
};


#endif