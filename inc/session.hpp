//
// Created by tymchenko on 14.04.2019.
//

#ifndef DICTIONARY_SESSION_HPP
#define DICTIONARY_SESSION_HPP

#include <boost/asio.hpp>
#include "http_headers.hpp"

class Session {
    boost::asio::streambuf buff;
    HttpHeaderds headers;

    static void read_body(const std::shared_ptr<Session> &pThis);

    static void read_next_line(const std::shared_ptr<Session> &pThis);

    static void read_first_line(const std::shared_ptr<Session> &pThis);


public:
    boost::asio::ip::tcp::socket socket;
    boost::asio::io_context::strand strand;

    Session(boost::asio::io_context &io_context)
            : socket(io_context),
            strand(io_context){
    }



    static void interact(const std::shared_ptr<Session> &pThis) {
        read_first_line(pThis);
    }
};


#endif //DICTIONARY_SESSION_HPP
