
#ifndef HTTP_SERVER3_REQUEST_HANDLER_HPP
#define HTTP_SERVER3_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include "parse_json_dictionary.h"
#include "read_functions.h"

std::string read_html(const std::string &filename);

using ptree = boost::property_tree::ptree;
struct reply;
struct request;

class response :
        private boost::noncopyable {
    std::string dict_html = read_html("../html/dict.html");
    std::string word_def_html = read_html("../html/get_word.html");
    ptree dict1 = create_dictionary_from_json("../dictionaries/dictionary1/dictionary1.json");
    std::vector<ptree> dicts2 = find_json_dictionaries("../dictionaries/dictionary2/");
public:

    explicit response();

    void handle_request(const request &req, reply &rep);

};

#endif // HTTP_SERVER3_REQUEST_HANDLER_HPP
