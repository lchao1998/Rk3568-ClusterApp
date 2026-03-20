/**@file  		ThreadPool.h
* @brief    	Thread pool
* @details  	Make pool of thread . but the max thread count is 10.
* @author		xuqiang
* @email		xu.qiang@zlingsmart.com
* @date			2023-06-20
* @version		V0.0.1
* @copyright	Copyright (c) 2023-2024  ZlingSmart Company Ltd.
**********************************************************************************
* @attention
* 硬件平台: (可选) \n
* SDK版本： (可选)
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2023/04/17  <td>1.0      <td>zlingsmart  <td>创建初始版本
* </table>
*
**********************************************************************************
*/
#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(int numThreads) : m_numThreads(numThreads), m_stop(false) {
        if (numThreads > 10)
        {
            m_numThreads = 10;
        }
        for (int i = 0; i < m_numThreads; ++i) {
            m_threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(m_queueMutex);
                        m_condition.wait(lock, [this] { return m_stop || !m_taskQueue.empty(); });
                        if (m_stop && m_taskQueue.empty())
                            return;
                        task = std::move(m_taskQueue.front());
                        m_taskQueue.pop();
                    }
                    task();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_stop = true;
        }
        m_condition.notify_all();
        for (std::thread& thread : m_threads)
            thread.join();
    }

    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_taskQueue.emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        }
        m_condition.notify_one();
    }

private:
    int m_numThreads;
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_taskQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_condition;
    bool m_stop;
};
