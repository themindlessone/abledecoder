#include <iostream>
#include <fstream>

#include "FileChunk.h"
#include "FormChunk.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "usage: abledecoder <in> <out>" << std::endl;
        return 0;
    }

    std::string inPath = argv[1];
    std::string outPath = argv[2];

    FormChunk formChunk;

    std::ifstream input(inPath, std::ifstream::binary);

    if (!input.good()) {
        throw std::runtime_error("error opening input file: " + inPath);
    }

    try {
        formChunk.read(input);
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << "reading file " << inPath << " failed" << std::endl;

        input.close();
        return 0;
    }

    input.close();

    std::ofstream output(outPath, std::ofstream::binary);

    if (!output.good()) {
        throw std::runtime_error("error opening output file: " + outPath);
    }
    try {
        formChunk.write(output);
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << "writing file " << outPath << " failed" << std::endl;

        output.close();
        return 0;
    }

    output.close();

    return 0;
}
