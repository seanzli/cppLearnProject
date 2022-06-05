#ifndef _SOCKET_SERVER_H_
#define _SOCKET_SERVER_H_

#include <unordered_map>
#include <string>
#include <exception>

#include "client.hpp"

namespace SocketClass {
    class SocketBindError : public std::exception {
    public:
        const char* what() {
            return "server bind error";
        }
    };
    class SocketListenError : public std::exception {
    public:
        const char* what() {
            return "server listen error";
        }
    };
    class SocketServer{
    public:
        explicit SocketServer(const SocketType type,
                              const unsigned short & port) {
            m_socket = getSocketFd(type);
            server_addr = initSocket("0.0.0.0", port);
            serverInit();
        }

        ~SocketServer() {
            disconnect();
        }

        void disconnect() {
            m_running.store(false);
            if (m_accept_th.joinable())
                m_accept_th.join();
        }

        bool send(const int port, const std::string& msg) {
            auto itr = m_hash.find(port);
            if (itr == m_hash.end())
                return false;
            itr->second->send(msg);
            return true;
        }

    private:
        int m_socket;
        struct sockaddr_in server_addr;
        std::unordered_map<int, std::shared_ptr<SocketConnect>> m_hash;
        std::thread m_accept_th;
        std::atomic<bool> m_running{false};

    private:
        void serverInit() {
            if (::bind(m_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
                throw(SocketBindError());
            if (::listen(m_socket, 2) == -1)
                throw(SocketListenError());
            m_running.store(true);
            startAccept();
        }

        void startAccept() {
            m_accept_th = std::thread(
                    [&] {
                        while (m_running.load()) {
                            sockaddr_in client_socket;
                            unsigned int len = sizeof(client_socket);
                            int client_fp = ::accept(m_socket, (struct sockaddr*)&client_socket, &len);
                            int port = client_socket.sin_port;
                            m_hash[port] = std::make_shared<SocketConnect>(client_fp, client_socket);
                        }
                    });
        }
    };
}



#endif // _SOCKET_SERVER_H_