#include <WiFi.h>
#include <PubSubClient.h>

static const char* WIFI_SSID = "TP-VJ";
static const char* WIFI_PASS = "FES38613921";

const char* mqtt_server = "192.168.3.14";
const int mqtt_port = 1883;
const char* mqtt_topic = "home/room1";
const char* mqtt_user = "jeesparz";
const char* mqtt_pass = "461236";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(2000);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.println("WiFi connected");

  Serial.println();
  Serial.print("http://");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);

}

void loop() {

  if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
    Serial.println("conectado");
    client.publish(mqtt_topic, "Conection succesfully with ESP32");
  } 
  else {
    Serial.print("falló, rc=");
    Serial.print(client.state());
  }
  delay(1000);
  client.loop();
}
