from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import numpy as np 
import pandas as pd 
import copy
import tqdm

discrete_features_size = {'Gender':2, 'CALC':4, 'FAVC':2, 'SCC':2, 'SMOKE':2, 'family_history_with_overweight':2, 'CAEC':4, 'MTRANS':5}
continue_features = ['Age', 'Height', 'Weight', 'FCVC', 'NCP', 'CH2O', 'FAF', 'TUE']

# metrics
def accuracy(y_true, y_pred):
    return sum(y_true == y_pred) / len(y_true)

# model
class DecisionTreeClassifier:
    class Node:
        def __init__(self, feature=None, threshold=None, value=None):
            self.feature = feature
            self.threshold = threshold
            self.value = value
            self.child = []

        def next_node(self, X):
            # print(f"feature: {self.feature}, threshold: {self.threshold}, Xvalue: {X[self.feature]}")
            if self.value is not None:
                return self.value
            if self.feature in continue_features:
                if X[self.feature] <= self.threshold:
                    return self.child[0]
                else:
                    return self.child[1]
            else:
                # print(f"feature: {self.feature}, Xvalue: {X[self.feature]}")
                return self.child[int(X[self.feature])]
            
    def __init__(self) -> None:
        self.tree = None
        self.tbar = tqdm.tqdm(total=1500)

    def divide(self, X, y):
        # X = copy.deepcopy(X)
        best_feature = None
        best_threshold = None
        best_gain = -1000
        #计算y的信息熵
        ent = 0
        for i in set(y['NObeyesdad']):
            p = sum(y['NObeyesdad']==i) / len(y['NObeyesdad'])
            ent -= p * np.log2(p)
        #计算信息增益
        for i in X:
            # print(f"feature: {i}")
            if i not in continue_features:
                gain = ent
                for j in set(X[i]):
                    # print(f"value: {j}")
                    #计算条件熵
                    ent_j = 0
                    for k in set(y['NObeyesdad']):
                        # print(f"label: {k}")
                        p = sum((X[i]==j) & (y['NObeyesdad']==k)) / sum(X[i]==j)
                        # print(p)
                        if p != 0: ent_j -= p * np.log2(p)
                    gain -= sum(X[i]==j) / len(X[i]) * ent_j
                # print(f"feature: {i}, gain: {gain}")
                if gain > best_gain:
                    best_gain = gain
                    best_feature = i
            else:
                record = 0
                th = 0
                for threshold in set(X[i]):
                    #计算信息增益
                    gain = ent
                    ent_1 = 0
                    ent_2 = 0
                    for k in set(y['NObeyesdad']):
                        if sum(X[i]<=threshold) > 0: p1 = sum((X[i]<=threshold) & (y['NObeyesdad']==k)) / sum(X[i]<=threshold)
                        else : p1 = 0
                        if sum(X[i]>threshold) > 0:  p2 = sum((X[i]>threshold) & (y['NObeyesdad']==k)) / sum(X[i]>threshold)
                        else : p2 = 0
                        if p1 != 0: ent_1 -= p1 * np.log2(p1)
                        if p2 != 0: ent_2 -= p2 * np.log2(p2)
                    gain -= sum(X[i]<=threshold) / len(X[i]) * ent_1 + sum(X[i]>threshold) / len(X[i]) * ent_2
                    if gain > record:
                        record = gain
                        th = threshold
                    if gain > best_gain:
                        best_gain = gain
                        best_feature = i
                        best_threshold = threshold
                # print(f"feature: {i}, gain: {record} threshold: {th}")

        return best_feature, best_threshold

    def fit(self, X, y):
        self.tree = self.generate_node(X, y)

    def generate_node(self, X, y):
        # X: [n_samples_train, n_features], 
        # y: [n_samples_train, ],
        # TODO: implement decision tree algorithm to train the model
        #生成节点
        self.tbar.update(1)
        X = X.reset_index(drop=True)
        y = y.reset_index(drop=True)
        new_node = self.Node()
        y_list = list(np.array(y).reshape(-1))
        #如果所有样本都属于同一类别，则标记为叶节点，return
        if len(set(y_list)) == 1:
            new_node.value = y_list[0]
            return new_node
        #如果A为空，或者D中样本在A上取值相同，则标记为叶节点，值为D中样本数最多的类，return
        def check_eq(X):
            for i in X:
                if len(set(X[i])) != 1:
                    return False
            return True
        max_cnt = 0
        for i in set(y_list):
            if sum(y_list==i) > max_cnt:
                max_cnt = sum(y_list==i)
        if len(X.columns) == 0 or check_eq(X):
            new_node.value = max_cnt
            return new_node
        #选择最优划分特征
        best_feature, best_threshold = self.divide(X, y)
        print(f"best_feature: {best_feature}, best_threshold: {best_threshold}")
        new_node.feature = best_feature
        new_node.threshold = best_threshold
        if best_feature in continue_features:
            X1 = X[X[best_feature] <= best_threshold].drop(columns=[best_feature])
            y1 = y[X[best_feature] <= best_threshold]
            X2 = X[X[best_feature] > best_threshold].drop(columns=[best_feature])
            y2 = y[X[best_feature] > best_threshold]
            if len(y1) != 0: new_node.child.append(self.generate_node(X1, y1))
            else: new_node.child.append(self.Node(value=max_cnt))
            if len(y2) != 0: new_node.child.append(self.generate_node(X2, y2))
            else: new_node.child.append(self.Node(value=max_cnt))
        else:
            for i in range(discrete_features_size[best_feature]):
                X_i = X[X[best_feature] == i].drop(columns=[best_feature])
                y_i = y[X[best_feature] == i]
                if len(y_i) != 0: new_node.child.append(self.generate_node(X_i, y_i))
                else: new_node.child.append(self.Node(value=max_cnt))
        return new_node
        
    def predict(self, X):
        # X: [n_samples_test, n_features],
        # return: y: [n_samples_test, ]
        y = np.zeros(X.shape[0])
        # TODO:
        for i in range(X.shape[0]):
            node = self.tree
            while node.value is None:
                node = node.next_node(X.iloc[i])
            y[i] = node.value
        return y

