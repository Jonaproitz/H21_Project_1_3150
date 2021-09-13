import numpy as np
import matplotlib.pyplot as plt
import os

def setuptime(N):
    t_1 = np.zeros(10)
    t_2 = np.zeros(10)
    for n in range(10):
        os.system(f"~/Documents/Sem_7/FYS3150/Project_1/Problems/Problem_7.exe {N}")
        t_1[n] = np.loadtxt("time.txt")
        os.system(f"~/Documents/Sem_7/FYS3150/Project_1/Problems/Problem_9.exe {N}")
        t_2[n] = np.loadtxt("time.txt")
    t_1 = np.mean(t_1)
    t_2 = np.mean(t_2)
    return t_1, t_2


N = [1e1, 1e2, 1e3, 1e4, 1e5, 1e6]
t_1 = np.zeros(len(N))
t_2 = np.zeros(len(N))

for i in range(len(N)):
    t_1[i], t_2[i] = setuptime(N[i])

plt.figure()
plt.title("Time comparison")

plt.plot(np.log10(N), np.log10(t_1), label="General algorithm")
plt.plot(np.log10(N), np.log10(t_2), label="Special algorithm")

plt.xlabel("log(N)")
plt.ylabel("log(time)")

plt.legend()
plt.savefig("time_comparison.pdf")