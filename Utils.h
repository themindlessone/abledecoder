#ifndef ABLEDECODER_UTILS_H
#define ABLEDECODER_UTILS_H

#include <array>
#include <cinttypes>

class Utils {
public:
    static uint32_t makeId(std::array<uint8_t, 4> id) {
        return *reinterpret_cast<uint32_t *>(id.data());
    }

    static uint32_t readId(std::istream &input) {
        uint32_t id;
        input.read(reinterpret_cast<char *>(&id), 4);
        return id;
    }

    static void writeId(std::ostream &output, uint32_t id) {
        output.write(reinterpret_cast<const char *>(&id), 4);
    }

    static uint32_t readUint32(std::istream &input) {
        uint32_t data;
        input.read(reinterpret_cast<char *>(&data), 4);
        return swapUint32(data);
    }

    static void writeUint32(std::ostream &output, uint32_t data) {
        uint32_t swappedData = swapUint32(data);
        output.write(reinterpret_cast<const char *>(&swappedData), 4);
    }

    static int32_t readInt32(std::istream &input) {
        int32_t data;
        input.read(reinterpret_cast<char *>(&data), 4);
        return swapInt32(data);
    }

    static void writeInt32(std::ostream &output, int32_t data) {
        int32_t swappedData = swapInt32(data);
        output.write(reinterpret_cast<const char *>(&swappedData), 4);
    }

    static int16_t readInt16(std::istream &input) {
        int16_t data;
        input.read(reinterpret_cast<char *>(&data), 2);
        return swapInt16(data);
    }

    static void writeInt16(std::ostream &output, int16_t data) {
        int16_t swappedData = swapInt16(data);
        output.write(reinterpret_cast<const char *>(&swappedData), 2);
    }

private:
    static uint16_t swapUint16(uint16_t val) {
        return (val << 8) | (val >> 8);
    }

    static int16_t swapInt16(int16_t val) {
        return (val << 8) | ((val >> 8) & (int16_t) 0xFF);
    }

    static uint32_t swapUint32(uint32_t val) {
        val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
        return (val << 16) | (val >> 16);
    }

    static int32_t swapInt32(int32_t val) {
        val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
        return (val << 16) | ((val >> 16) & 0xFFFF);
    }
};


#endif //ABLEDECODER_UTILS_H
