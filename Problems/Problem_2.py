import numpy as np
import matplotlib.pyplot as plt

def p(filename):
	A = np.loadtxt(filename)
	A = np.transpose(A)
	
	plt.figure()
	plt.title("")

	plt.plot(A[0], A[1])

	plt.show()

p("matrix.txt")

