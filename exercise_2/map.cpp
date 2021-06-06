#include "map.hpp"
#include <stdexcept>
#include <iostream>

// recursive clearing MapElement instances
void Map::MapElement::clear() {
    if(this->arr != nullptr) this->arr->clear();
    delete this->arr;
}

Map::MapElement::~MapElement() {
    std::cout << "Map element with key " << this->key << " is removed!" << std::endl;
}

// Map non-default constructor
Map::Map(const std::size_t size): size(size)
{
    // make sure size of Map must be greater than 0
    if(size == 0) throw std::runtime_error("Unable to create map with 0 size");
    
    // intialize Map object
    std::size_t count = size;
    if(count > 0) {
        this->head = new MapElement();
        --count;
        MapElement* iterator = this->head;
        while(count > 0) {
            iterator->arr = new MapElement();
            iterator = iterator->arr;
            --count;
        }
    }
}

// Map default destructor
Map::~Map() 
{
    // recursive clearing objects 
    if(this->head != nullptr) {
        this->head->clear();
        delete this->head;
    }
}

// calculate the hash value based on provided key
std::size_t Map::calcHash(const std::string &key) {
    std::size_t sum = 0;
    for(std::string::size_type i=0; i<key.size(); i++) {
        sum += key[i];
    }
    return sum%this->size;
}

// insert element with provided key into Map instance
// throw runtime-error exception if not insertable
void Map::insert(const std::string &key, const std::vector<Item> &order) {
    std::size_t hashedKey = this->calcHash(key);
    MapElement* cur = this->head;

    // run to the slot at index based on key
    while(hashedKey > 0) {
        cur = cur->arr;
        --hashedKey;
    }

    // first run to find out whether element exists 
    MapElement* tmp = cur; 

    while(tmp != nullptr) {

        // if current slot is not empty
        if(!tmp->empty) {

            // shift to the right if deleted is marked or key in current slot is not equal to provided key
            if(tmp->deleted || tmp->key.compare(key) != 0) tmp = tmp->arr;

            // found the element based on provided key
            else {
                tmp->empty = false;
                tmp->deleted = false;
                tmp->key = key;
                tmp->value = order;
                return;
            }
        }

        // stop if current slot is empty
        else break;
    }

    // shift to right if current slot is not empty and key in that slot is not equal to provided key
    while(cur != nullptr && !cur->empty && !cur->deleted && cur->key.compare(key) != 0) {
        cur = cur->arr;
    }

    // insert value into Map instance
    if(cur != nullptr) {
        cur->empty = false;
        cur->deleted = false;
        cur->key = key;
        cur->value = order;
    }
    // or throw runtime_error if no free slot is found
    else throw std::runtime_error("No free slot to insert the element");
}

// remove element with provided key from Map instance, if exists
void Map::remove(const std::string &key) {
    std::size_t hashedKey = this->calcHash(key);
    MapElement* cur = this->head;

    // run to the slot at index based on key
    while(hashedKey > 0) {
        cur = cur->arr;
        --hashedKey;
    }

    while(cur != nullptr) {

        // if current slot is not empty
        if(!cur->empty) {

            // shift to the right if deleted is marked or key in current slot is not equal to provided key
            if(cur->deleted || cur->key.compare(key) != 0) cur = cur->arr;

            // found the element based on provided key
            else {
                cur->deleted = true;
                break;
            }
        }

        // stop if current slot is empty
        else break;
    }
}

// get element with provided key from Map instance, if exists
// return empty value otherwise
std::vector<Item> Map::get(const std::string &key) {
    std::size_t hashedKey = this->calcHash(key);
    MapElement* cur = this->head;

    // run to the slot at index based on key
    while(hashedKey > 0) {
        cur = cur->arr;
        --hashedKey;
    }

    while(cur != nullptr) {

        // if current slot is not empty
        if(!cur->empty) {

            // shift to the right if deleted is marked or key in current slot is not equal to provided key
            if(cur->deleted || cur->key.compare(key) != 0) cur = cur->arr;

            // found the element based on provided key
            else return cur->value;
        }

        // stop if current slot is empty
        else break;
    }

    return std::vector<Item>();
}



