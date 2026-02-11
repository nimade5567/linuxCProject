#include<iostream>
#include "threadPool.h"
void exampleTask(){
    std::cout<<"the thread is running"<<std::this_thread::get_id()<<"\n"<<std::endl;
}
int main(){
    server::ThreadPool pool(4);
    pool.enqueue(exampleTask);
    pool.enqueue(exampleTask);
    pool.enqueue(exampleTask);
    pool.enqueue(exampleTask);
    return 0;
}