#include <catch2/catch_test_macros.hpp>
#include <threadpool/pool.hpp>

TEST_CASE("[POOL]") {
    threadpool::pool pool;
    unsigned int steps = 5;
    unsigned int counter = 0;
    std::mutex counter_mutex;

    for (int i = 0; i < steps; i++) {
        pool.push([&] {
            std::unique_lock<std::mutex> lock(counter_mutex);
            counter++;
        });
    }

    pool.start();

    while (pool.busy()) {}

    CHECK(steps == counter);
}