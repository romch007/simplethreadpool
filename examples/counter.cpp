#include <simplethreadpool/pool.hpp>
#include <iostream>

int main() {
    simplethreadpool::pool p;
    int counter = 0;
    std::mutex counter_mutex;

    for (int i = 0; i < 100; i++)
        p.push([&] {
            std::unique_lock<std::mutex> lock(counter_mutex);
            counter++;
        });

    p.start();

    while (p.busy()) {}

    std::cout << counter << std::endl;
}