#ifndef HTTP_SERVER3_REQUEST_HPP
#define HTTP_SERVER3_REQUEST_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>


struct header {
    std::string name;
    std::string value;
};

struct request {
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<header> headers;
};

struct reply {
    enum status_type {
        ok = 200,
        not_found = 404
    } status;
    std::vector<header> headers;
    std::string content;
    std::vector<boost::asio::const_buffer> to_buffers();
    static reply stock_reply(status_type status);
};

#endif // HTTP_SERVER3_REQUEST_HPP
