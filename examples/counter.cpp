#include <iostream>
#include <simplethreadpool/pool.hpp>

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

  while (p.busy()) {
  }

  std::cout << counter << std::endl;
}