/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#include "MainActivity.h"
#include "Arduino.h"
#include "SetupActivity.h"

MainActivity::MainActivity()
:Activity("LoRa Tester", true, 1) {

}

void MainActivity::drawIndicator(bool draw) {
    uint8_t posLeftX  = display.width() * 0.25;
    uint8_t posRightX = display.width() * 0.75;
    uint8_t posY      = 56;
    uint8_t radius    = 5;
    if(selectedMode == LoRaConstants::OTAA_MODE) {
        // draw filled left circle
        display.fillCircle(posLeftX  + 2, posY, radius, WHITE);
        // draw outlined right circle
        display.fillCircle(posRightX - 4, posY, radius, BLACK);
        display.drawCircle(posRightX - 4, posY, radius, WHITE);
    }
    else{
        // draw outlined left circle
        display.fillCircle(posLeftX  + 2, posY, radius, BLACK);
        display.drawCircle(posLeftX  + 2, posY, radius, WHITE);
        // draw filled right circle
        display.fillCircle(posRightX - 4, posY, radius, WHITE);
    }
    if(draw)
        display.display();
}

void MainActivity::drawLayout() {
    // draw "OTAA" on the left
    uint8_t paddingTop=16;
    display.setCursor(10, titleBarHeight + paddingTop);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("OTAA");

    // draw "ABP" on the right
    display.setCursor((display.width()) / 2 + 12, titleBarHeight + paddingTop);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("ABP");

    drawIndicator(false);
    
    display.display();
}



void MainActivity::onScroll(int distance) {
    // switch mode
    static int16_t counter = 0;
    counter += distance;
    selectedMode = counter % 2;
    drawIndicator();
    
}

void MainActivity::onClick() {
    // start SetupActivity and pass selected mode
    startActivity(new SetupActivity(selectedMode));
}

void MainActivity::onStart() {
	Activity::onStart();
    drawLayout();
}

void MainActivity::onPause() {
	Activity::onPause();
}
void MainActivity::onResume() {
	Activity::onResume();
    drawLayout();
}
void MainActivity::onDestroy() {
	Activity::onDestroy();
}

