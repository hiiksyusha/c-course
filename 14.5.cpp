#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>

// Функция, которая долго вычисляет результат
int long_computation(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x; // Простое вычисление для примера
}

int main() {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    // Преобразуем future в shared_future
    std::shared_future<int> shared_fut = future.share();
    
    // Функция для потоков, которая использует shared_future
    auto worker = [](std::shared_future<int> f, int id) {
        std::cout << "Поток " << id << " ждет результат..." << std::endl;
        int result = f.get(); // Блокируется, пока результат не будет готов
        std::cout << "Поток " << id << " получил результат: " << result << std::endl;
    };
    
    // Запускаем 2 потока с одним shared_future
    std::vector<std::thread> threads;
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(worker, shared_fut, i+1);
    }
    
    // вычисления в основном потоке
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Основной поток начинает вычисления..." << std::endl;
    
    promise.set_value(long_computation(15));
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}