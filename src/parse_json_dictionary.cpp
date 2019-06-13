#include "../inc/parse_json_dictionary.h"
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/optional/optional.hpp>

#include <iostream>

using ptree = boost::property_tree::ptree;

ptree create_dictionary_from_json(const std::string &filename) {
    // Create a root
    boost::property_tree::ptree root;
    // Load the json file in this ptree
    boost::property_tree::read_json(filename, root);
    return root;
}

std::string search_word(const std::string &word, const ptree &dictionary) {
    std::string word_definition = dictionary.get<std::string>(word, "No such word.");
    return word_definition;
}


std::vector<std::string> search_word_in_dict2(const std::string &word, const ptree &dictionary) {
    boost::optional<const ptree&> child = dictionary.get_child_optional(word);
    if(!child){
        return std::vector<std::string>(3);
    }

    const ptree &word_in_dict = dictionary.get_child(word);
    std::vector<std::string> results;
    BOOST_FOREACH(auto &v, word_in_dict) {
                    const ptree &key = word_in_dict.get_child(v.first);
                    std::string result;
                    BOOST_FOREACH(auto &w, key) {
                                    auto value = w.second.get<std::string>("");
                                    if (value.empty()) {
                                        auto vvalues = key.get_child(w.first);
                                        std::string res;
                                        BOOST_FOREACH(auto &y, vvalues) {
                                                        result += y.second.get<std::string>("") + " ";}
                                    } else {
                                        result += value + ",";
                                    }
                     }
                    results.push_back(result);
                }
    return results;
}





