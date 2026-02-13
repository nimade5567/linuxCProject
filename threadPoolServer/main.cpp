#include<iostream>
#include "threadPool.h"

#include<arpa/inet.h>
#include<unistd.h>

void handleClient(int client_id){
    char buffer[1024]={0};
    while(true){
        ssize_t n=read(client_id,buffer,sizeof(buffer));
        if(n<=0)
            break;
        std::cout << "收到: ";
        std::cout.write(buffer, n);
        std::cout << std::endl;
    }
    close(client_id);
}

int main(){
    //初始化线程
    server::ThreadPool pool(4);
    
    //初始化服务器
    int server_id=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in address{};
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);
    bind(server_id,(sockaddr*)&address,sizeof(address));
    listen(server_id,20);
    std::cout<<"服务器启动成功"<<std::endl;


    while(true){
    int client_id = accept(server_id,nullptr,nullptr);
    std::cout << "新客户端连接: " << client_id << std::endl;

    pool.enqueue([client_id]{
        std::cout << "线程开始处理客户端: " << client_id << std::endl;
        handleClient(client_id);
    });
}
    return 0;
}