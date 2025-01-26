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

namespace compress
{
    class File
    {
    private:
        string filename = "";
        string write_filename = "";
        short padding = 0;
        mci char_chart_in_num;

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
            mci char_chart_map;

            char ch;
            while (file.get(ch))
                char_chart_map[ch] += 1;

            char_chart_in_num = char_chart_map;

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

            bitset<8> to_bits;
            int pad = 0;

            string chart;
            for (auto &x : char_chart)
            {
                pad += (x.second.length() * char_chart_in_num[x.first]) % 8;
                to_bits = x.first;
                chart += to_bits.to_string();
                to_bits = ' ';
                chart += to_bits.to_string();
                chart += x.second;
                to_bits = '\n';
                chart += to_bits.to_string();
            }

            int chart_padding = (8 - (chart.length() % 8)) % 8;
            for (int i = 0; i < chart_padding; i++)
                chart += '0';

            write_file << chart.length() / 8 << ' ';
            write_file << chart_padding << ' ';
            while (chart.length() > 0)
            {
                bitset<8> string_to_bits(chart.substr(0, 8));
                unsigned char ch = static_cast<unsigned char>(string_to_bits.to_ulong());
                write_file << ch;
                chart.erase(0, 8);
            }
            write_file << ' ';

            padding = (8 - (pad % 8)) % 8;
            write_file << padding;
            write_file << ' ';

            write_file.close();
        }

        void save_compression(mcs &char_chart)
        {
            write_char_chart(char_chart);

            write_file.open(write_filename, ios::app);

            string line;
            char ch;
            while (file.get(ch))
            {
                line += char_chart[ch];

                if (line.length() >= 8)
                {
                    bitset<8> char_in_bits(line.substr(0, 8));
                    unsigned char character = static_cast<unsigned char>(char_in_bits.to_ulong());
                    write_file << character;
                    line.erase(0, 8);
                }
            }
            for (short i = 0; i < padding; i++)
                line += '0';

            if (line.length() >= 8)
            {
                bitset<8> char_in_bits(line.substr(0, 8));
                unsigned char character = static_cast<unsigned char>(char_in_bits.to_ulong());
                write_file << character;
                line.erase(0, 8);
            }

            write_file.close();
        }
    };
}