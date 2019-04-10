#include <Arduino_JSON.h>

unsigned long lastControlPacket = -10000;
JSONVar packet = "";
boolean disabled = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(13, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    // read serial data
    String in = Serial.readStringUntil('\n');
    JSONVar p = JSON.parse(in);

    // if the packet is valid json
    if(JSON.typeof(p) != undefined) {
      // set the public packet
      packet = p;

      // update last packet timing
      lastControlPacket = millis();
    }
  } 

  // has a decent amount of time elapsed since last packet?
  if(millis()-lastControlPacket > 200){
    if(!disabled) {
      disabled = true;
      disabledInit();
    } else {
      disabledLoop();
    }
    digitalWrite(13, true);
  } else {
    if(disabled){
      disabled = false;
      enabledInit();
    } else {
      enabledLoop();
    }
    digitalWrite(13, round(millis()/500) % 2 == 0);
  }
 
 delay(20);
}

// MODIFY BELOW THIS POINT

void robotInit() {
  // runs when Arduino boots, use instead of setup:
  
}

void disabledInit() {
  // runs when robot changes to disabled:
  
}

void disabledLoop() {
  // runs periodically when disabled:
   
}

void enabledInit() {
  // runs when robot changes to enabled:
}

void enabledLoop() {
  // runs periodically when enabled:
  
}
