# threadpool library

Simple C++ thread pool library

## Installation

## Usage

```cpp
#include <threadpool/pool.hpp>

int main() {
    threadpool::pool p;
    
    int counter = 0;
    std::mutex counter_mutex;
    
    for (int i = 0; i < 5; i++) {
        p.push([&] {
            std::unique_lock<std::mutex> lock(counter_mutex);
            counter++;
            // do some stuff
        })
    }
    
    p.start();
    
    while (p.busy()); // wait for all the jobs to be finished
    
    std::cout << counter << std::endl;
}
```
