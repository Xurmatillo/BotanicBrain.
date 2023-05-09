import tensorflow as tf
import numpy as np
import serial

# Connect to the Arduino platform
ser = serial.Serial('/dev/ttyACM0', 9600)

# Load the pre-trained neural network model
model = tf.keras.models.load_model('smart_gardener_model.h5')

# Collect sensor data
temperature = ser.readline()
humidity = ser.readline()
soil_moisture = ser.readline()
light_intensity = ser.readline()

# Preprocess the sensor data
input_data = np.array([temperature, humidity, soil_moisture, light_intensity])
input_data = input_data.reshape(1, 4)

# Make predictions using the neural network
predictions = model.predict(input_data)

# Act on the predictions
if predictions[0][0] > 0.5:
    ser.write(b'water_on')
else:
    ser.write(b'water_off')
if predictions[0][1] > 0.5:
    ser.write(b'light_on')
else:
    ser.write(b'light_off')
