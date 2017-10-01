#include "FormatVersionChunk.h"
#include "Utils.h"

FormatVersionChunk::FormatVersionChunk() : FileChunk(Utils::makeId({'F', 'V', 'E', 'R'})) {}

void FormatVersionChunk::readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) {}

void FormatVersionChunk::writeData(std::ostream &output) {
    Utils::writeUint32(output, 0xA2805140);
}
