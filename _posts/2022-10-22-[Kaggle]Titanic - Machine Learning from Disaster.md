---
layout : post
title : Titanic - Machine Learning from Disaster
comments : true
categories : 
- python
tags : [python]
---
# Titanic - Machine Learning from Disaster

![titanic.PNG](./img/titanic.png)

```python
import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import cross_val_score
train = pd.read_csv('./train.csv')
# 결측값
age_avg = train['Age'].mean(skipna=True)
fare_avg = train['Fare'].mean(skipna=True)
train['Age'] = train['Age'].fillna(age_avg)
train['Fare'] = train['Fare'].fillna(fare_avg)

# dict 형으로 문자열을 숫자로 변환
train['Sex'] = train['Sex'].map({'male' : 0, 'female' : 1})
train['Embarked'] = train['Embarked'].map({'S' : 0, 'Q' : 1, 'C' : 2})
train['Embarked'] = train['Embarked'].fillna(0)
#-------------------------------------------------------------------------------
train_x = train[['Pclass', 'SibSp', 'Sex', 'Age', 'Fare', 'Embarked']]
train_y = train['Survived']
# 모델 생성(의사 결정 트리)
"""
DecisionTreeClassifier 분류법
1. 여러가지 독립 변수 중 하나의 독립 변수를 선택하고 그 독립 변수에 대한 기준값(threshold)을 정한다. 이를 분류 규칙이라고 한다. 최적의 분류 규칙을 찾는 방법은 이후에 자세히 설명한다.

2. 전체 학습 데이터 집합(부모 노드)을 해당 독립 변수의 값이 기준값보다 작은 데이터 그룹(자식 노드 1)과 해당 독립 변수의 값이 기준값보다 큰 데이터 그룹(자식 노드 2)으로 나눈다.

3. 각각의 자식 노드에 대해 1~2의 단계를 반복하여 하위의 자식 노드를 만든다. 단, 자식 노드에 한가지 클래스의 데이터만 존재한다면 더 이상 자식 노드를 나누지 않고 중지한다.
"""
# model = DecisionTreeClassifier()
"""
Random Forest 분류법
상위 모델들이 예측하는 편향된 결과보다, 다양한 모델들의 결과를 반영함으로써 더 다양한 데이터에 대한 의사결정을 내릴 수 있게 함.

건강의 위험도를 예측하기 위해서는 많은 요소를 고려 성별, 키, 몸무게, 지역, 운동량, 흡연유무, 음주 여부, 혈당, 근육량, 기초 대사량 등 수많은 요소가 필요
Feature가 30개라 했을 때 30개의 Feature를 기반으로 하나의 결정 트리를 만든다면 트리의 가지가 많아질 것이고, 이는 오버피팅의 결과를 야기
30개의 Feature 중 랜덤으로 5개의 Feature만 선택해서 하나의 결정 트리 생성
계속 반복하여 여러 개의 결정 트리 생성
여러 결정 트리들이 내린 예측 값들 중 가장 많이 나온 값을 최종 예측값으로 지정
이렇게 의견을 통합하거나 여러 가지 결과를 합치는 방식을 앙상블(Ensemble)이라고 함
하나의 거대한 (깊이가 깊은) 결정 트리를 만드는 것이 아니라 여러 개의 작은 결정 트리를 만드는 것
분류 : 여러 개의 작은 결정 트리가 예측한 값들 중 가장 많은 값, 회귀 : 평균
"""
model = RandomForestClassifier()
# 학습하기
model.fit(train_x, train_y)
# 평가하기
scores = cross_val_score(model, train_x, train_y, scoring = 'accuracy', cv = 5) # cross-validation 5
print(scores.mean())
# 테스트 데이터 예측하기
test = pd.read_csv('./test.csv')

test['Age'] = test['Age'].fillna(age_avg)
test['Fare'] = test['Fare'].fillna(fare_avg)
test['Sex'] = test['Sex'].map({'male' : 0, 'female' : 1})
test['Embarked'] = test['Embarked'].map({'S' : 0, 'Q' : 1, 'C' : 2})
test['Embarked'] = test['Embarked'].fillna(0)
test_x = test[['Pclass', 'SibSp', 'Sex', 'Age', 'Fare', 'Embarked']]
test_y_pred = model.predict(test_x)

# 샘플 파일 형식에 맞춰 변환
submission = pd.read_csv("./sample_submission.csv")
submission['Survived'] = test_y_pred
submission.to_csv('submission.csv', index = False)
```


