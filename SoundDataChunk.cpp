#include "SoundDataChunk.h"
#include "Utils.h"

SoundDataChunk::SoundDataChunk() : FileChunk(Utils::makeId({'S', 'S', 'N', 'D'})) {}

void SoundDataChunk::readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) {
    uint32_t offset = Utils::readUint32(input);
    uint32_t blockSize = Utils::readUint32(input);

    if (offset != 0 || blockSize != 0)
        throw std::runtime_error("sound data offset or blockSize is not zero");

    this->soundData.allocate(static_cast<unsigned long>(dataSize) - 8);

    input.read(reinterpret_cast<char *>(&this->soundData[0]), dataSize - 8);
}

#define BYTEn(x, n)   (*((uint8_t*)&(x)+n))
#define BYTE0(x)   BYTEn(x,  0)
#define BYTE1(x)   BYTEn(x,  1)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)

void SoundDataChunk::decrypt(const Array<uint8_t> &key) {
    if (key.getSize() != 256) {
        throw std::invalid_argument("the size of key must be 256 bytes");
    }

    int8_t *ptr = &this->soundData[0];

    for (uint32_t i = 0; i < this->soundData.getSize(); ++i) {
        int8_t keyByte;

        if (*ptr && (keyByte = key[BYTE0(i) ^ BYTE1(i) ^ BYTE2(i) ^ BYTE3(i)], *ptr != keyByte)) {
            *ptr = *ptr ^ keyByte;
        }

        ++ptr;
    }
}

void SoundDataChunk::writeData(std::ostream &output) {
    Utils::writeUint32(output, 0); // offset
    Utils::writeUint32(output, 0); // blockSize

    output.write(reinterpret_cast<const char *>(&this->soundData[0]), this->soundData.getSize());
}
