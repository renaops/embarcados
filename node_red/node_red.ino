#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* MQTT_username = NULL ;
const char* MQTT_password = NULL; 

const char* mqtt_server = "192.168.2.69";
WiFiClient espClient;
PubSubClient client(espClient);

long now = millis();
long lastMeasure = 0;
int count = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  Serial.println();

  if(topic=="devices/bomba"){
      Serial.print("Mudando a bomba para: ");
      if(messageTemp == "on"){
        Serial.print("LIGADA");
      }
      else if(messageTemp == "off"){
        Serial.print("DESLIGADA");
      }
  }
  Serial.println();
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", MQTT_username, MQTT_password)) {
      Serial.println("connected");  
      client.subscribe("devices/bomba");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client", MQTT_username, MQTT_password);

  now = millis();
  if (now - lastMeasure > 3000) {
    lastMeasure = now;
    
    if (count > 10) count = 0;
    client.publish("devices/agua", String(count).c_str());
    count++;
  }
} 