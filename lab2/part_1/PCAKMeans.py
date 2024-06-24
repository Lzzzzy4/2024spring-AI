from sklearn.datasets import load_wine
import numpy as np 
import matplotlib.pyplot as plt
import numpy.linalg as LA
from gensim.models import KeyedVectors


def get_kernel_function(kernel:str):
    # TODO: implement different kernel functions 
    if kernel == "rbf":
        def rbf(x1, x2, gamma=1.0):
            return np.exp(-gamma * LA.norm(x1 - x2) ** 2)
        return rbf
    elif kernel == "linear":
        def linear(x1, x2):
            return np.dot(x1, x2)
        return linear
    return None

class PCA:
    def __init__(self, n_components:int=2, kernel:str="rbf") -> None:
        self.n_components = n_components
        self.kernel_f = get_kernel_function(kernel)
        # ...

    def fit(self, X:np.ndarray):
        # X: [n_samples, n_features]
        # TODO: implement PCA algorithm
        #对所有样本进行中心化
        X = X - np.mean(X, axis=0)
        X = X.T
        #利用核函数计算协方差矩阵
        n_samples = X.shape[0]
        cov = np.zeros((n_samples, n_samples))
        for i in range(n_samples):
            for j in range(n_samples):
                cov[i, j] = self.kernel_f(X[i], X[j])
        #计算特征值和特征向量
        eig_val, eig_vec = LA.eig(cov)
        #对特征值进行排序
        idx = np.argsort(-eig_val)
        #取前n_components个特征向量
        self.components = eig_vec[:, idx[:self.n_components]]
        print(f"components: {self.components.shape}")
        X = X.T

    def transform(self, X:np.ndarray):
        # X: [n_samples, n_features]
        X_reduced = np.zeros((X.shape[0], self.n_components))

        # TODO: transform the data to low dimension
        print(f"X: {X.shape}")
        for i in range(X.shape[0]):
            # print(i)
            for j in range(self.n_components):
                X_reduced[i, j] = np.dot(X[i], self.components[:, j])
        return X_reduced

class KMeans:
    def __init__(self, n_clusters:int=3, max_iter:int=10) -> None:
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.centers = None
        self.labels = None

    # Randomly initialize the centers
    def initialize_centers(self, points):
        # points: (n_samples, n_dims,)
        n, d = points.shape

        self.centers = np.zeros((self.n_clusters, d))
        for k in range(self.n_clusters):
            # use more random points to initialize centers, make kmeans more stable
            random_index = np.random.choice(n, size=10, replace=False)
            self.centers[k] = points[random_index].mean(axis=0)
        
        return self.centers
    
    # Assign each point to the closest center
    def assign_points(self, points):
        # points: (n_samples, n_dims,)
        # return labels: (n_samples, )
        n_samples, n_dims = points.shape
        self.labels = np.zeros(n_samples)
        # TODO: Compute the distance between each point and each center
        # and Assign each point to the closest center
        for i in range(n_samples):
            min_dist = float('inf')
            for j in range(self.n_clusters):
                dist = LA.norm(points[i] - self.centers[j])
                if dist < min_dist:
                    min_dist = dist
                    self.labels[i] = j
        return self.labels

    # Update the centers based on the new assignment of points
    def update_centers(self, points):
        # points: (n_samples, n_dims,)
        # TODO: Update the centers based on the new assignment of points
        for i in range(self.n_clusters):
            self.centers[i] = points[self.labels == i].mean(axis=0)
        return self.centers

    # k-means clustering
    def fit(self, points):
        # points: (n_samples, n_dims,)
        # TODO: Implement k-means clustering
        self.centers = self.initialize_centers(points)
        for i in range(self.max_iter):
            labels = self.assign_points(points)
            centers = self.update_centers(points)
            if np.all(labels == self.labels):
                break
            self.labels = labels
            self.centers = centers

    # Predict the closest cluster each sample in X belongs to
    def predict(self, points):
        # points: (n_samples, n_dims,)
        # return labels: (n_samples, )
        return self.assign_points(points)
    
def load_data():
    words = [
        'computer', 'laptop', 'minicomputers', 'PC', 'software', 'Macbook',
        'king', 'queen', 'monarch','prince', 'ruler','princes', 'kingdom', 'royal',
        'man', 'woman', 'boy', 'teenager', 'girl', 'robber','guy','person','gentleman',
        'banana', 'pineapple','mango','papaya','coconut','potato','melon',
        'shanghai','HongKong','chinese','Xiamen','beijing','Guilin',
        'disease', 'infection', 'cancer', 'illness', 
        'twitter', 'facebook', 'chat', 'hashtag', 'link', 'internet',
    ]
    w2v = KeyedVectors.load_word2vec_format('./data/GoogleNews-vectors-negative300.bin', binary = True)
    vectors = []
    for w in words:
        vectors.append(w2v[w].reshape(1, 300))
    vectors = np.concatenate(vectors, axis=0)
    return words, vectors

if __name__=='__main__':
    words, data = load_data()
    #翻转
    print(f"data:{data.shape}")
    pca = PCA(n_components=2, kernel='linear')
    pca.fit(data)
    data_pca = pca.transform(data)
    print(f"data_pca:{data_pca.shape}")
    print(data_pca)

    kmeans = KMeans(n_clusters=7)
    kmeans.fit(data_pca)
    clusters = kmeans.predict(data_pca)

    # plot the data
    
    plt.figure()
    plt.scatter(data_pca[:, 0], data_pca[:, 1], c=clusters)
    for i in range(len(words)):
        plt.annotate(words[i], data_pca[i, :]) 
    plt.title("Your student ID")
    plt.savefig("PCA_KMeans.png")