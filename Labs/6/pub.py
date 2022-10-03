import paho.mqtt.client as mqtt
from time import sleep

def on_connect(client, userdata, flags, rc):
    print("Connected with result code:", str(rc))
    print("Waiting for 2 seconds.")
    sleep(2)

    print("Sending message.")
    client.publish("hello/world", "This is a test.")

def main():
    client = mqtt.Client()
    client.on_connect = on_connect

    client.connect("localhost", 1883, 60)
    client.loop_forever()

if __name__ == "__main__":
    main()