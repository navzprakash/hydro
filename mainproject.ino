Z#include <DHT.h>
#include <WiFi.h >
#include <DallasTemperature.h>
#include <OneWire.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>
#define DHTPIN 4  // Define the GPIO pin where the DHT11 data pin is connected
#define DHTTYPE DHT11

#define RELAY_PIN 33
const char *ssid =  "AiROBOSOFT_guest";    
const char *pass =  "admin@2319Za";
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "navzz"
#define MQTT_PASS "aio_MHCS80T9lLQgDlFPSqKNZ1XNb3MU"
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Publish Moisture = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/Moisture"); 
Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/Temperature");
Adafruit_MQTT_Publish Humidity = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/Humidity");
//Adafruit_MQTT_Publish SoilTemp = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/SoilTemp");
//Adafruit_MQTT_Subscribe LED = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/LED");
// Adafruit_MQTT_Subscribe Pump = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Pump");
DHT dht(DHTPIN, DHTTYPE);
int _moisture,sensor_analog;
const int sensor_pin = 36;  /* Soil moisture sensor O/P pin */

void setup(void){
   pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600); 
  
  Serial.println("DHT11 Sensor Test");
  dht.begin();/* Set the baudrate to 115200*/
}

void loop(void){
 
  
  
     sensor_analog = analogRead(sensor_pin);
  _moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  

  Serial.print("Moisture = ");
  Serial.print(_moisture);  /* Print Temperature on the serial window */
  Serial.println("%");
  delay(1000);  
    // Delay for 2 seconds between measurements

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  //Check if any reads failed and exit early (to try again).
 if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
   return;
 }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  
/* Wait for 1000mS */
if(humidity<80&&temperature<30)
{digitalWrite(RELAY_PIN, HIGH);
delay(1000);}
else
{digitalWrite(RELAY_PIN, LOW);
  delay(1000);}

 if (currentTime - previousTime >= Interval) {
    if (! Moisture.publish(moisturePercentage))
    if (! Temperature.publish(temperature))
    if (! Humidity.publish(humidity))
    if (! SoilTemp.publish(soiltemp))
    if (! WeatherData.publish(icon))
}}
//#define RELAY_PIN 33 // ESP32 pin GPIO16 connected to the IN pin of relay
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//  // initialize digital pin as an output.
//  pinMode(RELAY_PIN, OUTPUT);
//}
//
//// the loop function runs over and over again forever
//void loop() {
//  digitalWrite(RELAY_PIN, HIGH);
//  delay(1000);
//  digitalWrite(RELAY_PIN, LOW);
//  delay(1000);
//}
