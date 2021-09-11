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

N = [1e1, 1e2, 1e3, 1e4, 1e5]
x, u, abs_error = fetch_data(N)

plt.figure()
for abs_error_i, x_i in zip(abs_error, x):
    plt.plot(x_i, np.log10(abs_error_i))
plt.show()

rel_error = []
plt.figure()
for abs_error, u, x in zip(abs_error, u, x):
    rel_error.append(abs(abs_error / u))
    plt.plot(x, np.log10(rel_error[-1]))
plt.show()

rel_max = []
for rel_error in rel_error:
    rel_max.append(np.max(rel_error))
print(pandas.DataFrame(zip(N, rel_max), columns=["N", "$max(epsilon_i)$"]))
plt.figure()
plt.plot(np.log10(N), np.log10(rel_max))
plt.show()