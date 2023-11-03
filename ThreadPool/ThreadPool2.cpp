//
// Created by Stream Hu on 2023/11/2.
//

#include "ThreadPool2.h"

ThreadPool2::ThreadPool2(int numThreads) : running(true) {
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this] {
                        return !running || !tasks.empty();
                    });

                    if (!running && tasks.empty()) {
                        return;
                    }

                    task = std::move(tasks.front());
                    tasks.pop();
                }

                task();
            }
        });
    }
}

ThreadPool2::~ThreadPool2() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        running = false;
    }

    condition.notify_all();

    for (std::thread& worker : workers) {
        worker.join();
    }
}

void ThreadPool2::AddTask(std::function<void()> task) {
    if (!running) {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(task);
    }

    condition.notify_one();
}