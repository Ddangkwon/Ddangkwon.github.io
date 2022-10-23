---
layout : post
title : Digit Recognizer
comments : true
categories : 
- python
tags : [python]
---
# Digit Recognizer

![titanic.PNG](./MNIST.png)

```python
import os
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from keras.utils.np_utils import to_categorical
# cnn을 통해 최종적으로 결과를 받으면 라벨수만큼의 각각의 확률값으로 반환된다. 결과값을 받기 편하게 하기위한 함수
from keras.models import Sequential
# 케라스 모델구성기본 함수
from keras.layers import Dense, Dropout, Flatten, Conv2D, MaxPool2D, BatchNormalization
# 케라스에서 필요한 레이어들 간편하게 쓸수 있다.
from keras.preprocessing.image import ImageDataGenerator
# 이미지를 조금 변화해줌으로써 성능을 올릴수 있다. 그랜드 마스터 Chris Deotte 의 25 Million Images! [0.99757] MNIST 커널에서 참고했다.(그외에도 거의 많이 참고했다.)
from keras.callbacks import EarlyStopping, ModelCheckpoint, ReduceLROnPlateau
# 콜벡 모델이 어떤 기준으로 돌다가 멈추고 저장하고 하는것들을 설정해줄수 있다.
import warnings
from keras.models import load_model
warnings.filterwarnings('ignore')
import tensorflow as tf
# Input data files are available in the read-only "../input/" directory
# For example, running this (by clicking run or pressing Shift+Enter) will list all files under the input directory

train_data = pd.read_csv('./train.csv')
test_data = pd.read_csv('./test.csv')
# X의 라벨값을 CNN에 넣을수 없고 이따 예측비교시 쓸거니까 분리해준다.
Y_train = train_data["label"]
X_train = train_data.drop(labels = ["label"],axis = 1)

# 0~255 사이의 픽셀명암의 숫자를 계산하기 편하기 255로 나눠 비율은 유지하고 숫자는 작게
X_train = X_train / 255.0
X_test = test_data / 255.0
#이제 (28,28) 모양으로 RESHAPE
X_train = X_train.values.reshape(-1,28,28,1)
X_test = X_test.values.reshape(-1,28,28,1)
#아까 뺴놓은 라벨값도 CNN결과값이랑 비교할수 있는 형태로
Y_train = to_categorical(Y_train, num_classes = 10)



datagen = ImageDataGenerator(
        rotation_range=10,
        zoom_range=0.1,
        width_shift_range=0.1,
        height_shift_range=0.1,)
X_train, X_valid, y_train, y_valid = train_test_split(X_train, Y_train, test_size = 0.1)

state = "define model"
if state != "load model":
    model = Sequential()

    model.add(Conv2D(16,kernel_size=3,activation= 'relu', input_shape = (28,28,1) ))
    model.add(BatchNormalization())
    model.add(Conv2D(16,kernel_size=3,activation='relu'))
    model.add(BatchNormalization())
    model.add(Conv2D(16,kernel_size=5,activation = 'relu', padding='same',strides=2))
    model.add(BatchNormalization())
    model.add(Dropout(0.4))

    model.add(Conv2D(32,kernel_size=3,activation= 'relu'))
    model.add(BatchNormalization())
    model.add(Conv2D(32,kernel_size=3,activation='relu'))
    model.add(BatchNormalization())
    model.add(Conv2D(32,kernel_size=5,activation = 'relu', padding='same',strides=2))
    model.add(BatchNormalization())
    model.add(Dropout(0.4))

    model.add(Conv2D(64,kernel_size=4,activation= 'relu'))
    model.add(BatchNormalization())
    model.add(Flatten())
    model.add(Dropout(0.4))
    model.add(Dense(10,activation='softmax'))

    model.summary()
else:
    model = load_model('digit_recognizer.h5')
    model.summary()

# 학습 결과가 수렴할 때 조기에 학습을 종료할 때 사용(현재 disable 상태)
early_stopping = EarlyStopping(patience=100,
                                min_delta=0.001,
                                restore_best_weights=True)

model.compile(optimizer='adam',loss='mean_squared_error',metrics=['accuracy'])

callbacks = [early_stopping]

# 10도 정도 돌리고 10% 정도 줌하고, 왼쪽, 오른쪽 시프트를 해서 다양한 변화를 준 데이터를 추가해준다.(이따 케라스 모델 fit_generator 할때 사용예정)
history = model.fit_generator(datagen.flow(X_train,y_train, batch_size=64),
                              epochs = 100,
                              steps_per_epoch = X_train.shape[0]//64,
                              validation_data = (X_valid,y_valid),
                              callbacks=callbacks,
                              verbose=1)

model.save('digit_recognizer.h5')

results = model.predict(X_test)
results = np.argmax(results,axis = 1)
results = pd.Series(results,name="Label")
submission = pd.concat([pd.Series(range(1,28001),name = "ImageId"),results],axis = 1)
submission.to_csv("submission.csv",index=False)

# 모델 로드 및 예측 사용
"""
model = load_model('digit_recognizer.h5')
model.summary()
test_num = plt.imread('img_1.jpg')
test_num = test_num[:,:,0]
test_num = (test_num > 125) * test_num
test_num = test_num.astype('float32') / 255.0
test_num = test_num.reshape((1, 28, 28, 1))
answer = model.predict(test_num)
answer = np.argmax(answer,axis = 1)
print(answer)

"""

```


