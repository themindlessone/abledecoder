#include "AbleChunk.h"
#include "Utils.h"

#include <openssl/evp.h>
#include <openssl/err.h>

AbleChunk::AbleChunk() : FileChunk(Utils::makeId({'a', 'b', 'l', 'e'})) {}

void AbleChunk::readData(std::istream &input, std::streamoff dataStart, int32_t dataSize) {
    this->keyIsValid = false;

    // skip useless 12 bytes
    input.seekg(12, std::ios::cur);

    uint32_t encryptedDataLength = Utils::readUint32(input);
    Array<uint8_t> encryptedData(encryptedDataLength);

    input.read(reinterpret_cast<char *>(&encryptedData[0]), encryptedData.getSize());

    this->decryptKey(encryptedData);
}

void AbleChunk::decryptKey(const Array<uint8_t> &encryptedData) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    const EVP_CIPHER *cipher = EVP_bf_cbc();

    uint8_t key[16] = {
            0x2B, 0xB1, 0x9D, 0x06, 0x98, 0xC3, 0xE1, 0xAB, 0x20, 0xC6,
            0xC1, 0x85, 0xFB, 0x7C, 0xD5, 0x17
    };

    uint8_t iv[8] = {
            0x28, 0x27, 0xC8, 0xE2, 0xC5, 0xEB, 0xA1, 0xB3
    };

    int success = EVP_DecryptInit_ex(ctx, cipher, 0, key, iv);

    if (!success) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("error decrypting data");
    }

    int decryptedDataLength;
    this->key.allocate(encryptedData.getSize() + EVP_CIPHER_CTX_block_size(ctx));

    success = EVP_DecryptUpdate(ctx, &this->key[0], &decryptedDataLength, &encryptedData[0], encryptedData.getSize());

    if (!success) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("error decrypting data");
    }

    int finalDataLength;
    success = EVP_DecryptFinal_ex(ctx, &this->key[decryptedDataLength], &finalDataLength);

    if (!success) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("error decrypting data");
    }

    decryptedDataLength += finalDataLength;

    EVP_CIPHER_CTX_free(ctx);

    if (12 + 256 > decryptedDataLength) {
        throw std::runtime_error("decrypted data is too short");
    }

    this->key.setView(12, 12 + 256);
    this->keyIsValid = true;
}

void AbleChunk::writeData(std::ostream &output) {
    throw std::runtime_error("not implemented");
}
