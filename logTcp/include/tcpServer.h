#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <functional>
#include "log.h"


namespace tcp{
    class Server{
        public:
            Server(size_t port_in,size_t numClients_in);
        private:
            int server_fd;
            sockaddr_in addr{};
            sockaddr_in client_addr{};
            char buffer[1024];
            size_t port;
            size_t numClients;
            int client_fd;
            void sendToClient();
    };
}