def load_data(datapath:str='./data/ObesityDataSet_raw_and_data_sinthetic.csv'):
    df = pd.read_csv(datapath)
    # 保留前十分之一的数据
    # df = df[:int(len(df['Age'])/10)]
    discrete_features = ['Gender', 'CALC', 'FAVC', 'SCC', 'SMOKE', 'family_history_with_overweight', 'CAEC', 'MTRANS']
    
    X = df.iloc[:, :-1]
    y = df.iloc[:, -1:]
    # encode discrete str to number, eg. male&female to 0&1
    labelencoder = LabelEncoder()
    for col in discrete_features:
        X[col] = labelencoder.fit(X[col]).transform(X[col])
    y['NObeyesdad'] = labelencoder.fit(y['NObeyesdad']).fit_transform(y['NObeyesdad'])

    print(len(X))
    print(len(X.columns))

    # for i in set(y['NObeyesdad']):
    #     print(i)
    #     print(sum(y['NObeyesdad']==i))

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    # X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.9, random_state=42)

    #将X，Y按序号排序后重命名
    X_train = X_train.reset_index(drop=True)
    y_train = y_train.reset_index(drop=True)
    # print(f"len:{len(X_train['Age'])}")

    return X_train, X_test, y_train, y_test

if __name__=="__main__":
    X_train, X_test, y_train, y_test = load_data('./data/ObesityDataSet_raw_and_data_sinthetic.csv')
    clf = DecisionTreeClassifier()
    clf.fit(X_train, y_train)
    
    y_pred = clf.predict(X_test)
    y_test = np.array(y_test).reshape(-1)
    print("test",accuracy(y_test, y_pred))

    y_pred = clf.predict(X_train)
    y_test = np.array(y_train).reshape(-1)
    print("train",accuracy(y_test, y_pred))