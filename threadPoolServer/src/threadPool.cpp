#include "threadPool.h"

namespace server{
ThreadPool::ThreadPool(size_t threadCounts):Stop(false){
    for(size_t i=0;i<threadCounts;i++){
        this->Workers.emplace_back([this]{
            while(true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);
                    this->Condition.wait(lock,[this]{
                        return this->Stop||!this->Tasks.empty();//如果队列不为空或者线程需要停止则唤醒线程
                    });
                    if(this->Stop&&this->Tasks.empty())
                        return;//如果线程需要停止并且队列里面是空的那么退出线程
                    task=std::move(this->Tasks.front());
                    this->Tasks.pop();//弹出队头元素
                }
                task();
            }
        });
    }
}
ThreadPool::~ThreadPool(){
    {
        std::lock_guard<std::mutex> lock(this->queueMutex);
        this->Stop=true;
    }
    this->Condition.notify_all();
    for(std::thread& worker: this->Workers){
        if(worker.joinable()){
            worker.join();
        }
    }
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(this->queueMutex);
        if(Stop) 
            throw std::runtime_error("enqueue on stopped ThreadPool");
        this->Tasks.push(std::move(task));
    }
    this->Condition.notify_one();
}
}
