#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "../inc/http_headers.hpp"
#include "../inc/parse_json_dictionary.h"
#include "../inc/session.hpp"

using boost::asio::ip::tcp;

void accept_and_run(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::io_context &io_context) {
    std::shared_ptr<Session> sesh = std::make_shared<Session>(io_context);
    acceptor.async_accept(
            sesh->socket,
            [sesh, &acceptor, &io_context](const std::error_code &accept_error) {
                accept_and_run(acceptor, io_context);
                if (!accept_error) {
                    Session::interact(sesh);
                }
            });
}


int main(int argc, const char *argv[]) {
    boost::asio::io_context io_context;
    tcp::endpoint endpoint{tcp::v4(), 8080};
    tcp::acceptor acceptor{io_context, endpoint};
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    acceptor.listen();
    accept_and_run(acceptor, io_context);
    std::vector<std::thread> threads;
    for (int i = 0, num_log_cpus = std::thread::hardware_concurrency(); i < num_log_cpus; ++i) {
        threads.emplace_back([&] { io_context.run(); });
    }
    for (auto &thread : threads) {
        thread.join();
    }
    return 0;
}