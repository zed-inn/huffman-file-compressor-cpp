#include "../headers/common.h"
#include "../headers/namespace.h"

char convert_firs8_2bit(string &str)
{
    string byte = str.substr(0, 8);
    str.erase(str.begin(), str.begin() + 8);

    char byte_char = static_cast<char>(bitset<8>(byte).to_ulong());
    return byte_char;
}

string convert_char_2bits(char c)
{
    bitset<8> bits(c);
    string binary_str = bits.to_string();

    return binary_str;
}