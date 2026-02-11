#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<thread>
#include<vector>
#include<queue>
#include<condition_variable>
#include<mutex>
#include<functional>
#include<stdexcept>
namespace server{
    class ThreadPool{
        public:
            ThreadPool(size_t threadCounts);
            ~ThreadPool();
            void enqueue(std::function<void()> task);
        private:
            std::vector<std::thread> Workers;
            std::queue<std::function<void()>> Tasks;
            std::condition_variable Condition;
            std::mutex queueMutex;
            bool Stop;
    };
}
#endif
