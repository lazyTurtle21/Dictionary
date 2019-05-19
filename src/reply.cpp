#include "../inc/structs.hpp"
#include <string>
#include <boost/lexical_cast.hpp>


namespace status_strings {
    const std::string ok =
            "HTTP/1.0 200 OK\r\n";
    const std::string not_found =
            "HTTP/1.0 404 Not Found\r\n";

    boost::asio::const_buffer to_buffer(reply::status_type status) {
        switch (status) {
            case reply::ok:
                return boost::asio::buffer(ok);
            case reply::not_found:
                return boost::asio::buffer(not_found);
            default:
                return boost::asio::buffer(not_found);
        }
    }

}

namespace misc_strings {
    const char name_value_separator[] = {':', ' '};
    const char crlf[] = {'\r', '\n'};
}

std::vector<boost::asio::const_buffer> reply::to_buffers() {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(status_strings::to_buffer(status));
    for (auto &h : headers) {
        buffers.emplace_back(boost::asio::buffer(h.name));
        buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
        buffers.emplace_back(boost::asio::buffer(h.value));
        buffers.push_back(boost::asio::buffer(misc_strings::crlf));
    }
    buffers.push_back(boost::asio::buffer(misc_strings::crlf));
    buffers.emplace_back(boost::asio::buffer(content));
    return buffers;
}


reply reply::stock_reply(reply::status_type status) {
    reply rep;
    rep.status = status;
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/html";
    return rep;
}


