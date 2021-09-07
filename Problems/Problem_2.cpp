
#include <armadillo>
#include <iomanip>

arma::vec u(arma::vec x){
    arma::vec val = 1 - (1 - exp(-10)) * x - exp(-10*x);
    return val;
}

int main(int argc, char* argv[]){
    // Create x array and Nx2 Matrix to store it and u(x)
    int N = atoi(argv[1]);
    arma::vec x = arma::linspace(0, 1, N);
    arma::mat A = arma::mat(N, 2);

    // Set columns of A matrix to x and u(x)
    A.col(0) = x;
    A.col(1) = u(x);
    
    // Set filename
    std::string filename = "matrix.txt";

    // Create and open the file
    std::ofstream ofile;
    ofile.open(filename);

    // Set width and precision
    int width = 12;
    int prec = 4;

    // Loop over rows
    for (int i = 0; i < N; i++)
    {
        // Write line with current row in A
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << A(i, 0)
              << std::setw(width) << std::setprecision(prec) << std::scientific << A(i, 1)
              << std::endl;
    }

    // Close output file
    ofile.close();
    return 0;
}