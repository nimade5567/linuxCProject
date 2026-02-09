#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;
int main(){
	//设置服务器地址
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//创建服务器套接字
	int server_socket = socket(AF_INET,SOCK_STREAM,0);
	if(server_socket==-1){
		cerr<<"Failed to create socket"<<endl;
		return -1;
	}else{
		cout<<"Socket created successfully"<<endl;
	}

	//绑定套接字到地址
	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		cerr<<"Failed to bind socket"<<endl;
		return -1;
	}else{
		cout<<"Socket bound successfully"<<endl;
	}
	//监听连接
	if(listen(server_socket,5)<0){
		cerr<<"Failed to listen on socket"<<endl;
		return -1;
	}else{
		cout<<"Listening on socket successfully"<<endl;
	}
	//接受连接
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int client_socket = accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_len);
	if(client_socket==-1){
		cerr<<"Failed to accept connection"<<endl;
		return -1;
	}else{
		cout<<"Connection accepted successfully"<<endl;
	}
	//接收数据
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	int read_size = read(client_socket,buffer,sizeof(buffer)-1);
	if(read_size<0){
		cerr<<"Failed to read data"<<endl;
		return -1;
	}else{
		cout<<"Data received: "<<buffer<<endl;
	}
	close(client_socket);
	close(server_socket);
	return 0;
}