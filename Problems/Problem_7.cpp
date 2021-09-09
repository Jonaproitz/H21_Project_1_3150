
#include <armadillo>
#include <iomanip>
#include <iostream>

arma::vec f_i(arma::vec x){
    arma::vec val = 100 * exp(-10*x);
    return val;
}

int main(int argc, char* argv[]){
    // Initial setup of necessary vectors
    int m = atoi(argv[1]);
    arma::vec x = arma::linspace(0, 1, m);
    double h = x(1) - x(0);
    arma::vec f = f_i(x) * h*h;

    double v_0 = 0;
    double v_m = 0;

    int n = m - 2;

    arma::vec g = arma::vec(n);
    for (int i = 0; i < n; i++){
        g(i) = f(i+1);
    }
    
    g(0) = g(0) + v_0;
    g(n-1) = g(n-1) + v_m;

    arma::vec a = arma::vec(n).fill(-1.);
    arma::vec b = arma::vec(n).fill(2.);
    arma::vec c = arma::vec(n).fill(-1.);

    arma::vec b_tilde = arma::vec(n);
    arma::vec g_tilde = arma::vec(n);
    arma::vec v = arma::vec(n);

    // Running over steps in the algorithm
    b_tilde(0) = b(0);
    g_tilde(0) = g(0);
    for (int i = 1; i < n; i++){
        double fac = a(i)/b_tilde(i-1);
        b_tilde(i) = b(i) - fac*c(i-1);
        g_tilde(i) = g(i) - fac*g_tilde(i-1);
    }
    //g_tilde.print();
    v(n-1) = g_tilde(n-1)/b_tilde(n-1);
    for (int i = n-2; i >= 0; i--){
        v(i) = (g_tilde(i) - c(i)*v(i+1)) / b_tilde(i);
    }
    v.print();

    return 0;
}