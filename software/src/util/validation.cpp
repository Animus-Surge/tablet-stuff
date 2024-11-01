#include "util/util.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool contains_key(const json& j, const std::string& key) {
    return j.find(key) != j.end();
}

bool contains_keys(const json& j, const std::vector<std::string>& keys) {
    for(const std::string& key : keys) {
        if(!contains_key(j, key)) {
            return false;
        }
    }

    return true;
}
