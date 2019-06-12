#include "../inc/parse_json_dictionary.h"
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

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


std::map<std::string, std::vector<std::string>> iterate_through_ptree(const ptree &tree,
        std::string& start){
    std::string res = tree.get<std::string>(start, "No such word.");
    std::map<std::string, std::vector<std::string>> results;
//    if (res.empty()){
//        ptree tree_child = tree.get_child(start);
//        BOOST_FOREACH(auto &v, tree_child) {
//            results.push_back(iterate_through_ptree(tree_child, v.first));
//        }
//    }
    return results;

}


std::map<std::string, std::vector<std::string>> search_word_in_dict2(const std::string &word, const ptree &dictionary) {
    const ptree &word_in_dict = dictionary.get_child(boost::algorithm::to_upper_copy(word));

    BOOST_FOREACH(auto &v, word_in_dict) {
        const ptree &key = word_in_dict.get_child(v.first);

        std::string value = word_in_dict.get<std::string>(v.first, "No such word.");
//        if
//      pair<char, int>('a', 20)
        BOOST_FOREACH(auto &w, value) {
                        std::cout << "Hero has " << w.first << ": " << w.second.get<std::string>("")
                                  << std::endl;

                    }

                }


    std::string word_definition = dictionary.get<std::string>(word + ".MEANINGS.1", "No such word.");

   return;
}



