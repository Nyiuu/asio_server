#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/registered_buffer.hpp>
#include <asio/use_awaitable.hpp>
#include <cstdio>
#include <asio.hpp>
#include <iostream>

using asio::ip::udp;
asio::io_context io;

const size_t port = 8080;

asio::awaitable<void> udp_co_server() {
    udp::endpoint local_ep(udp::v4(), port);
    udp::socket socket(io, local_ep);

    std::cout << "server running on: " << port  << "\n";

    char buffer[1024];
    udp::endpoint remote_ep;

    while (true) {
        auto n = co_await socket.async_receive_from(
        asio::buffer(buffer), 
        remote_ep,
        asio::use_awaitable);

        printf("Received %zu bytes from %s:%u\n", 
            n, 
            remote_ep.address().to_string().c_str(), 
            remote_ep.port()
        );

        co_await socket.async_send_to(asio::buffer(
            buffer, n),
            remote_ep,
            asio::use_awaitable);
        }
               
}

int main() {
    asio::co_spawn(io, udp_co_server(), asio::detached);
    io.run();
}