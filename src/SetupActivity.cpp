/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#include "SetupActivity.h"
#include <ui/AttributeChooserActivity.h>
#include <ui/DurationChooserActivity.h>
#include <list>

#include "LoRaTesterActivity.h"

SetupActivity::SetupActivity(uint8_t mode)
:ListActivity(listItems, "Setup", true, 1, true), selectedMode(mode) {
   
}

void SetupActivity::onItemClick(int index) {
	ListActivity::onItemClick(index);

	switch (index) {
		case 0: // choose Datarate
			startActivityForResult(new AttributeChooserActivity(dataRates,"Datarate", selectedDataRateIndex, true, 1, true), DATA_RATES_KEY);
			break;
		case 1: // choose transmit power
			startActivityForResult(new AttributeChooserActivity(txPowers,"txPower", selectedTxPowerIndex, true, 1, true), TX_POWER_KEY);
			break;
		case 2: // choose interval
			startActivityForResult(new DurationChooserActivity("Interval", intervalDuration, true, 1, true), INTERVAL_KEY);
			break;
		case 3: // choose Payload type
			startActivityForResult(new AttributeChooserActivity(payloads,"Payload",selectedPayloadIndex, true, 1, true), PAYLOAD_KEY);
			break;
		case 4: // start LoRaTesterActivity
			startActivity(new LoRaTesterActivity(selectedMode, dataRates[selectedDataRateIndex].getValue(), txPowers[selectedTxPowerIndex].getValue(), intervalDuration, payloads[selectedPayloadIndex].getValue()));
			break;
		}
}

void SetupActivity::onStart() {
	ListActivity::onStart();
}
void SetupActivity::onPause() {
	ListActivity::onPause();
}

void SetupActivity::onActivityResult(ByteStack &result, int8_t key) {
	std::list<String>::iterator listIt = listItems.begin();
	//adavance list iterator to the new start-index
	std::advance(listIt, selectedItem);
	
	// fetch the result and update listItem text
	switch(key) {
		case DATA_RATES_KEY:
		{
			selectedDataRateIndex = result.pop<int8_t>();
			*listIt = "Datarate: "+dataRates[selectedDataRateIndex].getTitle();
			Serial.print("dataRate= ");
			Serial.println(*listIt);
			break;
		}
			
		case TX_POWER_KEY:
		{
			selectedTxPowerIndex = result.pop<int8_t>();
			*listIt = "TxPower: "+txPowers[selectedTxPowerIndex].getTitle();
			Serial.print("txPower= ");
			Serial.println(*listIt);
			break;
		}

		case INTERVAL_KEY:
		{
			intervalDuration=result.pop<uint32_t>();
			*listIt="Interval: "+String(intervalDuration)+"s";
			break;
		}

		case PAYLOAD_KEY:{
			selectedPayloadIndex=result.pop<int8_t>();
			*listIt="Payload: "+payloads[selectedPayloadIndex].getTitle();
			break;
		}			
	}
}

void SetupActivity::onResume() {
	ListActivity::onResume();
}
void SetupActivity::onDestroy() {
	ListActivity::onDestroy();
}