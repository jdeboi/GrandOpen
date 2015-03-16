#include <Adafruit_NeoPixel.h>
#define PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// pins for the ultrasonic sensor
int ultrasonicPin = A0;
int arraysize = 9; // quantity of values to find the median (sample size). Needs to be an odd number
int rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse;
int modE;

void setup() {
  Serial.begin (9600);
  
  pinMode(ultrasonicPin, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // do a rainbow every time the Arduino is turned on
  rainbow(30);
  // turn pixel off
  strip.setPixelColor(0, 0);
  strip.show();
}

void loop() {
  
 for(int i = 0; i < arraysize; i++){								    
    //pulse = pulseIn(ultrasonicPin, HIGH);
    pulse = analogRead(ultrasonicPin);
    rangevalue[i] = pulse;
    delay(10);
  }
  //Serial.print("Unsorted: ");
  //printArray(rangevalue,arraysize);
  isort(rangevalue,arraysize);
  //Serial.print("Sorted: ");
  //printArray(rangevalue,arraysize);
  modE = mode(rangevalue,arraysize);
  //Serial.print("The mode/median is: ");
  Serial.print(modE);
  Serial.println();
  if (modE < 24) rainbow(30);
  else if (modE > 90) {
    strip.setPixelColor(0, 0);
    strip.show();
    delay(500);
  }
  else {
    int color = map(modE, 0, 90, 200, 0);
    strip.setPixelColor(0, Wheel(color));
    strip.show();
    delay(500);
  } 
}


void printArray(int *a, int n) {
  for (int i = 0; i < n; i++)
  {
    Serial.print(a[i], DEC);
    Serial.print(' ');
  }
  Serial.println();
}

// Sorting function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n){
  for (int i = 1; i < n; ++i)  {
    uint16_t j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--) {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}
 
// Mode function, returning the mode or median.
int mode(int *x,int n){
  int i = 0;
  int count = 0;
  int maxCount = 0;
  uint16_t mode = 0;
  int bimodal;
  int prevCount = 0;
  while(i<(n-1)){
    prevCount=count;
    count=0;
    while( x[i]==x[i+1] ) {
      count++;
      i++;
    }
    if( count > prevCount & count > maxCount) {
      mode=x[i];
      maxCount=count;
      bimodal=0;
    }
    if( count == 0 ) {
      i++;
    }
    if( count == maxCount ) {      //If the dataset has 2 or more modes.
      bimodal=1;
    }
    if( mode==0 || bimodal==1 ) {  // Return the median if there is no mode.
      mode=x[(n/2)];
    }
    return mode;
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    strip.setPixelColor(0, Wheel((i+j) & 255));
    strip.show();
    delay(wait);
  }
}

