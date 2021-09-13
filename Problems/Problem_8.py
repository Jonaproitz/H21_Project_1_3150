import numpy as np
import matplotlib.pyplot as plt
import os
import pandas


def fetch_data(N):
    abs_error = []; u = []; x = []
    for N in N:
        os.system(f"~/Documents/Sem_7/FYS3150/Project_1/Problems/Problem_2.exe {N}")
        os.system(f"~/Documents/Sem_7/FYS3150/Project_1/Problems/Problem_7.exe {N}")
        x_new, u_new = np.transpose(np.loadtxt("matrix.txt"))
        x_2, v = np.transpose(np.loadtxt("approx.txt"))
        abs_error_new = abs(u_new[1:-1] - v[1:-1])
        abs_error.append(np.array(abs_error_new))
        u.append(np.array(u_new[1:-1]))
        x.append(np.array(x_new[1:-1]))
    return x, u, abs_error 

N = [1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7]
x, u, abs_error = fetch_data(N)
plt.rc("xtick", labelsize=13)
plt.rc("ytick", labelsize=13)

plt.figure()
plt.title("Absolute error", fontsize=15)
for abs_error_i, x_i, N_i in zip(abs_error, x, N):
    plt.plot(x_i, np.log10(abs_error_i), label=f"N = {N_i}")

plt.xlabel("$\\log_{10}(x)$")
plt.ylabel("$\\log_{10}(|u_i - v_i|$")
plt.legend()
plt.savefig("abs_error.pdf")

rel_error = []
plt.figure()
plt.title("Relative error", fontsize=15)
for abs_error, u, x, N_i in zip(abs_error, u, x, N):
    rel_error.append(abs(abs_error / u))
    plt.plot(x, np.log10(rel_error[-1]), label=f"N = {N_i}")

plt.xlabel("$\\log_{10}(x)$")
plt.ylabel("$\\log_{10}(|\\frac{u_i - v_i}{u_i}|)$")
plt.legend()
plt.savefig("rel_error.pdf")

rel_max = []
for rel_error in rel_error:
    rel_max.append(np.max(rel_error))
print(pandas.DataFrame(zip(N, rel_max), columns=["N", "$max(epsilon_i)$"]))
plt.figure()
plt.title("Maximum relative error")
plt.plot(np.log10(N), np.log10(rel_max), "-o", color="black")

plt.xlabel("$\\log_{10}(N)$")
plt.ylabel("$Max(\\epsilon)$")
plt.savefig("max_error.pdf")

"""
    python3 Problem_8.py
            N  $max(epsilon_i)$
0        10.0      9.682820e-02
1       100.0      8.498198e-04
2      1000.0      8.350052e-06
3     10000.0      8.342473e-08
4    100000.0      1.452374e-09
5   1000000.0      8.405051e-07
6  10000000.0      2.983866e-06
"""