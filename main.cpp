#include <bits/stdc++.h>
#include "utils/file.h"

using namespace std;

int main(int argc, char *argv[])
{
    string file_to_compress = get_filename(argc, argv);

    File f(file_to_compress);
    f.open();

    vpci char_chart = f.get_char_chart();

    for (auto &x : char_chart)
    {
        cout << "{ " << x.first << " , " << x.second << " }" << endl;
    }

    f.close();

    return 0;
}
