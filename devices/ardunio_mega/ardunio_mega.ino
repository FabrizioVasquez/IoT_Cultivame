#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#define seaLevelPressure_hPa 1013.25
#define UV_PIN 0
#define RAIN_PIN 9
#define CO2_PIN 2
#define DHT_PIN 2
#define DHTTYPE DHT11

Adafruit_BMP085 bmp;
DHT dht(DHT_PIN, DHTTYPE);
String cmessage; // complete message

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  //nodemcu.begin(115200);

  dht.begin();
  pinMode(UV_PIN,INPUT);
  pinMode(RAIN_PIN, INPUT);

  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	  while (1) {}
  }
}
  
void loop() {
    float uvValue = analogRead(UV_PIN);
    int co2value = analogRead(CO2_PIN);    
    int rainvalue = digitalRead(RAIN_PIN);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float bmptemp = bmp.readTemperature(); 
    float bmpprea = bmp.readPressure();
    float bmpalti = bmp.readAltitude();
    float bmppreasea = bmp.readSealevelPressure();
    float bmprealalt = bmp.readAltitude(seaLevelPressure_hPa * 100);

    //Sensor altimetro
    /*Serial.print("Temperature = ");
    Serial.print(bmptemp);
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmpprea);
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmpalti);
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmppreasea);
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmprealalt);
    Serial.println(" meters");
    
    Serial.print("UV  = ");
    Serial.print(uvValue);

    Serial.print("\nshuvia  = ");
    Serial.print(rainvalue);
    
    Serial.print("\nCO2  = ");
    Serial.print(co2value);

    Serial.print("\nHumedad  = ");
    Serial.print(h);
    Serial.print("\nTemperatura  = ");
    Serial.print(t);*/

    cmessage = cmessage + bmptemp;
    cmessage = cmessage + ",";
    cmessage = cmessage + bmpprea;
    cmessage = cmessage + ",";
    cmessage = cmessage + bmpalti;
    cmessage = cmessage + ",";
    cmessage = cmessage + bmppreasea;
    cmessage = cmessage + ",";
    cmessage = cmessage + bmprealalt;
    cmessage = cmessage + ",";
    cmessage = cmessage + uvValue;
    cmessage = cmessage + ",";
    cmessage = cmessage + rainvalue;
    cmessage = cmessage + ",";
    cmessage = cmessage + co2value;
    cmessage = cmessage + ",";
    cmessage = cmessage + h;
    cmessage = cmessage + ",";
    cmessage = cmessage + t;
    Serial.print(cmessage);
    Serial.println("");

    Serial3.write(cmessage.c_str());
    Serial3.write("\n");

    cmessage = "";
    
    delay(1000);
}
