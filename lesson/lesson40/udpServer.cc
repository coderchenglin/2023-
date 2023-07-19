#include"udpServer.hpp"
#include<memory>

int main()
{
    std::unique_ptr<udpServer> usvr(new udpServer());

    usvr->initServer();
    usvr->start();

    return 0;
}


