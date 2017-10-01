#ifndef ABLEDECODER_FORMCHUNK_H
#define ABLEDECODER_FORMCHUNK_H


#include "FileChunk.h"
#include "AbleChunk.h"
#include "FormatVersionChunk.h"
#include "CommonChunk.h"
#include "SoundDataChunk.h"

class FormChunk : public FileChunk {
public:
    FormChunk();

    void read(std::istream &input);

protected:
    void readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) override;

    void writeData(std::ostream &output) override;

private:
    FormatVersionChunk formatVersionChunk;

    AbleChunk ableChunk;

    CommonChunk commonChunk;

    SoundDataChunk soundDataChunk;
};


#endif //ABLEDECODER_FORMCHUNK_H
