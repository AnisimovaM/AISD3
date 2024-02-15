import matplotlib.pyplot as plt
import numpy as np

def graph(path):
    comp_count, copy_count = np.loadtxt(path, unpack=True)
    # Построение графика
    x = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000]
    plt.plot(x, comp_count, marker='o', linestyle=':')
    plt.plot(x, copy_count, marker='o', linestyle=':')
    #plt.plot(x,  [y**2 for y in x])
    # plt.plot(x,  [y*np.log2(y) for y in x])
    plt.title('Stat')
    plt.xlabel('X')
    plt.ylabel('Y')

    plt.xscale('log')

    plt.show()

graph('C:\\Users\\Сергей\\Desktop\\masha\\naturale_two_way_sort.txt')
