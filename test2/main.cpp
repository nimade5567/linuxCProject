#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex mtx;
void increment(int& counter){
    for(int i=0;i<1000;i++){
        lock_guard<mutex> lock(mtx); // Lock the mutex to protect the counter
        counter++;
        cout<<"Counter: "<<counter<<endl;
    }
}
int main(){
    int counter=0;
    thread t1(increment,ref(counter));
    thread t2(increment,ref(counter));
    t1.join();
    t2.join();
    cout<<"Final counter value: "<<counter<<endl;
    return 0;
}