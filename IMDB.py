from  keras.datasets import imdb
import matplotlib.pyplot as plt

(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=10000)

max([max(sequence) for sequence in train_data])


word_index = imdb.get_word_index()
reverse_word_index = dict([(val, key) for (key, val) in word_index.items()])
decoded_review = ' '.join([reverse_word_index.get(i-3, '?') for i in train_data[0]])

import numpy as np

def vectorize(sequences, dimension=10000): 
		results = np.zeros((len(sequences), dimension))
		for i, sequence in enumerate(sequences):
			results[i, sequence] = 1
		return results

x_train = vectorize(train_data)
x_test = vectorize(test_data)
y_train = np.asarray(train_labels).astype('float32')
y_test = np.asarray(test_labels).astype('float32')


from keras import models
from keras import layers

model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))


model.compile(loss = 'binary_crossentropy',optimizer='rmsprop',  metrics = ['accuracy'])


x_val = x_train[:10000]
y_val = y_train[:10000]

partial_x = x_train[10000:]
partial_y = y_train[10000:]


history = model.fit(partial_x, partial_y, epochs=20, batch_size=512, validation_data=(x_val, y_val))
results = model.evaluate(x_test, y_test)
print(results)

# Plot training & validation loss 
loss_values = history.history['loss'] 
val_loss_values = history.history['val_loss'] 
epochs = range(1, len(loss_values) + 1) 
 
plt.plot(epochs, loss_values, 'bo', label='Training Loss') 
plt.plot(epochs, val_loss_values, 'b', label='Validation Loss') 
plt.title('Training and Validation Loss') 
plt.xlabel('Epochs') 
plt.ylabel('Loss') 
plt.legend() 
plt.show() 
 
# Plot training & validation accuracy 
acc_values = history.history['accuracy'] 
val_acc_values = history.history['val_accuracy'] 
 
plt.plot(epochs, acc_values, 'ro', label='Training Accuracy') 
plt.plot(epochs, val_acc_values, 'r', label='Validation Accuracy') 
plt.title('Training and Validation Accuracy') 
plt.xlabel('Epochs') 
plt.ylabel('Accuracy') 
plt.legend() 
plt.show() 





