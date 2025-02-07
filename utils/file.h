#include "../headers/common.h"
#include "../headers/types.h"
#include "../headers/dsa.h"
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

        vpci get_char_chart()
        {
            mci char_chart_dict;

            char x;
            while (f.get(x))
                char_chart_dict[x] += 1;

            vpci char_chart;
            for (auto &x : char_chart_dict)
                char_chart.push_back(x);

            quicksort(char_chart);

            return char_chart;
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

            vpci char_chart = get_char_chart();

            return true;
        }
    };
}
#endif