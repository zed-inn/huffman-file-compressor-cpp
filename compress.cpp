#include "./utils/file.h"
#include "./headers/common.h"
#include "./headers/namespace.h"

using namespace Huffman;

int main()
{
    string filename = "./test/exm.txt"; // test file

    File f(filename);

    f.open();

    f.compress();

    f.close();

    return 0;
}
