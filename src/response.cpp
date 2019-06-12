#include "../inc/response.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "../inc/structs.hpp"

std::string read_html(const std::string &filename) {
    std::ifstream f(filename);
    std::stringstream buf;
    buf << f.rdbuf();
    return buf.str();
}

response::response() = default;

void response::handle_request(const request &req, reply &rep) {
    std::string html_res;

    if (req.uri == "/dictionary") {
        rep.status = reply::ok;
        html_res = this->dict_html;
    } else if (boost::starts_with(req.uri, "/dictionary?word=")) {
        rep.status = reply::ok;
        html_res = this->word_def_html;
        //ABALONES
        std::string word = req.uri.substr(req.uri.find("word=") + 5);
        html_res = (boost::format(html_res) % word % search_word(boost::algorithm::to_lower_copy(word), dict1)).str();
//        std::cout << "hi hello" << search_word_in_dict2("ABALONE", dict2);
    } else {
        rep.status = reply::not_found;
        html_res = "<html><body><h1>404 Not Found</h1><p>There's nothing here.</p></body></html>";
    }
    rep.content.append(html_res);
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/html";
}


