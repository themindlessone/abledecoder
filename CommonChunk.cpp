#include "CommonChunk.h"
#include "Utils.h"

CommonChunk::CommonChunk() : FileChunk(Utils::makeId({'C', 'O', 'M', 'M'})) {}

void CommonChunk::readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) {
    this->numChannels = Utils::readInt16(input);
    this->numSampleFrames = Utils::readUint32(input);
    this->sampleSize = Utils::readInt16(input);
    input.read(reinterpret_cast<char *>(&this->sampleRate[0]), 10);
    this->compressionType = Utils::readId(input);
}

void CommonChunk::writeData(std::ostream &output) {
    Utils::writeInt16(output, this->numChannels);
    Utils::writeUint32(output, this->numSampleFrames);
    Utils::writeInt16(output, this->sampleSize);
    output.write(reinterpret_cast<const char *>(&this->sampleRate[0]), 10);
    Utils::writeId(output, Utils::makeId({'N', 'O', 'N', 'E'}));

    uint8_t count = 14;
    output.write(reinterpret_cast<const char *>(&count), 1);
    char compressionName[15] = {'n', 'o', 't', ' ', 'c', 'o', 'm', 'p', 'r', 'e', 's', 's', 'e', 'd', '\0'};
    output.write(compressionName, 15);
}
