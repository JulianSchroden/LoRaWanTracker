/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#ifndef _MAINACTIVITY_h
#define _MAINACTIVITY_h

#include <ui/Activity.h>
#include "LoRaConstants.h"


class MainActivity: public Activity {

private: 
    uint8_t selectedMode = LoRaConstants::OTAA_MODE;
    void drawLayout();
    void drawIndicator(bool draw=true);

public:
	MainActivity();
	virtual void onScroll(int distance);
	virtual void onClick();

	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onDestroy();
};



#endif
