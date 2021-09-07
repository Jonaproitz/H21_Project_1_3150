
#include <armadillo>

arma::vec u(arma::vec x){
    arma::vec val = 1 - (1 - exp(-10)) * x - exp(-10*x);
    return val;
}

int init(){
    return 0;
}