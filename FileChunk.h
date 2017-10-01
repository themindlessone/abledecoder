#ifndef ABLEDECODER_FILECHUNK_H
#define ABLEDECODER_FILECHUNK_H


#include <iostream>
#include <cinttypes>

class FileChunk {
public:
    explicit FileChunk(uint32_t id);

    void write(std::ostream &output);

    virtual void readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) = 0;

    virtual void writeData(std::ostream &output) = 0;

    uint32_t getId() {
        return this->id;
    }

protected:
    const uint32_t id;
};

#endif //ABLEDECODER_FILECHUNK_H
