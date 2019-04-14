#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include "../inc/http_headers.hpp"
#include "../inc/parse_json_dictionary.h"
#include "../inc/session.hpp"


void accept_and_run(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::io_service &io_service) {
    std::shared_ptr<Session> sesh = std::make_shared<Session>(io_service);
    acceptor.async_accept(sesh->socket,
                          [sesh, &acceptor, &io_service](const std::error_code &accept_error) {
                              accept_and_run(acceptor, io_service);
                              if (!accept_error) {
                                  Session::interact(sesh);
                              }
                          });
}


int main(int argc, const char *argv[]) {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::tcp::v4(), 8080};
    boost::asio::ip::tcp::acceptor acceptor{io_service, endpoint};
    acceptor.listen();
    accept_and_run(acceptor, io_service);
    io_service.run();
    return 0;
}