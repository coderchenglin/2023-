#pragma once

#include <iostream>
#include <string>
#include <strings.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

namespace Client
{
    using namespace std;

    class udpClient
    {
    public:
        udpClient(const string &serverip, const uint16_t &serverport)
            : _serverip(serverip), _serverport(serverport), _sockfd(-1), _quit(false)
        {
        }
        void initClient()
        {
            // 创建socket
            _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_sockfd == -1)
            {
                cerr << "socket error: " << errno << " : " << strerror(errno) << endl;
                exit(2);
            }
            cout << "socket success: "
                 << " : " << _sockfd << endl;

            // 2. client要不要bind[必须要的]，client要不要显示的bind，需不需程序员自己bind？不需要！！！
            // 写服务器的是一家公司，写client是无数家公司 -- 由OS自动形成端口进行bind！-- OS在什么时候，如何bind
        }

        static void *readMessage(void *args)
        {
            int sockfd = *(static_cast<int *>(args));
            pthread_detach(pthread_self());
            while (true)
            {
                char buffer[1024];
                struct sockaddr_in temp;
                socklen_t temp_len = sizeof(temp);
                size_t n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&temp, &temp_len);
                if (n >= 0)
                    buffer[n] = 0;
                cout << buffer << endl;
            }

            return nullptr;
        }

        void run()
        {
            pthread_create(&_reader, nullptr, readMessage, (void *)&_sockfd);

            struct sockaddr_in server;
            memset(&server, 0, sizeof(server));
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr(_serverip.c_str());
            server.sin_port = htons(_serverport);

            string message;
            char cmdline[1024];
            while (!_quit)
            {
                //cerr << "# "; // ls -a -l
                // cin >> message;
                fprintf(stderr, "Enter# ");
                fflush(stderr);
                fgets(cmdline, sizeof(cmdline), stdin);
                cmdline[strlen(cmdline)-1] = 0;
                message = cmdline;
                sendto(_sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&server, sizeof(server));
            }
        }
        ~udpClient()
        {
        }

    private:
        int _sockfd;
        string _serverip;
        uint16_t _serverport;
        bool _quit;

        pthread_t _reader;
    };
} // namespace Client
