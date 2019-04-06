#include "parse_json_dictionary.h"

boost::property_tree::ptree create_dictionary_from_json(const std::string& filename){
    // Create a root
    boost::property_tree::ptree root;
    // Load the json file in this ptree
    boost::property_tree::read_json(filename, root);
    return root;
}

std::string search_word(const std::string& word, const boost::property_tree::ptree& dictionary){
    std::string word_definition = dictionary.get<std::string>(word, "No such word.");
    return word_definition;
}