#include <iostream>
#include <fstream>

#include "nbtpp/tag.hpp"
#include "nbtpp/nbt.hpp"
#include "stde/streams/gzip.hpp"

using namespace nbtpp;
using namespace stde;

int main() {
    std::ifstream f("tests/bigtest.nbt");
    nbtpp::nbt n(f);

    n.debug();
}
