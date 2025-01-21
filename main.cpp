#include <bits/stdc++.h>
#include "utils/file.h"

using namespace std;

int main(int argc, char *argv[])
{
    string file_to_compress = get_filename(argc, argv);

    File f(file_to_compress);
    f.open();

    string s;
    while (getline(f.file, s))
        cout << s << endl;

    f.close();

    return 0;
}
