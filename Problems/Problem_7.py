import numpy as np
import matplotlib.pyplot as plt
import os    

N = [10, 100, 1000]
plt.rc("xtick", labelsize=13)
plt.rc("ytick", labelsize=13)
plt.figure()
plt.title("Comparison of analytical and numerical solutions", fontsize=15)
for N in N:
    os.system(f"~/Documents/Sem_7/FYS3150/Project_1/Problems/Problem_7.exe {N}")
    x, v = np.transpose(np.loadtxt("approx.txt"))
    plt.plot(x, v, label=f"N = {N}")

A = np.loadtxt("matrix.txt")
A_T = np.transpose(A)

plt.plot(A_T[0], A_T[1], label="$u(x)$", linestyle="--")

plt.xlabel("x")
plt.grid()
plt.legend()
plt.savefig("comparison.pdf")