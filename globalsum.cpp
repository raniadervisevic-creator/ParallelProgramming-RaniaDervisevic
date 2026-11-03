#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <string>

// 1. NAIVE DOUBLE SUMMATION
double sum_naive(const std::vector<double>& v) {
    double s = 0.0;
    for (double x : v) s += x;
    return s;
}

// 2. LONG DOUBLE SUMMATION
double sum_long_double(const std::vector<double>& v) {
    long double s = 0.0;
    for (double x : v) s += x;
    return static_cast<double>(s);
}

// 3. PAIRWISE SUMMATION
double sum_pairwise_rec(const double* arr, long n) {
    if (n <= 128) {
        double s = 0.0;
        for (long i = 0; i < n; ++i) s += arr[i];
        return s;
    }
    long mid = n / 2;
    return sum_pairwise_rec(arr, mid) + sum_pairwise_rec(arr + mid, n - mid);
}

double sum_pairwise(const std::vector<double>& v) {
    return sum_pairwise_rec(v.data(), v.size());
}

// 4. KAHAN SUMMATION
double sum_kahan(const std::vector<double>& v) {
    double sum = 0.0;
    double c = 0.0;
    for (double x : v) {
        double y = x - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

// 5. KNUTH SUMMATION (TwoSum)
void two_sum(double a, double b, double &s, double &t) {
    s = a + b;
    double a_prime = s - b;
    double b_prime = s - a_prime;
    double da = a - a_prime;
    double db = b - b_prime;
    t = da + db;
}

double sum_knuth(const std::vector<double>& v) {
    double sum = 0.0;
    double err = 0.0;
    for (double x : v) {
        double s, t;
        two_sum(sum, x, s, t);
        sum = s;
        err += t;
    }
    return sum + err;
}

int main() {
    std::cout << "GLOBAL SUM PRECISION AND PERFORMANCE TEST\n";
    std::cout << "=======================================\n\n";

    std::vector<int> powers = {10, 12, 14, 16};

    for (int p : powers) {
        long N = 1L << p; // 2^p elements

        std::vector<double> data(N);
        long double exact_sum_ld = 0.0;
        for (long i = 0; i < N; ++i) {
            double val = 0.05 + 1e-12 * (i % 100);
            data[i] = val;
            exact_sum_ld += val;
        }

        double reference_sum = static_cast<double>(exact_sum_ld);

        std::cout << "=======================================\n";
        std::cout << "ARRAY SIZE: 2^" << p << " = " << N << " elements\n";
        std::cout << "Reference sum: " << std::fixed << std::setprecision(14) << reference_sum << "\n\n";

        auto benchmark = [&](const std::string& name, double (*func)(const std::vector<double>&)) {
            auto start = std::chrono::high_resolution_clock::now();
            double res = func(data);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            double error = std::abs(res - reference_sum);

            std::cout << std::left << std::setw(16) << name
                      << "| Error: " << std::scientific << std::setprecision(12) << error
                      << " | Runtime: " << std::fixed << std::setprecision(6) << duration.count() << " s\n";
        };

        benchmark("Standard double", sum_naive);
        benchmark("Long double",     sum_long_double);
        benchmark("Pairwise",        sum_pairwise);
        benchmark("Kahan",           sum_kahan);
        benchmark("Knuth",           sum_knuth);
        std::cout << "\n";
    }

    return 0;
}
