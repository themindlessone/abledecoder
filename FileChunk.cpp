#include "FileChunk.h"
#include "Utils.h"

FileChunk::FileChunk(uint32_t id) : id(id) {}

void FileChunk::write(std::ostream &output) {
    Utils::writeId(output, this->id);

    output.seekp(4, std::ios_base::cur);

    std::streampos contentBeginPosition = output.tellp();

    this->writeData(output);

    std::streampos contentEndPosition = output.tellp();

    output.seekp(contentBeginPosition - std::streamoff(4));

    auto dataSize = static_cast<int32_t>(contentEndPosition - contentBeginPosition);
    Utils::writeInt32(output, dataSize);

    output.seekp(contentEndPosition);

    if (dataSize % 2 == 1) {
        char padding[1] = {'\0'};
        output.write(padding, 1);
    }
}
