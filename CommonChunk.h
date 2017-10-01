#ifndef ABLEDECODER_COMMONCHUNK_H
#define ABLEDECODER_COMMONCHUNK_H

#include <array>

#include "FileChunk.h"

class CommonChunk : public FileChunk {
public:
    CommonChunk();

    void readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) override;

    void writeData(std::ostream &output) override;

    uint32_t getCompressionType() const {
        return compressionType;
    }

private:
    int16_t numChannels;

    uint32_t numSampleFrames;

    int16_t sampleSize;

    std::array<uint8_t, 10> sampleRate;

    uint32_t compressionType;
};


#endif //ABLEDECODER_COMMONCHUNK_H
