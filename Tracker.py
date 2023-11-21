import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# 提供的数据
data_main = [
    [2, 1, 1, 0, 1],
    [3, 4, 1, 0, 4],
    [3, 4, 1, 0, 4],
    [2, 2, 1, 0, 2],
    [2, 2, 1, 0, 2],
    [3, 5, 1, 0, 5],
    [3, 5, 1, 0, 5]
]

data_test1 = [
    [4, 4, 1, 0, 4],
    [3, 4, 1, 0, 4],
    [2, 2, 1, 0, 2],
    [2, 2, 1, 0, 2],
    [3, 5, 1, 0, 5],
    [2, 5, 1, 0, 5]
]

data_test2 = [
    [3, 4, 1, 0, 4],
    [3, 4, 1, 0, 4],
    [2, 2, 1, 0, 2],
    [2, 2, 1, 0, 2],
    [3, 4, 1, 0, 5],
    [2, 5, 1, 0, 5]
]

data_main2 = [
    [2, 1, 1, 0, 1],
    [3, 4, 1, 0, 4],
    [3, 4, 1, 0, 4],
    [2, 2, 1, 0, 2],
    [2, 2, 1, 0, 2],
    [3, 5, 1, 0, 5],
    [99, 5, 1, 0, 5]
]

# 计算FuncEmbedding
def calculate_func_embedding(data):
    sum_data = np.sum(data, axis=0)
    count = len(data)
    return np.append(sum_data, count)

embedding_main = calculate_func_embedding(data_main[1:])  # 从第二行开始计算
embedding_test1 = calculate_func_embedding(data_test1)
embedding_main2 = calculate_func_embedding(data_main2[1:])  # 从第二行开始计算
embedding_test2 = calculate_func_embedding(data_test2)

# 准备数据进行聚类
X = np.array([embedding_main, embedding_test1, embedding_main2,embedding_test2])

# 执行 K-Means 聚类
kmeans = KMeans(n_clusters=2, random_state=0).fit(X)
labels = kmeans.labels_

# 绘图
plt.figure(figsize=(8, 6))
colors = ['blue', 'red']
for i in range(X.shape[0]):
    plt.scatter(X[i, 0], X[i, 1], color=colors[labels[i]], label=f'Function {i+1} - Cluster {labels[i]+1}')

plt.title('FuncEmbedding Clustering')
plt.xlabel('S_DEF + S_USE + S_PTRS + S_CFUNC + S_DVARS')
plt.ylabel('Count')
plt.legend()
plt.show()

(embedding_main, embedding_test1, embedding_main2), labels