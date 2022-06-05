#ifndef _SOCKET_CLIENT_
#define _SOCKET_CLIENT_

#include <string>
#include <future>
#include <functional>

#include "socketBasic.hpp"

namespace SocketClass {

    class SocketClient{
    public:
        explicit SocketClient(const SocketType type,
                              const std::string& ip,
                              const int& port,
                              std::function<void(std::string)> call_back = [](std::string){}) {
            m_socket = getSocketFd(type);
            client_addr = initSocket(ip, port);
            m_call_back = call_back;
        }

        ~SocketClient() {
            disconnect();
        }

        bool connect() {
            int nRet = ::connect(m_socket, (sockaddr*)&client_addr, sizeof(client_addr));
            if (nRet == 0)
                m_connected.store(true);
            return m_connected.load();
        }

        void disconnect() {
            m_connected.store(false);
            if (m_recv_th.joinable())
                m_recv_th.join();
        }

        /**
         * register call-back function
         * @param call_back
         */
        void registe(std::function<void(std::string)> call_back) {
            m_call_back = call_back;
        }

        /**
         * sent a message to server
         * @param str message
         * @return send success or not
         */
        bool send(const std::string str) {
            if (!m_connected.load())
                return false;
            int nRet = ::send(m_socket, str.c_str(), str.length(), 0);
            if (nRet > 0)
                return true;
            return false;
        }

        /**
         * receive message, move to call_back function.
         */
        void recv() {
            m_recv_th = std::thread([&] {
                char *buffer = new char[1024];
                while (m_connected.load()) {
                    int nRet = ::recv(m_socket, buffer, 1024, 0);
                    if (nRet > 0) {
                        //m_recv_message.emplace(std::move(std::string(buffer)));
                        m_call_back(std::move(std::string(buffer)));
                    }
                }
            });
        }

    private:
        int m_socket;
        struct sockaddr_in client_addr;
        std::atomic<bool> m_connected{false};
        // std::queue<std::string> m_recv_message;
        std::function<void(std::string)> m_call_back;
        std::thread m_recv_th;
    };
}

#endif //_SOCKET_CLIENT_