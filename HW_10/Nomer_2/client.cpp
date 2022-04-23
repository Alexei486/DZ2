#include <thread>
#include <boost/asio.hpp>
#include<iostream>
#include <string>

class Client
{
public:
    Client(std::string& name, boost::asio::ip::tcp::endpoint endpoint, boost::asio::io_service& io_service) :
            c_name(name), c_endpoint(endpoint), c_socket(io_service, c_endpoint.protocol())
    {
        c_socket.connect(c_endpoint);
    }
    ~Client() {}
    void main_job()
    {
        boost::asio::streambuf buffer;
        boost::asio::read_until(c_socket, buffer, '!');
        std::istream input_stream(&buffer);
        std::getline(input_stream, server_name, '!');

        boost::asio::write(c_socket, boost::asio::buffer(c_name + ": !"));
        std::thread thred([this]() { read_data_until(); });
        write_data();
        thred.join();
    }
    std::string read_data_until()
    {
        boost::asio::streambuf buffer;
        while (true)
        {
            boost::asio::read_until(c_socket, buffer, '!');

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
        boost::asio::write(c_socket, boost::asio::buffer(c_name + ": " + message));
    }

private:
    boost::asio::ip::tcp::socket c_socket;
    boost::asio::ip::tcp::endpoint c_endpoint;
    std::string c_name;
    std::string server_name;
};



int main(int argc, char** argv) {

    std::string raw_ip_address = "127.0.0.1";

    const std::size_t size = 30;
    auto port = 3333;
    std::string name = "client";
    try {
        boost::asio::ip::tcp::endpoint endpoint(
                boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_service io_service;
        Client client(name, endpoint, io_service);
        client.main_job();
    }
    catch (boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;


        return e.code().value();
    }
}