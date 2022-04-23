#include <thread>
#include <boost/asio.hpp>
#include<iostream>
#include <string>
class Server{
public:
    Server(std::string name, boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) : c_acceptor(io_service, endpoint.protocol()), c_socket(io_service)
    {

        c_acceptor.bind(endpoint);
        c_acceptor.listen(c_size);
        c_acceptor.accept(c_socket);
    }
    void main_job()
    {
        std::thread thred([this]() { read_data_until(); });
        write_data();
        thred.join();
    }
    std::string read_data_until()
    {
        boost::asio::streambuf buffer;

        boost::asio::read_until(c_socket, buffer, '!');
        std::string message;
        // Because buffer 'buf' may contain some other data
        // after '\n' symbol, we have to parse the buffer and
        // extract only symbols before the delimiter.
        std::istream input_stream(&buffer);
        std::getline(input_stream, message, '!');

        std::cout << message << std::endl;
    }
    void write_data()
    {
        std::string message;
        std::getline(std::cin, message);
        boost::asio::write(c_socket, boost::asio::buffer(c_name + ": " + message));
    }


private:
    boost::asio::ip::tcp::acceptor c_acceptor;
    const std::size_t c_size = 50;
    boost::asio::ip::tcp::socket c_socket;
    std::string c_name;
};



int main(int argc, char** argv) {

    const std::size_t size = 30;

    auto port = 3333;


    boost::asio::ip::address ip_address =
            boost::asio::ip::address_v6::any();

    boost::asio::ip::tcp::endpoint endpoint(ip_address, port);
    boost::asio::io_service io_service;
    std::string name = "server";
    try {
        Server server(name, io_service, endpoint);
        server.main_job();
    }
    catch (boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;


        return e.code().value();
    }
}