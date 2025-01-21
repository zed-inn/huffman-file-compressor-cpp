#include <bits/stdc++.h>
#include "strings.h"
#include "sort.h"

using namespace std;

string get_directory(string file_location)
{
    file_location = replace_all_instances(file_location, '\\', '/');

    string directory = "";
    int i = file_location.length();
    while (file_location[i] != '/' && i >= 0)
        i--;

    if (i >= 0)
        directory = file_location.substr(0, i);
    directory += '/';

    return directory;
}

string get_filename(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "No filename/path given." << endl;
        exit(1);
    }

    return argv[1];
}

class File
{
private:
    string filename = "";

public:
    ifstream file;
    File(string filename) : filename(filename) {}

    void open()
    {
        file.open(filename);
        if (!file.is_open())
        {
            cout << "File doesn't exist, check location and name then try again" << endl;
            file.close();
            exit(1);
        }
    }

    vpci get_char_chart()
    {
        map<char, int> char_chart_map;

        string s;
        while (getline(file, s))
        {
            for (int i = 0; i < s.length(); i++)
                char_chart_map[s[i]] += 1;
        }

        vpci char_chart;
        for (auto &x : char_chart_map)
            char_chart.push_back(x);

        quicksort(char_chart);

        return char_chart;
    }

    void close()
    {
        file.close();
    }
};