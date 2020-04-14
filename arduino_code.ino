#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// wifi settings
const char* ssid     = "YourWifiName";
const char* password = "YourWifiPW";

// website to get data from
const char* host = "0z02zemtz2.execute-api.us-east-2.amazonaws.com";

// fingerprint
const char fingerprint[] PROGMEM = "98f85efc1101034f0fc11efee981c99cc843274c";

void setup() {
  // initialze baud rate for writing to serial
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to be available
  delay(100);

  // set pin mode for blinkenlights
  pinMode(0, OUTPUT);

  // connect to wifi network
  Serial.print("attempting to connect to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println();
  Serial.println("connected to wifi!");
}
 
void loop() {
  // blink the lights
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  delay(2000);

  Serial.println("BEGINNING OF MAIN LOOP");

  // attempt to connect to the api
  Serial.print("connecting to the api at: ");
  Serial.println(host);
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
 
  const int port = 443;
  if (!client.connect(host, port)) {
    Serial.println("connection failed!!!");
    delay(500);
    return;
  }

  // hit an endpoint of the api
  String url = "/Development/controllers/1/receivers/1/valves";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(500);

  // read the response
  String response = "";
  while (client.available()) {
    response = client.readStringUntil('\r');
  }

  // deserialize JSON and print valve statuses
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, response);
  JsonArray array = doc.as<JsonArray>();
  for(JsonObject v : array) {
    Serial.print("Printing the status of valve: ");
    Serial.print(v["valve_id"].as<int>());
    Serial.print(" - ");
    Serial.println(v["status"].as<int>() ? "On" : "Off");
  }

  Serial.println();

  
}
