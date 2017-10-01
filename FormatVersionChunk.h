#ifndef ABLEDECODER_FORMATVERSIONCHUNK_H
#define ABLEDECODER_FORMATVERSIONCHUNK_H


#include "FileChunk.h"

class FormatVersionChunk : public FileChunk {
public:
    FormatVersionChunk();

    void readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) override;

    void writeData(std::ostream &output) override;
};


#endif //ABLEDECODER_FORMATVERSIONCHUNK_H
