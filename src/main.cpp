#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

#include "server.cpp"
#include "parse_json_dictionary.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
using ptree = boost::property_tree::ptree;

//boost::property_tree::ptree create_dictionary_from_json(const std::string& filename);

