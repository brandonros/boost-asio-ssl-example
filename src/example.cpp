#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace io = boost::asio;
namespace ip = io::ip;
namespace ssl = io::ssl;
using tcp = ip::tcp;
using error_code = boost::system::error_code;
using ssl_socket = ssl::stream<tcp::socket>;

int main(int argc, char* argv[]) {
    io::io_context io_context;
    ssl::context ssl_context(ssl::context::tls);
    ssl_socket socket(io_context, ssl_context);
    tcp::resolver resolver(io_context);
    // resolve
    auto endpoints = resolver.resolve("google.com", "443");
    // connect
    io::connect(socket.next_layer(), endpoints);
    // handshake
    socket.handshake(ssl::stream_base::client);
    // write request
    char request[] =
        "GET / HTTP/1.1\n"
        "Host: www.google.com\n"
        "Connection: close\n\n";
    io::write(socket, io::buffer(request));
    // read response
    io::streambuf response;
    error_code ec;
    io::read(socket, response, ec);
    // print to stdout
    std::cout << std::istream(&response).rdbuf() << "\n";
    return 0;
}
