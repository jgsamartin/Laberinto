import csv
import numpy as np
import random
import tensorflow as tf

# Parámetros de configuración de la red
pTest = 0.2             # % Datos usados para la validación
pTrain = 1 - pTest      # % Datos usados para el entrenamiento

# Leemos el fichero CSV
data = []
with open('./energy-data.csv', 'r') as file:
    reader = csv.reader(file, delimiter=',')
    for row in reader:
        data.append(list(map(int, row)))

# Ordenamos aleatoriamente el array
np.random.shuffle(data)

# Creamos conjunto de entrenamiento y de validación
limite = round(pTest * len(data))
#x_train = 

# Scale pixel values from [0,255] to [0,1] 
x_train, x_test = x_train / 255.0, x_test / 255.0

# Define the network by stacking layers
network = tf.keras.models.Sequential([
  tf.keras.layers.Flatten(input_shape=(28, 28)),
  tf.keras.layers.Dense(128, activation='relu'),
  tf.keras.layers.Dropout(0.2),
  tf.keras.layers.Dense(10, activation='softmax')
])

# Create the training system 
network.compile(optimizer='adam',
                loss='sparse_categorical_crossentropy',
                metrics=['accuracy'])

# Train the network with train data
network.fit(x_train, y_train, epochs=5)

# Evaluate the network on test data
loss, accuracy = network.evaluate(x_test, y_test)
print('Loss =',loss,'\nAccuracy =',accuracy)