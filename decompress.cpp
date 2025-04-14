#include "./utils/file.h"
#include "./headers/common.h"
#include "./headers/namespace.h"

using namespace Huffman_Decompression;

int main()
{
    string filename = "./test/exm.compressed"; // test file

    File f(filename);

    f.open();

    f.decompress();

    f.close();

    return 0;
}
