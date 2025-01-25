#include "utils/file.h"

int main(int argc, char *argv[])
{
    string file_to_compress = get_filename(argc, argv);

    File f(file_to_compress);
    f.open();

    vpci char_chart = f.get_char_chart();

    vbt tree = convert_to_binary_tree(char_chart);
    Binary_Tree *head = generate_huffman_tree(tree);

    mcs char_to_binary_string;

    put_values(head, char_to_binary_string, "");

    int i = 0;
    for (auto &x : char_to_binary_string)
    {
        cout << "{ " << x.first << " , " << x.second << " }" << endl;
        i++;
    }

    f.close();

    return 0;
}
