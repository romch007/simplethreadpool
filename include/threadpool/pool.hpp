#pragma once

#ifndef THREADPOOL_POOL_HPP
#define THREADPOOL_POOL_HPP

#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace threadpool {
    class pool {
    public:
        pool();
        explicit pool(unsigned int max_threads);
        ~pool();

        pool(const pool&) = delete;
        pool(pool&&) noexcept = delete;

        pool& operator=(const pool&) = delete;
        pool& operator=(pool&&) noexcept = delete;

        [[nodiscard]] unsigned int max_workers() const;

        void start();
        void push(const std::function<void()>& job);
        bool busy();
        void stop();

    private:
        void thread_loop();

        unsigned int m_max_workers;
        bool should_terminate = false;
        std::mutex m_queue_mutex;
        std::condition_variable m_mutex_condition;
        std::vector<std::thread> m_threads;
        std::queue<std::function<void()>> m_jobs;
    };
}

#endif
