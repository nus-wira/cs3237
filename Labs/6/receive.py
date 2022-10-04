from pathlib import Path
import paho.mqtt.client as mqtt
import numpy as np
import json
from PIL import Image
from os import listdir
from os.path import join

import tensorflow as tf
from tensorflow.python.keras.backend import set_session
from keras.models import Model, load_model

MODEL_NAME = 'flowers.hd5'

# Our samples directory
SAMPLE_PATH = './samples'

tpl = ('daisy', 'dandelion', 'roses', 'sunflowers', 'tulips')

session = tf.compat.v1.Session(graph = tf.compat.v1.Graph())

# model = Model()

with session.graph.as_default():
    set_session(session)
    model = load_model(MODEL_NAME)

classes = ("daisy", "dandelion", "roses", "sunflowers", "tulips")

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected.")
        client.subscribe("Group_05/IMAGE/classify")
    else:
        print("Failed to connect. Error code:", rc)

def classify(model: Model, image: np.ndarray) -> tuple[str, float, int]:
    with session.graph.as_default():
        set_session(session)
        result = model.predict(image)
        themax = np.argmax(result)

    return (tpl[themax], result[0][themax], themax)

def classify_flower(filename: Path, data: np.ndarray) -> dict:
    print("Start classifying")
    label, score, win = classify(model, data)
    # So that json can serialize
    score = float(score)
    win = int(win)
    print("Done.")
    return {"filename": filename, "prediction": classes[win], "score": score, "index": win}

def on_message(client, userdata, msg):
    # Payload is in msg. We convert it back to a Python dictionary.
    recv_dict = json.loads(msg.payload)

    # Recreate the data
    img_data = np.array(recv_dict["data"])
    result = classify_flower(recv_dict["filename"], img_data)

    print("Sending results: ", result)
    client.publish("Group_05/IMAGE/predict", json.dumps(result))

def setup(hostname: str) -> mqtt.Client:
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    # client.connect(hostname)
    client.connect("localhost", 1883, 60)
    # client.loop_start()
    client.loop_forever()
    return client

# Test main
def main():
    # with session.graph.as_default():
    #     set_session(session)
    #     model = load_model(MODEL_NAME)

    setup("192.168.0.1")

    # sample_files = listdir(SAMPLE_PATH)
    

        # for filename in sample_files:
        #     filename = join(SAMPLE_PATH, filename)
        #     img = load_image(filename)
        #     label, prob, _ = classify(model, img)

        #     print(f"We think with certainty {prob} that image {filename} is {label}.")


if __name__ == "__main__":
    main()