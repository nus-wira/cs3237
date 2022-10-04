import paho.mqtt.client as mqtt
import numpy as np
from PIL import Image
import json
from pathlib import Path

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected.")
        client.subscribe("Group_05/IMAGE/predict")
    else:
        print("Failed to connect. Error code:", rc)

def on_message(client, userdata, msg):
    print("Received message from server.")
    resp_dict = json.loads(msg.payload)
    filename = resp_dict["filename"]
    prediction = resp_dict["prediction"]
    score = resp_dict["score"]
    print(f"{filename = }, {prediction = }, {score = }")

def setup(hostname: str) -> mqtt.Client:
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    # client.connect(hostname)
    client.connect("localhost", 1883, 60)
    client.loop_start()
    return client

# Load image
def load_image(image_fname: Path) -> np.ndarray:
    img = Image.open(image_fname)
    img = img.resize((249, 249))
    imgarray = np.array(img)/255.0
    final = np.expand_dims(imgarray, axis=0)
    return final

def send_image(client: mqtt.Client, filename: Path):
    img = load_image(filename)
    img_list = img.tolist()
    send_dict = {"filename": filename, "data": img_list}
    client.publish("Group_05/IMAGE/classify", json.dumps(send_dict))

def main():
    client = setup("192.168.0.1")
    print("Sending data.")
    send_image(client, "tulip2.jpg")
    print("Done. Waiting for results.")
    while True:
        pass

if __name__ == "__main__":
    main()