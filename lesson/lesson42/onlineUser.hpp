#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

class User
{
public:
    User(const string &ip, const uint16_t &port) : _ip(ip), _port(port)
    {
    }
    ~User()
    {
    }
    string ip(){ return _ip; }
    uint16_t port(){ return _port; }
private:
    string _ip;
    uint16_t _port;
};

class OnlineUser
{
public:
    OnlineUser() {}
    ~OnlineUser() {}
    void addUser(const string &ip, const uint16_t &port)
    {
        string id = ip + "-" + to_string(port);
        users.insert(make_pair(id, User(ip, port)));
    }
    void delUser(const string &ip, const uint16_t &port)
    {
        string id = ip + "-" + to_string(port);
        users.erase(id);
    }
    bool isOnline(const string &ip, const uint16_t &port)
    {
        string id = ip + "-" + to_string(port);
        return users.find(id) == users.end() ? false : true;
    }
    void broadcastMessage(int sockfd, const string &ip, const uint16_t &port, const string &message)
    {
        for (auto &user : users)
        {
            struct sockaddr_in client;
            bzero(&client, sizeof(client));

            client.sin_family = AF_INET;
            client.sin_port = htons(user.second.port());
            client.sin_addr.s_addr = inet_addr(user.second.ip().c_str());
            string s = ip + "-" + to_string(port) + "# ";
            s += message;
            sendto(sockfd, s.c_str(), s.size(), 0, (struct sockaddr *)&client, sizeof(client));
        }
    }

private:
    unordered_map<string, User> users;
};