#ifndef ABLEDECODER_ABLECHUNK_H
#define ABLEDECODER_ABLECHUNK_H


#include "FileChunk.h"
#include "Array.h"

class AbleChunk : public FileChunk {
public:
    AbleChunk();

    void readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) override;

    void writeData(std::ostream &output) override;

    const Array<uint8_t> &getKey() const {
        if (!this->keyIsValid) {
            throw std::runtime_error("contains no decrypted key");
        }

        return key;
    };

private:
    void decryptKey(const Array<uint8_t> &encryptedData);

    Array<uint8_t> key;
    bool keyIsValid = false;
};


#endif //ABLEDECODER_ABLECHUNK_H
