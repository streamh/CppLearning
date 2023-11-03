#include <iostream>
#include "ThreadPool.h"
#include "ThreadPool2.h"
#include <thread>
#include <future>

void myFunction() {
    printf("do the thread method.");
}

void createThreads() {
    //method1
    std::thread myThread1(myFunction);
    myThread1.join();

    //method2
    auto myLambda = [] {
        printf("the lambda function.");
    };
    std::thread myThread2(myLambda);
    myThread2.join();

    //method3
    void (*functionPointer)() = myFunction;
    std::thread myThread3(functionPointer);
    myThread3.join();

    //method4;
    std::future<void> result = std::async(std::launch::async, myLambda);
    result.get();

    //method5
    //OpenMP?
    /*
    #pragma omp parallel
    {
        // 并行执行的代码
    }
    */
}

int main() {
//    ThreadPool pool(4);
//
//    for (int i = 0; i < 8; ++i) {
//        auto task = std::make_shared<Task>(TaskPriority::Normal, "Task" + std::to_string(i));
//        pool.addTask(task);
//    }
//
//    std::this_thread::sleep_for(std::chrono::seconds(5)); // 等待任务完成

    ThreadPool2 pool(4); // 创建一个具有4个线程的线程池

    for (int i = 0; i < 8; ++i) {
        pool.AddTask([i] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Task " << i << " executed by thread " << std::this_thread::get_id() << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5)); // 等待任务完成

    //methods on how to creat the Threads
    createThreads();

    return 0;
}

