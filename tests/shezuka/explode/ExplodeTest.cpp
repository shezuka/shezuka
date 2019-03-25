#include <shezuka/strings/explode.h>
#include <cassert>

using namespace shezuka::strings;

void basic_test() {
    std::string str = "string to explode";

    auto exploded = explode(str, " ");
    assert(exploded.size() == 3);
    assert(exploded[0] == std::string("string"));
    assert(exploded[1] == std::string("to"));
    assert(exploded[2] == std::string("explode"));
};

void advanced_test() {
    std::string str = "string to explode";

    auto exploded = explode(str, " to ");
    assert(exploded.size() == 2);
    assert(exploded[0] == std::string("string"));
    assert(exploded[1] == std::string("explode"));
}

int main() {
    basic_test();
    advanced_test();
    return 0;
}