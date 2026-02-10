#include<thread>
#include<vector>
#include<queue>
#include<condition_variable>
#include<functional>
#include<iostream>
#include<mutex>
using namespace std;
class threadPool{
    public:
        threadPool(size_t numThreads);
        ~threadPool();
        void queueTasks(function<void()> task);
    private:
        vector<thread> workers;
        queue<function<void()>> tasks;
        condition_variable condition;
        mutex queueMutex;
        bool stop;
};
threadPool::threadPool(size_t numThreads):stop(false){
    for(int i=0;i<numThreads;i++){
        workers.emplace_back([this]{
            while(true){
                function<void()> task;
                {
                    unique_lock<mutex> lock(this->queueMutex);
                    this->condition.wait(lock,[this]{
                        return this->stop||!this->tasks.empty();
                    });
                    if(this->stop&&this->tasks.empty())
                        return;
                    task=this->tasks.front();
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}
void threadPool::queueTasks(function<void()> task){
    {
        lock_guard<mutex> lock(this->queueMutex);
        this->tasks.push(move(task));
    }
    condition.notify_one();
}
threadPool::~threadPool(){
    {
        lock_guard<mutex> lock(this->queueMutex);
        stop=true;
    }
    condition.notify_all();
    for(thread& worker:workers){
        if(worker.joinable()){
            worker.join();
        }
    }
}
void exmapleTask(){
    cout<<"this thread is running"<<this_thread::get_id()<<"\n"<<endl;
}
int main(){
    threadPool pool(4);
    pool.queueTasks(exmapleTask);
    pool.queueTasks(exmapleTask);
    pool.queueTasks(exmapleTask);
    pool.queueTasks(exmapleTask);
    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}