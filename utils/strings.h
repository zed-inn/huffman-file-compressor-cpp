#include <string>

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

string replace_instance(string &source_string, string target, string replacement)
{
    bool replaced = false;
    string result = "";
    for (int i = 0; i < source_string.length(); i++)
    {
        int j = i, k = 0;
        for (; k < target.length() && j < source_string.length(); k++, j++)
        {
            if (source_string[j] != target[k])
                break;
        }
        if (j - i == target.length() && k == target.length())
            replaced = true;
        if (replaced)
        {
            result = source_string.substr(0, i) + replacement + source_string.substr(j);
            break;
        }
    }

    return result;
}