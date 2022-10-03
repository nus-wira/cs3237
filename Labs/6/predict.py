from keras.models import Model, load_model
import tensorflow as tf
from tensorflow.python.keras.backend import set_session
import numpy as np
from PIL import Image
from os import listdir
from os.path import join
from pathlib import Path

MODEL_NAME = 'flowers.hd5'

# Our samples directory
SAMPLE_PATH = './samples'

tpl = ('daisy', 'dandelion', 'roses', 'sunflowers', 'tulips')

# Takes in a loaded model, an image in numpy matrix format,
# And a label dictionary

session = tf.compat.v1.Session(graph = tf.compat.v1.Graph())

def classify(model: Model, image: np.ndarray) -> tuple[str, float, int]:
    with session.graph.as_default():
        set_session(session)
        result = model.predict(image)
        themax = np.argmax(result)

    return (tpl[themax], result[0][themax], themax)

# Load image
def load_image(image_fname: Path) -> np.ndarray:
    img = Image.open(image_fname)
    img = img.resize((249, 249))
    imgarray = np.array(img)/255.0
    final = np.expand_dims(imgarray, axis=0)
    return final

# Test main
def main():
    with session.graph.as_default():
        set_session(session)
        model = load_model(MODEL_NAME)

        sample_files = listdir(SAMPLE_PATH)

        for filename in sample_files:
            filename = join(SAMPLE_PATH, filename)
            img = load_image(filename)
            label, prob, _ = classify(model, img)

            print(f"We think with certainty {prob} that image {filename} is {label}.")

if __name__ == "__main__":
    main()
