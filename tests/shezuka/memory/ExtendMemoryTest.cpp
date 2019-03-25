#include <shezuka/memory/ArrayMemory.h>
#include <cstring>
#include <cassert>
#include <stdio.h>
#include <stdexcept>
#include <string>

using namespace std;

template<class T>
void do_assertions(const shezuka::memory::ArrayMemory<T> &am, const std::string &str) {
    const size_t str_len = str.length();
    assert(am.size() == str_len);
    assert(strlen((const char *) am) == str_len);
    assert(am.equals(str.c_str(), str_len));
}

int main() {
    shezuka::memory::ArrayMemory<char> am;

    string base_string{"Some data to test"};
    am.set_size(base_string.length());
    strcpy((char *) am, base_string.c_str());
    do_assertions(am, base_string);

    string new_string{"another value to test but it longer"};
    am.raise(new_string.length() - base_string.length());
    strcpy((char *) am, new_string.c_str());
    do_assertions(am, new_string);

    string sub_string = new_string.substr(0, 5);
    am.reduce(new_string.length() - sub_string.length());
    strcpy((char *) am, sub_string.c_str());
    do_assertions(am, sub_string);

    return 0;
}
