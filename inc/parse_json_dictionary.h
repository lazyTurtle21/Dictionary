
#ifndef TRY_BOOST_PARSE_JSON_DICTIONARY_H
#define TRY_BOOST_PARSE_JSON_DICTIONARY_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>


boost::property_tree::ptree create_dictionary_from_json(const std::string& filename);
std::string search_word(const std::string& word, const boost::property_tree::ptree& dictionary);
std::vector<std::string> search_word_in_dict2(const std::string &word, const boost::property_tree::ptree &dictionary);
#endif //TRY_BOOST_PARSE_JSON_DICTIONARY_H