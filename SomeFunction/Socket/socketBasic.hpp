#ifndef _SOCKET_BASIC_H_
#define _SOCKET_BASIC_H_

#include <sys/socket.h>
#include <arpa/inet.h>

#include <string>
#include <thread>
#include <queue>

namespace SocketClass {
    enum class SocketType {
        UDP,
        TCP,
        UNKNOWN
    };

    static int getSocketFd(const SocketType type) {
        switch (type) {
            case SocketType::TCP: return socket(AF_INET, SOCK_STREAM, 0);
            case SocketType::UDP: return socket(AF_INET, SOCK_DGRAM,0);
            default:
                return -1;
        }
    }

    static sockaddr_in initSocket(const std::string& ip, const unsigned short port) {
        sockaddr_in sock;
        memset(&sock, 0, sizeof(sockaddr_in));
        sock.sin_family = AF_INET;
        sock.sin_port = htons(port);
        sock.sin_addr.s_addr = inet_addr(ip.c_str());
        return sock;
    }

    class SocketConnect {
    public:
        explicit SocketConnect(const SocketType type,
                               const std::string& ip,
                               const unsigned short & port) {
            m_socket = getSocketFd(type);
            m_sock_connect = initSocket(ip, port);
        }

        explicit SocketConnect(int socket_fp, sockaddr_in socket) {
            m_socket = socket_fp;
            m_sock_connect = socket;
        }

        virtual ~SocketConnect() {
            disconnect();
        };

        void disconnect() {
            m_running.store(false);
            m_send_cv.notify_all();
            m_recv_cv.notify_all();
            if (m_send_th.joinable())
                m_send_th.join();
            if (m_recv_th.joinable())
                m_recv_th.join();
        }

        bool connect() {
            int nRet = ::connect(m_socket, (sockaddr*)&m_sock_connect, sizeof(m_sock_connect));
            if (nRet == 0) {
                m_running.store(true);
                start();
            }
            return m_running.load();
        }

        void send(const std::string msg) {
            {
                std::lock_guard<std::mutex> lg(m_send_mutex);
                m_send_que.emplace(msg);
            }
            m_send_cv.notify_one();
        }



        void registerCallBack(std::function<void(std::string)> call_back) {
            m_call_back = call_back;
        }


    protected:
        int m_socket;
        struct sockaddr_in m_sock_connect;
        std::atomic<bool> m_running{false};
        std::thread m_send_th, m_recv_th;
        std::queue<std::string> m_send_que, m_recv_que;
        std::mutex m_send_mutex, m_recv_mutex;
        std::condition_variable m_send_cv, m_recv_cv;
        std::function<void(std::string)> m_call_back = [](std::string){};

    protected:
        void start() {
            startSendThread();
            startRecvThread();
        }

        void startSendThread() {
            m_send_th = std::thread(
                    [&]{
                        while (m_running.load()) {
                            std::string msg;
                            {
                                std::unique_lock<std::mutex> ul(m_send_mutex);
                                m_send_cv.wait(ul, [&]{
                                    return (!m_send_que.empty() || !m_running.load());
                                });
                                if (!m_running.load())
                                    return;
                                if (m_send_que.empty())
                                    continue;
                                msg = m_send_que.front();
                                m_send_que.pop();
                            }
                            sendFunction(msg);
                        }
                    });
        }

        bool sendFunction(const std::string msg) {
            int nRet = ::send(m_socket, msg.c_str(), msg.length(), 0);
            if (nRet > 0)
                return true;
            return false;
        }

        void startRecvThread() {
            m_recv_th = std::thread([&] {
                char *buffer = new char[1024];
                while (m_running.load()) {
                    int nRet = ::recv(m_socket, buffer, 1024, 0);
                    if (nRet > 0) {
                        {
                            std::lock_guard<std::mutex> lg(m_recv_mutex);
                            m_recv_que.emplace(std::string(buffer));
                        }
                        m_recv_cv.notify_one();
                    }
                }
                delete[] buffer;
            });
        }

        virtual std::string recv() {
            std::string msg;
            {
                std::unique_lock<std::mutex> lg(m_recv_mutex);
                m_recv_cv.wait(lg, [&]{
                    return (!m_recv_que.empty() || !m_running.load());
                });
                msg = m_recv_que.front();
                m_recv_que.pop();
            }
            m_call_back(msg);
            return msg;
        }
    };
}


#endif //_SOCKET_BASIC_H_