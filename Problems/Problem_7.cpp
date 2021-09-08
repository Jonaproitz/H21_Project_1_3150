
#include <armadillo>
#include <iomanip>

arma::vec f_i(arma::vec x){
    arma::vec val = 100 * exp(-10*x);
    return val;
}

int main(int argc, char* argv[]){

    return 0;
}