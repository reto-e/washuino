#include <CayenneMQTTMKR1000.h>
#include "config.h"

int ldr_val; // value from light dependent resistor (ldr)
int val_sum; //
int trigger_value; // if a sound is louder then this it starts the pattern watching loop
bool goIntoLoop = false;
bool messageSent = false;
int channel = 0;  // channel for receiver of sms

//-------------------------------------------------
//   readChannel
//-------------------------------------------------
void readChannel() {
  int channel_val = analogRead(A1);
//  Serial.println(channel_val);
  if(channel_val < 25)                        { channel = 1; } //reto
  if(channel_val > 25 && channel_val < 50)    { channel = 2; } // iris
  if(channel_val > 120 && channel_val < 420)  { channel = 3; } // Markus
  if(channel_val > 550 && channel_val < 800)  { channel = 4; } // Martin
  if(channel_val > 870 && channel_val < 980)  { channel = 5; } // Chrigi
  if(channel_val > 960 )                      { channel = 0; } // kein sms
}


//-------------------------------------------------
//   Setup
//-------------------------------------------------

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);  // comment out for debugging
  pinMode(6, OUTPUT);  // led pin
  trigger_value = 300;
 
}

//-------------------------------------------------
//   Loop
//-------------------------------------------------
void loop() {

  for (int i = 0; i < 10; i++) {
    ldr_val = analogRead(A0);
    val_sum = val_sum + ldr_val;
  }

  float flat_val = val_sum/10;
  
  
//  Serial.println(flat_val);
//  delay(20);

  val_sum = 0;  // set sum to 0 again for next loop
  
  if(flat_val > trigger_value) {
    digitalWrite(6, HIGH); // turn LED on
    readChannel();
    if (channel > 0) {
      goIntoLoop = true;
      }
  }
  else {
    digitalWrite(6, LOW);  // turn LED off
  }
  
  if(goIntoLoop) {
//    Serial.print("Channel value: ");
//    Serial.println(channel);
    readChannel();    // read channel again to have latest position of slider
    Cayenne.loop();  // comment out for debugging
  }
  
}

CAYENNE_OUT_DEFAULT()
{
  if(messageSent == false) {
    Cayenne.virtualWrite(channel, 1);
    messageSent = true;
  }
  
}
