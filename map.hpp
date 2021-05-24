#pragma once
#include <utility>
#include <string>
#include <vector>

typedef std::pair<int, std::string> Item;

class Map {
public:
    Map(const std::size_t size);
    ~Map();

    void insert(const std::string &key, const std::vector<Item> &order);
    std::vector<Item> get(const std::string &key);
    void remove(const std::string &key);

private:
    class MapElement {
    public:
        ~MapElement();
        std::string key;
        std::vector<Item> value;
        bool empty = true;
        bool deleted = false;
        MapElement* arr;
        
        void clear();
    };
    const std::size_t size;
    std::size_t calcHash(const std::string &key);
    MapElement* head = nullptr;
};
