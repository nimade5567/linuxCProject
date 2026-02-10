#include<iostream>
int main(){
    int x=20;
    auto lambada=[&x](){
        x=x-1;
        return x;
    };
    std::cout<<lambada()<<std::endl;
    std::cout<<x<<std::endl;
    return 0;
}