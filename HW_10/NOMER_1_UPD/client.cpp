#include <thread>
#include <boost/asio.hpp>
#include<iostream>
#include <string>

class Client
{
    using socket_1=boost::asio::ip::tcp::socket;

public:
    Client(std::string& name, std::string& raw_ip_address, int port) :
            c_name(name), c_endpoint(boost::asio::ip::address::from_string(raw_ip_address), port), c_socket(nullptr)
    {
        c_socket = std::make_shared<socket_1>(io_service, c_endpoint.protocol());
        c_socket->connect(c_endpoint);
        std::cout<<"connected";
    }
    ~Client() {}
    void main()
    {
        boost::asio::streambuf buffer;
        boost::asio::read_until(*c_socket, buffer, '!');
        std::istream input_stream(&buffer);
        std::getline(input_stream, server_name, '!');

        boost::asio::write(*c_socket, boost::asio::buffer(c_name + ": !"));
        std::thread thred([this]() { read_data_until(); });
        write_data();
        thred.join();
    }
    void read_data_until()
    {
        boost::asio::streambuf buffer;
        while (true)
        {
            boost::asio::read_until(*c_socket, buffer, '!');

            std::string message;

            // Because buffer 'buf' may contain some other data
            // after '\n' symbol, we have to parse the buffer and
            // extract only symbols before the delimiter.
            std::istream input_stream(&buffer);
            std::getline(input_stream, message, '!');
            if (message == "exit")
            {
                break;
            }
            std::cout << message << std::endl;
            //return message;
        }
    }
    void write_data()
    {
        std::string message;
        std::getline(std::cin, message);
        boost::asio::write(*c_socket, boost::asio::buffer(c_name + ": " + message));
    }

private:
    boost::asio::io_service io_service;
    std::shared_ptr<socket_1> c_socket;
    boost::asio::ip::tcp::endpoint c_endpoint;
    std::string c_name;
    std::string server_name;
};



int main(int argc, char** argv) {

    std::string raw_ip_address = "93.175.8.67";
    const std::size_t size = 30;
    auto port = 48999;
    std::string name = "client";
    try {
        boost::asio::ip::tcp::endpoint endpoint(
                boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_service io_service;
        Client client(name, raw_ip_address, port);
        client.main();
    }
    catch (const boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;


        return e.code().value();
    }
}
