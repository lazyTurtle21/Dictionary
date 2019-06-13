//
// Created by sofik on 13.06.2019.
//

#include "../inc/parse_json_dictionary.h"
#include "../inc/read_functions.h"


using ptree = boost::property_tree::ptree;
using namespace boost::filesystem;

std::vector<ptree> find_json_dictionaries(const path & dir_path){
    std::vector<ptree> jsons;
    if (!exists(dir_path)) return jsons;
    directory_iterator end_itr;
    for (directory_iterator itr( dir_path ); itr != end_itr; ++itr){
        if (!is_directory(itr->status()))
            if(boost::algorithm::to_lower_copy(itr->path().extension().string()) == ".json"){
                jsons.push_back(create_dictionary_from_json(itr->path().string()));
            }
    }
    return jsons;
}
