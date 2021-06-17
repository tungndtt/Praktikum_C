#include <iostream>
#include <fstream>
#include "file.hpp"
#include "insertion_sort.hpp"
#include "plain_text_parser.hpp"
#include "csv_parser.hpp"

int main() {
    std::vector<std::string> supported_extensions = {
        "txt", "csv"  
    };

    std::vector<Parser*> parsers = {
        new PlainTextParser(),
        new CSVParser(),
    };

    std::vector<SortingStrategy*> sortStrategies = {
        new InsertionSort(),
    };

    File* sort_file = nullptr;
    File* write_file = nullptr;
    while (true) {
        std::cout << "###################### SORT-FILE PROGRAM ######################" << std::endl;
        
        std::cout << "Provide the path of file, that you want to sort: " << std::endl;
        std::string path;
        std::cin >> path;
        try {
            if(sort_file != nullptr) delete sort_file;
            sort_file = new File(path, std::fstream::in);
        }
        catch(std::ifstream::failure e) {
            std::cout << "!!!! This file path does not exist. Try again !!!!" << std::endl;
            continue;
        }

        std::string file_extension = path.substr(path.find_last_of(".") + 1);
        int parse_mode;
        std::string key;
        if(file_extension == "csv") {
            std::cout << "Provide the key, based on that you want to sort: ..." << std::endl;
            std::cin >> key;
            parse_mode = 1;
        }
        else if(file_extension == "txt") {
            parse_mode = 0;
            key = "0";
        }
        else {
            std::cout << "!!!! Unsupported sort-file extension !!!!" << std::endl;
            continue;
        }

        int sort_mode;
        while(true) {
            std::cout << "Sorting strategy: insertion-sort (0) ..." << std::endl;
            std::cin >> sort_mode;
            if(sort_mode < 0 || sort_mode >= sortStrategies.size()) {
                std::cout << "!!!! Unsupported sorting strategy. Please choose again !!!!" << std::endl;
            }
            else break;
        }
        
        std::cout << "Provide the path of file, that you want to write result " << std::endl;
        std::cin >> path;
        try {
            if(write_file != nullptr) delete write_file;
            write_file = new File(path, std::fstream::out);
        }
        catch(std::ofstream::failure e) {
            std::cout << "!!!! This file path does not exist. Try again !!!!" << std::endl;
            continue;
        }

        std::vector<Row> rows = parsers[parse_mode]->parse(*sort_file);
        sortStrategies[sort_mode]->sort(rows, key);
        parsers[parse_mode]->write(*write_file, rows);

        std::cout << std::endl;
        std::cout << "-------> Write done! Open the file the see result <-------" << std::endl;
        std::cout << std::endl;

        char c;
        bool _continue = false;
        while(true) {
            std::cout << "Do you want to retry ? (y/n) ..." << std::endl;
            std::cin >> c;
            if(c == 'n') break;
            else if(c == 'y') {
                _continue = true;
                break;
            }
            else {
                std::cout << "!!!! Invalid input. Just y/n !!!!" << std::endl;
            }
        }

        if(!_continue) break;
    }
    
    delete sort_file;
    delete write_file;

    for(Parser* parser : parsers) delete parser;
    for(SortingStrategy* sortStrategy : sortStrategies) delete sortStrategy;

    return 0;
}
