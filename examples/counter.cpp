#include <iostream>
#include <atomic>
#include <simplethreadpool/pool.hpp>

int main() {
  simplethreadpool::pool p;
  std::atomic<int> counter = 0;

  for (int i = 0; i < 100; i++) {
    p.push([&] {
        counter++;
    });
  }

  p.start();

  while (p.busy());

  std::cout << counter << std::endl;
}
