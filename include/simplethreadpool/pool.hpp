#pragma once

#ifndef SIMPLETHREADPOOL_POOL_HPP
#define SIMPLETHREADPOOL_POOL_HPP

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <simplethreadpool/config.hpp>
#include <thread>

namespace simplethreadpool {
  class SIMPLETHREADPOOL_API pool {
   public:
    /**
     * Construct a thread pool with a number of worker corresponding to hardware
     * max threads
     */
    pool();

    /**
     * Construct a thread pool
     * @param max_threads Max workers in the thread pool
     */
    explicit pool(unsigned int max_threads);
    ~pool();

    pool(const pool&) = delete;
    pool(pool&&) noexcept = delete;

    pool& operator=(const pool&) = delete;
    pool& operator=(pool&&) noexcept = delete;

    /**
     * Get the max number of workers
     * @return The max number of workers
     */
    [[nodiscard]] unsigned int max_workers() const;

    /**
     * Start the thread pool
     */
    void start();

    /**
     * Push a new job to the thread pool
     * @param job The new job
     */
    void push(const std::function<void()>& job);

    /**
     * Check if the thread pool is currently running tasks
     * @return If the thread pool is busy
     */
    bool busy();

    /**
     * Stop the thread pool
     */
    void stop();

   private:
    void thread_loop();

    unsigned int m_max_workers;
    bool m_should_terminate = false;
    std::mutex m_queue_mutex;
    std::condition_variable m_mutex_condition;
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_jobs;
  };
}  // namespace simplethreadpool

#endif
