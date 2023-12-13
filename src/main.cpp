#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include "MQ135.h"

Adafruit_SSD1306 oled(128,64, &Wire,-1);
DHT my_sensor(18, DHT11);
float temp, humidity;


int i = 0;
float ldr;
float ldr_a;
float resol = 4096;
int count;

void setup(){

  Serial.begin(115200);
  my_sensor.begin();
  delay(2000);



  // Connect to Arduino IoT Cloud
  // ArduinoCloud.begin(ArduinoIot);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */



  int count = 0;
  pinMode(2, OUTPUT);
  pinMode(4,INPUT);
  pinMode(0,INPUT);
  digitalWrite(2, LOW);


  if (oled.begin(SSD1306_SWITCHCAPVCC,0x3C )){
    Serial.println("Failed");
    return;
  }

  //boiler plate for writing anything on oled



  
  

}


void loop() {


  MQ135 gasSensor = MQ135 (15);
  float air_quality = gasSensor.getPPM();
  int air = air_quality;
  // Serial.println(air_quality);

  humidity = my_sensor.readHumidity();
  temp = my_sensor.readTemperature();
  int ldr = analogRead(4);



  int humidity_i = humidity;

  ldr_a = ldr/resol;
  ldr_a = ldr_a*100;
  int ldr_ai = ldr_a;


  if(ldr < 100){

    if (digitalRead(0) != 1){
    count = count +1;
    delay(500);}

    digitalWrite(2, HIGH);
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,0);
    



  if (count == 1){


    
    oled.setTextSize(4);
    oled.print(ldr_ai);
    oled.print("%");

    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Bright");
  
  }

    if (count == 2){


    
    oled.setTextSize(4);
    oled.print(temp);


    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Celsius");
  
  }

    if (count == 3){


    
      oled.setTextSize(4);
      oled.print(humidity_i);
      oled.print("%");

      oled.setTextColor(SSD1306_WHITE);
      oled.setCursor(0,32);
      oled.setTextSize(3);
      oled.print("Humid");}


    if (count == 4){


  
    oled.setTextSize(4);
    oled.print(air);
    // oled.print("%");

    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Quality");}

    else{
      oled.setTextSize(8);
      oled.print("ON");}

    oled.display();

  }
  
  else{
  digitalWrite(2, LOW);
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  

  if (digitalRead(0) != 1){
    count = count +1;
    delay(500);}

  if (count == 1){


  
    oled.setTextSize(4);
    oled.print(ldr_ai);
    oled.print("%");

    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Bright");
  
  }

    if (count == 2){


    
    oled.setTextSize(4);
    oled.print(temp);


    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Celsius");
  
  }

    if (count == 3){


  
    oled.setTextSize(4);
    oled.print(humidity_i);
    oled.print("%");

    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Humid");}

    if (count == 4){


  
    oled.setTextSize(4);
    oled.print(air);
    // oled.print("%");

    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,32);
    oled.setTextSize(3);
    oled.print("Quality");
  
  }
  else{
    oled.setTextSize(7);
    oled.print("OFF");}}








  oled.display();


  if (count > 4){
    count = 0;
  }
  
  // Serial.print(ldr_ai);
  // Serial.print(",");
  // Serial.print(temp);
  // Serial.print(",");
  // Serial.print(humidity_i);
  // Serial.println(",");
  delay(100);






}