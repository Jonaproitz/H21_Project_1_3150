
#include <armadillo>

arma::vec u(arma::vec x){
    arma::vec val = 1 - (1 - exp(-10)) * x - exp(-10*x);
    return val;
}

int main(int argc, char* argv[]){
    int N = atoi(argv[1]);
    arma::vec x = arma::linspace(0, 1, N);
    arma::mat A = arma::mat(N, 2);
    A.col(0) = x;
    A.col(1) = u(x);
    A.save("matrix.bin");
    return 0;
}