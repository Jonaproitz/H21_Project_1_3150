import numpy as np
import matplotlib.pyplot as plt

def p(filename):
	# Fetch data textfile
	A = np.loadtxt(filename)
	
	# Plot data
	A_T = np.transpose(A)
	plt.rc("xtick", labelsize=13)
	plt.rc("ytick", labelsize=13)
	plt.figure()
	plt.title("Exact solution to differential equation", fontsize=15)

	plt.plot(A_T[0], A_T[1])

	plt.xlabel("$x$", fontsize=13)
	plt.ylabel("$u(x)$", fontsize=13)

	plt.grid()
	plt.savefig("exact_solution.pdf")

p("matrix.txt")

