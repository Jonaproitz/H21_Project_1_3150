
#include <armadillo>
#include <iomanip>
#include <iostream>
#include <chrono>

arma::vec f_i(arma::vec x){
    arma::vec val = 100 * exp(-10*x);
    return val;
}

int main(int argc, char* argv[]){
    // Initial setup of necessary vectors
    int m = atoi(argv[1]);
    arma::vec x = arma::linspace(0, 1, m);
    double h = 1.0 / (m-1);
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

    arma::vec v_star_1 = arma::vec(1).fill(v_0), v_star_m = arma::vec(1).fill(v_m);

    // Start measuring time
    auto t1 = std::chrono::high_resolution_clock::now();

    // Running over steps in the algorithm
    b_tilde(0) = b(0);
    g_tilde(0) = g(0);
    for (int i = 1; i < n; i++){
        double fac = a(i)/b_tilde(i-1);
        b_tilde(i) = b(i) - fac*c(i-1);
        g_tilde(i) = g(i) - fac*g_tilde(i-1);
    }

    v(n-1) = g_tilde(n-1)/b_tilde(n-1);
    for (int i = n-2; i >= 0; i--){
        v(i) = (g_tilde(i) - c(i)*v(i+1)) / b_tilde(i);
    }
    
    // Stop measuring time
    auto t2 = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    double duration_seconds = std::chrono::duration<double>(t2 - t1).count();
    std::string timefile = "time.txt";
    std::ofstream tfile;
    tfile.open(timefile);

    int timewidth = 12;
    int timeprec = 4;

    tfile << std::setw(timewidth) << std::setprecision(timeprec) << std::scientific << duration_seconds << std::endl;

    tfile.close();
    // Implement solution into the complete solution
    arma::vec v_star = join_cols(v_star_1, v, v_star_m);

    // Set filename and open file
    std::string filename = "approx.txt";
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