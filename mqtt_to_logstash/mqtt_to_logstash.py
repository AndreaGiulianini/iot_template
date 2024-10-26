import paho.mqtt.client as mqtt
import requests
import json

MQTT_BROKER = "mqtt"  # Name of the MQTT broker in the container Docker
MQTT_PORT = 1883
LOGSTASH_HTTP_ENDPOINT = "http://logstash:5044"

# Callback for MQTT connection
def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        print("Connected to MQTT broker")
        client.subscribe("#")  # Subscribe to all topics
    else:
        print(f"Failed to connect to MQTT broker. Reason: {reason_code}")

# Callback for MQTT messages received
def on_message(client, userdata, msg):
    data = {
        "topic": msg.topic,
        "payload": msg.payload.decode("utf-8"),
        "qos": msg.qos,
    }
    # Send the message to Logstash
    try:
        response = requests.post(LOGSTASH_HTTP_ENDPOINT, json=data)
        response.raise_for_status()
        print(f"Message sent: {data}")
    except requests.exceptions.RequestException as e:
        print(f"Error sending message: {e}")

# Config the MQTT client
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.connect(MQTT_BROKER, MQTT_PORT, 60)

# Loop forever
client.loop_forever()
