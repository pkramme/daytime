#include<ctime>
#include<iostream>
#include<boost/asio.hpp>
#include<cstring>
#include<cstdlib>
using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
     if(argc != 2)
     {
          std::cout << "USAGE: " << argv[0] << " <port>" << std::endl;
          return 0;
     }
     boost::asio::io_service ioService;
     unsigned short port = atoi(argv[1]);
     tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), port));
     while(true)
     {
          tcp::socket socket(ioService);
          std::cout << "Listening on port " << port << " (end with ^c)" << std::endl;
          acceptor.accept(socket);
          std::cout << "LOCAL ENDPOINT: " << socket.local_endpoint() << std::endl;
          std::cout << "Connection to " << socket.remote_endpoint() << " established" << std::endl;
          time_t now = time(NULL);
          const char *timestring = ctime(&now);
          socket.write_some(boost::asio::buffer(timestring, strlen(timestring) + 1));
     }
     return 0;
}
