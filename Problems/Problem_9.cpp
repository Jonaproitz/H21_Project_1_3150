
#include <armadillo>
#include <iostream>
#include <iomanip>
#include <chrono>

arma::vec func(arma::vec x){
    return 100 * exp(-10*x);
}

int main(int argc,char* argv[]){
    int m = atoi(argv[1]);
    int n = m - 2;

    double h = 1.0 / (m-1);
    arma::vec x_star = arma::linspace(h, 1-h, n);
    arma::vec g = func(x_star) * h * h;

    arma::vec x_0 = arma::vec(1).fill(0.), x_m = arma::vec(1).fill(1.);
    arma::vec x = join_cols(x_0, x_star, x_m);

    arma::vec b_tilde = arma::vec(n);
    b_tilde(0) = 2;

    arma::vec g_tilde = arma::vec(n);
    g_tilde(0) = g(0);
    
    arma::vec v = arma::vec(n);

    // Start measuring time
    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; i++){
        double fac = 1 / b_tilde(i - 1);
        b_tilde(i) = 2 - fac;
        g_tilde(i) = g(i) + fac * g_tilde(i - 1);
    }

    v(n-1) = g_tilde(n-1) / b_tilde(n-1);
    for (int i = n-2; i >= 0; i--){
        v(i) = (g_tilde(i) + v(i+1)) / b_tilde(i);
    }
    // Stop measuring time
    auto t2 = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    double duration_seconds = std::chrono::duration<double>(t2 - t1).count();

    arma::vec v_0 = arma::vec(1).fill(0.), v_m = arma::vec(1).fill(0.);
    arma::vec v_star = join_cols(v_0, v, v_m);

    // Set filename and open file
    std::string filename = "new_approx.txt";
    std::ofstream ofile;
    ofile.open(filename);

    // Set width and precision
    int width = 18;
    int prec = 10;

    // Loop over rows
    for (int i = 0; i < m; i++)
    {
        // Write relevant values to file
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x(i)
              << std::setw(width) << std::setprecision(prec) << std::scientific << v_star(i)
              << std::endl;
    }

    ofile.close();
    return 0;
}