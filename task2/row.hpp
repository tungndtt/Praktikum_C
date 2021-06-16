#pragma once

#include <string>
#include <unordered_map>

class Row {
public:
    const std::string& get(std::string& key) const;
    void insert(const std::string& key, const std::string& value);
    std::unordered_map<std::string, std::string>::const_iterator begin() const;
    std::unordered_map<std::string, std::string>::const_iterator end() const;

private:
    std::unordered_map<std::string, std::string> fields;
};