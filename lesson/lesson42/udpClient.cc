#include "udpClient.hpp"
#include <memory>

using namespace Client;

static void Usage(string proc)
{
    cerr << "\nUsage:\n\t" << proc << " server_ip server_port\n\n";
}

// ./udpClient server_ip server_port
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    string serverip = argv[1];
    uint16_t serverport = atoi(argv[2]);

    unique_ptr<udpClient> ucli(new udpClient(serverip, serverport));

    ucli->initClient();
    ucli->run();

    return 0;
}
