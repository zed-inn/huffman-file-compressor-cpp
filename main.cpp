#include "./utils/file.h"
#include "./headers/common.h"
#include "./headers/namespace.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Required: type and input file" << endl;
        return -1;
    }

    const string operation = argv[1];
    const string input_filename = argv[2];
    string output_filename = "";
    if (argc >= 4)
        output_filename = argv[3];

    if (operation.compare("-c") == 0)
    {
        Huffman_Compression::File f(input_filename);
        if (output_filename != "")
            f.output_filename = output_filename;

        if (!f.open())
            return -1;

        f.compress();
        f.close();

        cout << "File Compressed successfully: " << f.output_filename << endl;
    }
    else if (operation.compare("-d") == 0)
    {
        Huffman_Decompression::File f(input_filename);
        if (output_filename != "")
            f.output_filename = output_filename;

        if (!f.open())
            return -1;

        f.decompress();
        f.close();

        cout << "File Decompressed successfully: " << f.output_filename << endl;
    }
    else
    {
        cerr << "Invalid operation" << endl;
        return -1;
    }

    return 0;
}
