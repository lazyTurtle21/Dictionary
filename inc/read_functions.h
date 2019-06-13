//
// Created by sofik on 13.06.2019.
//

#ifndef DICTIONARY_READ_FUNCTIONS_H
#define DICTIONARY_READ_FUNCTIONS_H


#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>

std::vector<boost::property_tree::ptree> find_json_dictionaries(const boost::filesystem::path & dir_path);


#endif //DICTIONARY_READ_FUNCTIONS_H
