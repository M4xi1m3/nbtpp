#include <iostream>
#include <fstream>

#include "nbtpp/tag.hpp"
#include "nbtpp/nbt.hpp"
#include "nbtpp/nbtexception.hpp"
#include "stde/streams/gzip.hpp"

using namespace nbtpp;
using namespace stde;

int main(int argc, char** argv) {
    // std::ifstream f("tests/hell.mcr");
    // f.seekg(0x2005);

    std::ifstream f("tests/hello_world.nbt");
    nbtpp::nbt n(f);
    n.debug();
    std::cout << +n.getCompressionMethod() << std::endl;
}
