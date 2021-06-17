#include "row.hpp"

const std::string& Row::get(std::string& key) const {
    return this->fields.at(key);
}

void Row::insert(const std::string& key, const std::string& value) {
    this->fields.insert({key, value});
}

std::unordered_map<std::string, std::string>::const_iterator Row::begin() const {
    return this->fields.cbegin();
}

std::unordered_map<std::string, std::string>::const_iterator Row::end() const {
    return this->fields.cend();
}