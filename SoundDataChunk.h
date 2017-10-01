#ifndef ABLEDECODER_SOUNDDATACHUNK_H
#define ABLEDECODER_SOUNDDATACHUNK_H


#include "FileChunk.h"
#include "Array.h"

class SoundDataChunk : public FileChunk {
public:
    SoundDataChunk();

    void readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) override;

    void writeData(std::ostream &output) override;

    void decrypt(const Array<uint8_t> &key);

private:
    Array<int8_t> soundData;
};


#endif //ABLEDECODER_SOUNDDATACHUNK_H
