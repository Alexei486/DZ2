#include <thread>
#include <boost/asio.hpp>
#include<iostream>
#include <string>
class Server
        {
public:
    Server(std::string name, int port) :
            c_endpoint(boost::asio::ip::address_v4::any(), port), c_acceptor(nullptr), c_socket(nullptr), c_name(name)
    {
        c_acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(io_service, c_endpoint.protocol());
        c_socket = std::make_shared<boost::asio::ip::tcp::socket>(io_service);
        c_acceptor->bind(c_endpoint);
        c_acceptor->listen(c_size);
        c_acceptor->accept(*c_socket);
    }
    void main()
    {
        boost::asio::write(*c_socket, boost::asio::buffer(c_name + ": !"));
        boost::asio::streambuf buffer;
        boost::asio::read_until(*c_socket, buffer, '!');
        std::istream input_stream(&buffer);
        std::getline(input_stream, client_name, '!');
        std::thread thred([this]() { read_data_until(); });
        write_data();
        thred.join();
    }
    void read_data_until()
    {
        boost::asio::streambuf buffer;
        while(true) {
            boost::asio::read_until(*c_socket, buffer, '!');
            std::string message;
            // Because buffer 'buf' may contain some other data
            // after '\n' symbol, we have to parse the buffer and
            // extract only symbols before the delimiter.
            std::istream input_stream(&buffer);
            std::getline(input_stream, message, '!');
            if (message == client_name + "exit")
            {
                break;
            }
            std::cout << message << std::endl;
        }
    }
    void write_data() {

        std::string message;
        while (true) {
            std::getline(std::cin, message);
            boost::asio::write(*c_socket, boost::asio::buffer(c_name + ": " + message));
            if (message == "exit!")
            {
                break;
            }
        }
    }
private:
    boost::asio::io_service io_service;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> c_acceptor;
    boost::asio::ip::tcp::endpoint c_endpoint;
    const std::size_t c_size = 50;
    std::shared_ptr<boost::asio::ip::tcp::socket> c_socket;
    std::string c_name;
    std::string client_name;
};



int main(int argc, char** argv) {

    auto port = 3333;
    boost::asio::io_service io_service;
    std::string name = "server";
    try {
        Server server(name, port);
        server.main();
    }
    catch (boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;


        return e.code().value();
    }
}