import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
import numpy as np
from scipy.linalg import eigh

def load_data():
    # data = [[1, 2, 4],
    #     [2, 2, 2],
    #     [1, 2, 1],
    #     [3, 2, 3],
    #     [1, 3, 3]
    #     ]
    data = np.random.rand(10, 3)
    data = np.array(data, dtype=np.float64)
    mean = np.mean(data)
    # return centered data
    # redundant for PCA since it is already centered
    # usefull for visualization
    return data-mean

def visualize(data, analysis):
    print("Data:\n", data, "\nData Shape:", data.shape)
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    # Plot data points
    ax.scatter(data[:, 0], data[:, 1], data[:, 2], c='r', marker='o')
    # Plot principal components
    ax.quiver(0, 0, 0, analysis[:, 0], analysis[:, 1], analysis[:, 2], length=.5, color='steelblue')
    plt.show()
    
def analysis(data):
    pca = PCA(n_components=3)
    pca.fit(data)
    # print(pca.explained_variance_ratio_)
    # print(pca.singular_values_)
    return np.array(pca.components_, dtype=np.float32)

def basis_change(data, basis):
    return np.dot(data, basis.T)

def main():
    data = load_data()
    a = analysis(data)
    visualize(data, a)
    print("PCA:\n", a)
    # b = basis_change(data, a)
    # print(b)

if __name__ == '__main__':
    main()