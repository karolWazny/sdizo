#ifndef SDIZO_1_TEXTFILEREADER_H
#define SDIZO_1_TEXTFILEREADER_H

#include <memory>
#include <string>
#include <fstream>


class TextFileReader {
public:
    std::unique_ptr<int32_t[]> fromFile(std::string filename);

private:
    void read(std::string);

    std::unique_ptr<int32_t[]> fileContent;
};


#endif //SDIZO_1_TEXTFILEREADER_H
