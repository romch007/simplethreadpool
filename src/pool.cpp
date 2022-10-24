#include <threadpool/pool.hpp>

namespace threadpool {
    pool::pool() : pool(std::thread::hardware_concurrency()) {}

    pool::pool(unsigned int max_threads) : m_max_workers(max_threads) {}

    pool::~pool() {
        stop();
    }

    unsigned int pool::max_workers() const { return m_max_workers; }

    void pool::push(const std::function<void()> &job) {
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_jobs.push(job);
        }
        m_mutex_condition.notify_one();
    }

    void pool::start() {
        m_threads.resize(m_max_workers);
        for (int i = 0; i < m_max_workers; i++)
            m_threads.at(i) = std::thread(&pool::thread_loop, this);
    }

    void pool::thread_loop() {
        while (true) {
            std::function<void()> job;
            {
                std::unique_lock<std::mutex> lock(m_queue_mutex);
                m_mutex_condition.wait(lock, [this] {
                    return !m_jobs.empty() || m_should_terminate;
                });
                if (m_should_terminate) return;
                job = m_jobs.front();
                m_jobs.pop();
            }
            job();
        }
    }

    bool pool::busy() {
        bool is_busy;
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            is_busy = !m_jobs.empty();
        }
        return is_busy;
    }

    void pool::stop() {
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_should_terminate = true;
        }
        m_mutex_condition.notify_all();
        for (auto& active_thread : m_threads)
            active_thread.join();
        m_threads.clear();
    }
}
