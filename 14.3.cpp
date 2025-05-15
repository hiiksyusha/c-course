#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>

// Атомарные счетчики 
std::atomic<long long> total_in_circle(0);
std::atomic<long long> total_points(0);

void monte_carlo_pi(long long iterations) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    
    long long local_in_circle = 0;
    
    for (long long i = 0; i < iterations; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        if (x*x + y*y <= 1.0) {
            local_in_circle++;
        }
    }
    
    total_in_circle += local_in_circle;
    total_points += iterations;
}

int main() {
    const int num_threads = std::thread::hardware_concurrency();
    const long long total_iterations = 100000000LL; // 100 миллионов точек
    const long long iterations_per_thread = total_iterations / num_threads;
    
    std::cout << "Вычисление π методом Монте-Карло" << std::endl;
    std::cout << "Используем " << num_threads << " потоков" << std::endl;
    
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();
    
    // Создаем потоки
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(monte_carlo_pi, iterations_per_thread);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Вычисляем π
    double pi_estimate = 4.0 * total_in_circle / total_points;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Результат: π ≈ " << pi_estimate << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;
    
    return 0;
}