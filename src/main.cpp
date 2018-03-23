/**  
 *  Copyright (c) 2017-2018 Julian Schroden. All rights reserved.  
 *  Licensed under the MIT License. See LICENSE file in the project root for full license information.  
 */  

#include <Arduino.h>
#include <Runtime.h>
#include "MainActivity.h"

Runtime &runtime = Runtime::getInstance();

void setup() {     
    Serial.begin(115200);
    Serial.println("Starting Runtime");
    runtime.startActivity(new MainActivity());
}


void loop() {
    runtime.runOnce();
}