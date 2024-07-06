/*BOARD: Arduino Uno */
/*Additional hardware: 
/* - relay module
/* - water level monitor module
/* - mini submersible water pump
/* - OLED Screen  128x64
/* - temperature probe
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0X3C
#define ONE_WIRE_BUS 8

#define relay 12
#define water 10

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temp(&oneWire);

int water_level =1;
float Celcius=0;
float Fahrenheit=0;

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.print(F("Allocation failed"));
    for (;;); //loop forever
  }
  //temp.begin();
  pinMode(relay, OUTPUT);
  pinMode(water, INPUT_PULLUP);
  display.display();
  delay(1000);
  display.clearDisplay();
}


void loop() {
  water_level = digitalRead(water);
  temp.requestTemperatures();
  Celcius = temp.getTempCByIndex(0);
  Fahrenheit = temp.toFahrenheit(Celcius);

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15,20);
  display.print(Fahrenheit);
  display.display();

  if(water_level == 0) {
    digitalWrite(relay, HIGH);
    delay(2000);
  } else{
    digitalWrite(relay, LOW);
    }
    delay(500);

}
