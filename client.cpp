#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>
#include <asio/registered_buffer.hpp>
#include <asio/steady_timer.hpp>
#include <asio/use_awaitable.hpp>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <asio.hpp>
#include <iostream>
#include <string>
#include <sys/socket.h>

using asio::ip::udp;


constexpr size_t port = 8080;
constexpr std::string server_ip = "127.0.0.1";

asio::awaitable<void> udp_co_clent(asio::io_context& io) {
    udp::socket socket(io);
    udp::resolver resolver(io);

    auto endpoints = co_await resolver.async_resolve(
        server_ip,
        std::to_string(port),
        asio::use_awaitable
    );

    auto receiver_ep = *endpoints.begin();
    
    socket.open(udp::v4());

    const std::string message = "hello nyiuu";

    while (true) {
        auto bytes_sent = co_await socket.async_send_to(
            asio::buffer(message),
            receiver_ep,
            asio::use_awaitable
        );

        std::cout << "-> 发送成功 (" << bytes_sent << " 字节): '" << message << "'" << std::endl;

        asio::steady_timer timer(io);
        timer.expires_after(std::chrono::seconds(1));
        co_await timer.async_wait(asio::use_awaitable);
    }


}

int main() {
    asio::io_context io;
    asio::co_spawn(io, udp_co_clent(io), asio::detached);
    io.run();    
}