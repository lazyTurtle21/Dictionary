#ifndef DICTIONARY_HTTP_HEADERS_HPP
#define DICTIONARY_HTTP_HEADERS_HPP

#include <string>
#include<map>
#include <fstream>
#include "parse_json_dictionary.h"

using ptree = boost::property_tree::ptree;

std::string read_html(const std::string &filename);

class HttpHeaderds {
    std::string method;
    std::string url;
    std::string version;
    std::map<std::string, std::string> headers;
    ptree dict1 = create_dictionary_from_json("../dictionaries/dictionary1.json");
    std::string dict_html = read_html("../html/dict.html");
    std::string word_def_html = read_html("../html/get_word.html");

public:
    std::string get_response();

    int content_length();

    void on_read_header(const std::string &line);

    void on_read_request_line(std::string line);
};


#endif //DICTIONARY_HTTP_HEADERS_HPP
