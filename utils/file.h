#include "../headers/common.h"
#include "../headers/types.h"
#include "../headers/namespace.h"

#ifndef FILE_H
#define FILE_H

namespace Huffman
{
    class File
    {
    private:
        ifstream f;
        ofstream f_out;

        dict_ci get_chart_map()
        {
            dict_ci chart_map;

            string line;
            while (getline(f, line))
                for (char i : line)
                    chart_map[i] += 1;

            return chart_map;
        }

    public:
        string input_filename;
        string output_filename;

        File(string filename) : input_filename(filename)
        {
            auto it = filename.rfind(".");
            if (it != string::npos)
                filename = filename.substr(0, it);

            output_filename = filename + "." + FILE_EXTENSION;
        }

        File(string input_filename,
             string output_filename) : input_filename(input_filename),
                                       output_filename(output_filename) {}

        // opens the input file
        bool open()
        {
            if (f.is_open())
            {
                cout << "File is already open" << endl;
                return false;
            }

            if (input_filename.length() == 0)
            {
                cout << "No input filename" << endl;
                return false;
            }

            f.open(input_filename);
            return true;
        }

        // close the input file
        bool close()
        {
            if (!f.is_open())
            {
                cout << "File is already close" << endl;
                return false;
            }

            f.close();
            return true;
        }

        bool compress()
        {
            if (!f.is_open())
            {
                cout << "File is not open" << endl;
                return false;
            }

            dict_ci chart_map = get_chart_map();

            for (auto x : chart_map)
                cout << x.first << " " << x.second << endl;

            return true;
        }
    };
}
#endif