#include "log.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>


int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        LOG_ERROR("socket creation failed");
        return -1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        LOG_ERROR("bind failed");
        return -1;
    }

    if (listen(server_fd, 1) < 0) {
        LOG_ERROR("listen failed");
        return -1;
    }

    LOG_INFO("server listening on port 8080...");

    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        LOG_ERROR("accept failed");
        return -1;
    }

    LOG_INFO("client connected");

    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes <= 0) {
            LOG_WARN("client disconnected or read error");
            break;
        }

        LOG_INFO(buffer);

        const char* reply = "Message received\n";
        write(client_fd, reply, strlen(reply));
    }

    close(client_fd);
    close(server_fd);
    LOG_INFO("server exited");
    return 0;
}
