import tensorflow as tf
from tensorflow import keras

import numpy as np
import matplotlib.pyplot as np

((train_data,train_labels),(eval_data,eval_labels)) = tf.keras.datasets.mnist.load_data()

train_size = train_data.shape
train_labels_size = train_labels.shape

with open('train_data.txt', 'w') as train_file:

 for h in range(1000):
  for i in range (28):
   train_file.write('\n')
   for j in range(28):
    train_file.write(str(train_data[h][i][j])+'   ')
  train_file.write('\n')
