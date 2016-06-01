#include<iostream>
#include<cstdlib>
#include<boost/asio.hpp>

int main(int argc, char *argv[])
{
     if(argc != 3)
     {
          std::cout << "USAGE: " << argv[0] << "<IP-Adress> <Port>" << std::endl;
          return 1;
     }
     boost::asio::io_service ioService;
     unsigned short port = atoi(argv[2]);
     boost::asio::ip::tcp::endpoint server(boost::asio::ip::address::from_string(argv[1]), port);
     boost::asio::ip::tcp::socket socket(ioService);
     socket.connect(server);
     std::cout << "LOCAL ENDPOINT: " << socket.local_endpoint() << std::endl;
     std::cout << "CONNECT WITH... " << socket.remote_endpoint() << " ...connected" << std::endl;
     int bufferwidth = 80;
     char buffer[bufferwidth + 1];
     int current_bytes = socket.read_some(boost::asio::buffer(buffer, bufferwidth));
     buffer[current_bytes] = '\0';
     std::cout << buffer << std::endl;
}
