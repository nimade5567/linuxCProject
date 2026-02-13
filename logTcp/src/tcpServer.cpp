#include "tcpServer.h"

void tcp::Server::sendToClient()
{
    std::string msg;
    while(true){
        std::getline(std::cin,msg);
        write(this->client_fd,&msg,sizeof(msg));
    }
}

tcp::Server::Server(size_t port_in, size_t numClients_in):port(port_in),numClients(numClients_in)
{
    this->server_fd=socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        LOG_ERROR("socket creation failed");
    }
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = INADDR_ANY;

     if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        LOG_ERROR("bind failed");
    }

    if (listen(server_fd, numClients) < 0) {
        LOG_ERROR("listen failed");
    }
    LOG_INFO("server listening on port 8080...");


    socklen_t client_len = sizeof(client_addr);
    this->client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (this->client_fd < 0) {
        LOG_ERROR("accept failed");
    }

    LOG_INFO("client connected");
    std::thread t([this]{
        this->sendToClient();
    });
    t.detach();
    while(true){
        memset(this->buffer,0,sizeof(this->buffer));
        int bytes = read(this->client_fd, this->buffer, sizeof(this->buffer) - 1);
        if (bytes <= 0) {
            LOG_WARN("client disconnected or read error");
            break;
        }

        LOG_INFO(this->buffer);
    }
    close(this->client_fd);
    close(this->server_fd);
    LOG_INFO("server exited");
}
