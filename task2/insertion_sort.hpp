#pragma once

#include "sorting_strategy.hpp"

class InsertionSort : public SortingStrategy {
public:
    virtual void sort(std::vector<Row>& rows, std::string& key);
};