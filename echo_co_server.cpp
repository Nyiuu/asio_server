#include <cstdio>
#include <asio.hpp>

using asio::ip::udp;

const size_t port = 8080;
asio::io_context io;

asio::awaitable<void> udp_echo_server()
{
    udp::endpoint listen_endpoint(udp::v4(), port);
    udp::socket socket(io, listen_endpoint);

    printf("UDP Echo Server running on port %zu\n", port);

    char data[1024];
    udp::endpoint remote_endpoint; 

    try {
        while (true) {
            std::size_t n = co_await socket.async_receive_from(
                asio::buffer(data),
                remote_endpoint,
                asio::use_awaitable
            );

            printf("Received %zu bytes from %s:%u\n", 
                   n, 
                   remote_endpoint.address().to_string().c_str(), 
                   remote_endpoint.port());
            
            co_await socket.async_send_to(
                asio::buffer(data, n),
                remote_endpoint,
                asio::use_awaitable
            );
        }
    } catch (std::exception& e) {
        printf("Exception in UDP server: %s\n",  e.what());
    }
}

int main()
{
    try {
        asio::co_spawn(io, udp_echo_server(), asio::detached);
        io.run();
    } catch (std::exception& e) {
        printf("Exception in UDP server: %s\n",  e.what());
    }

    return 0;
}