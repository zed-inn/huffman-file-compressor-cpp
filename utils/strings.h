#include <bits/stdc++.h>

using namespace std;

string replace_all_instances(string &source_string, char target, char replacement)
{
    string result = "";
    for (int i = 0; i < source_string.length(); i++)
    {
        if (source_string[i] == target)
            result += replacement;
        else
            result += source_string[i];
    }

    return result;
}
