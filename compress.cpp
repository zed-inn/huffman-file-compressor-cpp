#include "./utils/file.h"
#include "./headers/common.h"
#include "./headers/namespace.h"

using namespace Huffman;

int main()
{
    string filename = "./test/exm.txt";

    File f(filename);

    cout << f.open() << endl;
    cout << f.open() << endl;

    cout << f.close() << endl;
    cout << f.close() << endl;

    return 0;
}
