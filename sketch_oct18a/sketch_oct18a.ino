#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WifiSSID";                  // SSID Wi-fi
const char* password = "WifiPassword";          // Password Wi-Fi
const char* mqtt_server = "NgrokDomain";        // IP address broker MQTT with Ngrok
const int mqtt_port = 10374;                    // Port created by Ngrok for TCP tunnel
const int led_pin = 15;                         // Pin LED GPIO

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connection to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on [");
  Serial.print(topic);
  Serial.print("]: ");
  String message;

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  switch(x){
    case 1:

    case 2:
  }

  // Accendo il LED
  digitalWrite(led_pin, HIGH);
  delay(3000);
  // Spengo il LED
  digitalWrite(led_pin, LOW);
}

void reconnect() {
  // Loop finché non siamo connessi al broker MQTT
  while (!client.connected()) {
    Serial.print("Connection to MQTT broker..");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      // Una volta connessi, iscriviti al topic
      client.subscribe("my-channel");
    } else {
      Serial.print("Connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      // Aspetta 5 secondi prima di ritentare
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost, reconnecting...");
    setup_wifi();
  }
  
  // Check MQTT connection
  if (!client.connected()) {
    reconnect();
  }
  
  // Maintain MQTT connection
  client.loop();
}
