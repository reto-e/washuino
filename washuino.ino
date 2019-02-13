
char im[128], data[128];                // used for fft
int mic_val; // value from mic
int distance[5]; // look up how to set up array
int trigger_volume; // if a sound is louder then this it starts the pattern watching loop
int threshold = 20;

unsigned long initial_millis;
unsigned long a_millis;
unsigned long b_millis;

// https://www.youtube.com/watch?v=5RmQJtE61zE&t=311s

// https://www.instructables.com/id/Arduino-Frequency-Detection/

// https://www.youtube.com/watch?v=jCkrgSbVNBs
// 

bool checkForDingDong(int distance[]) {
  bool isDingDong = false;
  if (distance[0] > 400-threshold && distance[0] < 400+threshold &&
      distance[1] > 400-threshold && distance[1] < 400+threshold &&
      distance[2] > 1200-threshold && distance[2] < 1200+threshold &&
      distance[3] > 400-threshold && distance[3] < 400+threshold &&
      distance[4] > 400-threshold && distance[4] < 400+threshold) isDingDong = true;
      return isDingDong;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  trigger_volume = 500;
 
// wiring the module: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-agc-electret-microphone-amplifier-max9814.pdf
}

void loop() {
  //----------------------------------------
  // Variante peaks zaehlen
  //---------------------------------------
  
  mic_val = analogRead(A0);
  if(mic_val > trigger_volume) {
    initial_millis = millis();
    a_millis = millis();
    int i = 0;
    while(millis() - initial_millis < 3000) {
      mic_val = analogRead(A0);

      // If there is another loud sound at least 200 milliseconds later
      if(mic_val > trigger_volume && millis() - a_millis > 200) {
        distance[i] = millis() - a_millis;
        a_millis = millis();
        if (i < 4) { i++; }
        } 
    }
    Serial.println(distance[0]);
    Serial.println(distance[1]);
    Serial.println(distance[2]);
    Serial.println(distance[3]);
    Serial.println(distance[4]);
    
  }
  if(checkForDingDong(distance)) Serial.println("Ding Dong erkannt");

  // reset distance values to 0
    for (int i = 0; i < 5; i++ ) {
      distance[i] = 0;
      }
  
 }
