//
// Created by tymchenko on 14.04.2019.
//

#include "../inc/http_headers.hpp"
#include <boost/algorithm/string/predicate.hpp>


std::string read_html(const std::string &filename) {
    std::ifstream f(filename);
    std::stringstream buf;
    buf << f.rdbuf();
    return buf.str();
}

std::string HttpHeaderds::get_response() {
    std::stringstream ssOut;

    if (url == "/dictionary") {
        ssOut << "HTTP/1.1 200 OK" << std::endl;
        ssOut << "content-type: text/html" << std::endl;
        ssOut << "content-length: " << this->dict_html.length() << std::endl;
        ssOut << std::endl;
        ssOut << this->dict_html;
    } else if (boost::starts_with(url, "/dictionary?word=")) {
        std::string sHTML = this->word_def_html;
        std::string word = url.substr(url.find("word=") + 5);
        sHTML = (boost::format(sHTML) % word % search_word(word, dict1)).str();
        ssOut << "HTTP/1.1 200 OK" << std::endl;
        ssOut << "content-type: text/html" << std::endl;
        ssOut << "content-length: " << sHTML.length() << std::endl;
        ssOut << std::endl;
        ssOut << sHTML;
    } else {
        std::string sHTML =
                "<html><body><h1>404 Not Found</h1><p>There's nothing here.</p></body></html>";
        ssOut << "HTTP/1.1 404 Not Found" << std::endl;
        ssOut << "content-type: text/html" << std::endl;
        ssOut << "content-length: " << sHTML.length() << std::endl;
        ssOut << std::endl;
        ssOut << sHTML;
    }
    return ssOut.str();
}

int HttpHeaderds::content_length() {
    auto request = headers.find("content-length");
    if (request != headers.end()) {
        std::stringstream ssLength(request->second);
        int content_length;
        ssLength >> content_length;
        return content_length;
    }
    return 0;
}

void HttpHeaderds::on_read_header(const std::string &line) {
    std::stringstream ssHeader(line);
    std::string headerName;
    std::getline(ssHeader, headerName, ':');

    std::string value;
    std::getline(ssHeader, value);
    headers[headerName] = value;
}

void HttpHeaderds::on_read_request_line(std::string line) {
    std::stringstream ssRequestLine(line);
    ssRequestLine >> method;
    ssRequestLine >> url;
    ssRequestLine >> version;
    std::cout << "request for resource: " << url << std::endl;
}

