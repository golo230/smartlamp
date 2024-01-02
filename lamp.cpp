#include <Adafruit_NeoPixel.h>
#define DIN 12
#define TRIG 2
#define ECHO 3
#define NUMBER_PIXELS 61
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMBER_PIXELS, DIN, NEO_GRB + NEO_KHZ800);

int wait = 500;
int i = 0;
long duration;
int distance;
volatile bool active = false;
volatile bool tempactive = false;
volatile bool color = false;

void setup()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  led.begin();
  led.clear();
  led.show();
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10) {
    active = !active;
    tempactive = true;
  }
  
  if (active && tempactive){

    for (int i=0; i<led.numPixels()-1; i++) {
        void rainbow7(uint16_t i, uint16_t wait);
        int np = led.numPixels(); 
        // led.setPixelColor(i % np, 255, 255, 255);
        
        if (color) { led.setPixelColor(i % np, 255, 0, 0); }
        else { led.setPixelColor(i % np, 0, 255, 0); }
        color = !color;
    }
    led.show();
    tempactive = false;
    delay(750);
  }

  else if (!active && tempactive) {
    led.clear();
    led.show();
    tempactive = false;
    delay(750);
  } 
} 

// traveling RGB strip code
/*
void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance Outer: ");
  Serial.println(distance);

  if (distance < 50) {active = !active; }
  
  while (active){

    for (int i=0; i<led.numPixels()-1; i++) {
        void rainbow7(uint16_t i, uint16_t wait);
        int np = led.numPixels();  // we use the modulo function with this
        led.setPixelColor(i     % np, 0, 0, 0); // off
        led.setPixelColor((i+1) % np, 25, 0, 25); // violet
        led.setPixelColor((i+2) % np, 255, 0, 255); // indigo
        led.setPixelColor((i+3) % np, 0, 0, 150); // blue
        led.setPixelColor((i+4) % np, 0, 150, 0); // green
        led.setPixelColor((i+5) % np, 255, 255, 0); // yellow
        led.setPixelColor((i+6) % np, 110, 70, 0); // orange
        led.setPixelColor((i+7) % np, 150, 0, 0); // red
        led.show();
        delay(100); 
        led.clear();

        digitalWrite(TRIG, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG, LOW);
        duration = pulseIn(ECHO, HIGH);
        distance = duration * 0.034 / 2;
        Serial.print("Distance Inner: ");
        Serial.println(distance);

      if (distance < 50) {
        active = !active;
        led.clear();
        led.show();
        delay(wait * 2); 
        break;
        }
    }
  }
} */