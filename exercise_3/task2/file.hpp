#pragma once

#include <string>
#include <fstream>

class File {
public:
    File(std::string path, std::ios_base::openmode mode);
    ~File();
    std::string getline();
    void write(const std::string& content);
    bool hasNextLine();
    File(const File& other_file) = delete;

private:
    std::fstream file;
};