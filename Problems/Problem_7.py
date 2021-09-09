import numpy as np
import matplotlib.pyplot as plt
import os    

N = [10, 100, 1000]
plt.figure()
plt.title("", fontsize=15)
for N in N:
    os.system(f"~/Documents/Sem_7/FYS3150/Project_1/Problems/Problem_7.exe {N}")
    x, v = np.transpose(np.loadtxt("approx.txt"))
    plt.plot(x, v, label=f"{N}")

A = np.loadtxt("matrix.txt")
A_T = np.transpose(A)

plt.plot(A_T[0], A_T[1], label="$u(x)$", linestyle="--")

plt.grid()
plt.legend()
plt.show()