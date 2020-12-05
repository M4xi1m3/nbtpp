#include <iostream>
#include <fstream>

#include "nbtpp/tag.hpp"
#include "nbtpp/nbt.hpp"
#include "nbtpp/nbtexception.hpp"
#include "stde/streams/gzip.hpp"

using namespace nbtpp;
using namespace stde;

int main(int argc, char** argv) {
    std::ifstream f("tests/issue_13.dat");
    nbtpp::nbt n(f);
    n.debug();
}
