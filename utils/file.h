#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include "strings.h"
#include "sort.h"
#include "../constants/constants.h"

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
    string write_filename = "";

public:
    ifstream file;
    ofstream write_file;
    File(string filename) : filename(filename), write_filename(filename + '.' + FILE_EXTENSION) {}

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

    void write_char_chart(mcs &char_chart)
    {
        write_file.open(write_filename, ios::trunc);
        if (!write_file)
        {
            cout << "Couldn't write in file" << endl;
            exit(1);
        }

        write_file << char_chart.size() << endl;
        for (auto &x : char_chart)
            write_file << x.first << " " << x.second << endl;

        write_file.close();
    }

    void save_compression(mcs &char_chart)
    {
        write_char_chart(char_chart);

        write_file.open(write_filename, ios::app);

        string line;
        while (getline(file, line))
        {
            string new_line = "";
            for (auto i : line)
                new_line += char_chart[i];

            write_file << new_line.length() << endl;
            for (int i = 0; i < new_line.length(); i += 8)
            {
                bitset<8> char_in_bits(new_line.substr(i, 8));
                char character = static_cast<char>(char_in_bits.to_ulong());
                write_file << character;
            }
            write_file << endl;
        }

        write_file.close();
    }
};