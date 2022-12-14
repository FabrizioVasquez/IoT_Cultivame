#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>  // WiFi
#include <DHT.h>

#define DHTPIN 0
#define UVPIN 15
#define DHTTYPE DHT11
const char *ssid = "HUAWEIP10lite";         // Enter your WiFi name
const char *password = "9261566b39f3";      // Enter WiFi password// MQTTBroker
const char *mqtt_broker = "192.168.174.2";  // Enter your WiFi or Ethernet IP
const char *topic = "test/topic";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);
String message;
String myString;
char rdata; // received charactors

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  //sensor init
  dht.begin();
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to mosquitto mqttbroker\n", client_id.c_str());
    if (client.connect(client_id.c_str())) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println(" - - - - - - - - - - - -");
}

void loop() {
  client.loop();
  //delay(2000);
  //float g = analogRead(A0); //Gas
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  //float uv = analogRead(UVPIN); //UV
  // Publish and Subscribe
  message = "";
  /*message += h;
  message += ",";
  message += "";
  message += t;
  message += ","; 
  message += String(h/1023*100);
  message += ",";
  message += uv;*/

  if (Serial.available() > 0 ) {
    rdata = Serial.read();

    if ( rdata == '\n') {
      Serial.println(myString); 
      message = myString; //getValue(myString, ',', 0);
      myString = "";
    } else {
      myString = myString + rdata;      
    }

  // client.publish(topic, "Node: Sensing Enviroment"); //Send the message to the broker
    client.publish(topic, message.c_str()); //Send the message to the broker

    client.subscribe(topic);//delay(100);
  }
}