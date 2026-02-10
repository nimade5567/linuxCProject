#include<functional>
#include<queue>
#include<iostream>
using namespace std;
void task1(){
    cout<<"Task 1 executed!"<<endl;
    // do something
}
void task2(){
    cout<<"Task 2 executed!"<<endl;
    // do something
}
int main(){
    queue<function<void()>> taskQueue;
    taskQueue.push(task1);
    taskQueue.push(task2);
    while(!taskQueue.empty()){
        function<void()> test=taskQueue.front(); // get the next task
        test(); // execute the taskcmk
        taskQueue.pop(); // remove the task from the queue
    }
    return 0;
}