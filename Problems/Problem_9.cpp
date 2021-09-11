
#include <armadillo>
#include <iostream>
#include <iomanip>

arma::vec func(arma::vec x){
    return 100 * exp(-10*x);
}

int main(int argc,char* argv[]){
    int m = atoi(argv[1]);
    int n = m - 2;

    double dt = 1.0 / (m-1);
    arma::vec g = func(arma::linspace(dt, 1-dt, n));

    arma::vec b_tilde = arma::vec(n);
    b_tilde(0) = 2;

    arma::vec g_tilde = arma::vec(n);
    g_tilde(0) = g(0);
    
    arma::vec v = arma::vec(n);



    return 0;
}