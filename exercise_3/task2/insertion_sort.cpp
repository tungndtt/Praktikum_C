#include "insertion_sort.hpp"

void InsertionSort::sort(std::vector<Row>& rows, std::string& key) {
    for(int i=0; i<rows.size(); i++) {
        Row value = rows[i];
        int changeIdx = i;
        for(int j=i-1; j>=0; j--) {
            if(value.get(key) < rows[j].get(key)) {
                changeIdx = j;
            }
        }

        for(int c=i-1; c>=changeIdx; c--) {
            rows[c+1] = rows[c];
        }
        rows[changeIdx] = value;
    }
}