#include <CayenneMQTTMKR1000.h>
#include "config.h"

// https://www.youtube.com/watch?v=5RmQJtE61zE&t=311s
// https://www.instructables.com/id/Arduino-Frequency-Detection/
// https://www.youtube.com/watch?v=jCkrgSbVNBs
// wiring the module: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-agc-electret-microphone-amplifier-max9814.pdf
// https://github.com/myDevicesIoT/Cayenne-MQTT-Arduino/blob/master/examples/Basics/SendData/SendData.ino

#define RETO_CHANNEL 1


int ldr_val; // value from light dependent resistor (ldr)
int trigger_value; // if a sound is louder then this it starts the pattern watching loop
bool goIntoLoop = false;
bool messageSent = false;


//-------------------------------------------------
//   Setup
//-------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

  trigger_value = 130;

  
}

//-------------------------------------------------
//   Loop
//-------------------------------------------------
void loop() {
  ldr_val = analogRead(A0);
  Serial.println(ldr_val);
  delay(200);
  
  if(ldr_val > trigger_value) {
    goIntoLoop = true;
  }
  
  if(goIntoLoop) {
    Cayenne.loop();
  }
  
}

CAYENNE_OUT(RETO_CHANNEL)
{
  if(messageSent == false) {
    Cayenne.virtualWrite(RETO_CHANNEL, 1);
    messageSent = true;
  }
  
}
