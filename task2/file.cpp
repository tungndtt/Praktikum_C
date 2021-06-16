#include "file.hpp"
#include <sstream>
#include <iostream>

File::File(std::string path, std::ios_base::openmode mode) {
    this->file.open(path, mode);
    std::cout << "Open file from path " << path << std::endl;
}

File::~File() {
    this->file.close();
}

std::string File::getline() {
    std::string line;
    std::getline(this->file, line);
    return line;
}

void File::write(const std::string& content) {
    this->file << content;
}

bool File::hasNextLine() {
    return this->file.peek() != EOF;
}