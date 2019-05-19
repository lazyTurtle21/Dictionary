#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "../inc/http_headers.hpp"
#include "../inc/parse_json_dictionary.h"
#include "../inc/session.hpp"


void accept_and_run(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::io_context &io_context) {
    std::shared_ptr<Session> sesh = std::make_shared<Session>(io_context);
    acceptor.async_accept(sesh->socket,
                          [sesh, &acceptor, &io_context](const std::error_code &accept_error) {
                              accept_and_run(acceptor, io_context);
                              if (!accept_error) {
                                  Session::interact(sesh);
                              }
                          });
}


int main(int argc, const char *argv[]) {
    boost::asio::io_context io_context;
//    std::vector<std::thread> threads;
//    size_t threads_num = 4;
//    threads.reserve(threads_num);
    boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::tcp::v4(), 8080};
    boost::asio::ip::tcp::acceptor acceptor{io_context, endpoint};
   acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.listen();
    accept_and_run(acceptor, io_context);
    //io_context.run();
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < 4; ++i)
    {
      threads.emplace_back([&]{io_context.run();});
    }
    for (auto &thread : threads)
        thread.join();
    return 0;
}