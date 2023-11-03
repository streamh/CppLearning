//
// Created by Stream Hu on 2023/11/2.
//

#ifndef THREADPOOL_THREADPOOL2_H
#define THREADPOOL_THREADPOOL2_H

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

class ThreadPool2 : public std::enable_shared_from_this<ThreadPool2> {
public:
    explicit ThreadPool2(int threadNumber = 6);
    ~ThreadPool2();
    void AddTask(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool running;
};


#endif //THREADPOOL_THREADPOOL2_H
