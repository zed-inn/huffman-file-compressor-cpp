#include "../headers/common.h"
#include "../headers/types.h"
#include "../headers/dsa.h"
#include "../headers/utils.h"
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

        vpci get_char_count()
        {
            mci char_chart_dict;

            char x;
            while (this->f.get(x))
                char_chart_dict[x] += 1;

            vpci char_chart;
            for (auto &x : char_chart_dict)
                char_chart.push_back(x);

            return char_chart;
        }

        vhf get_char_chart()
        {
            vpci char_count = this->get_char_count();
            vhf char_chart;

            for (auto x : char_count)
            {
                hf *node = new hf(x.first, x.second);
                char_chart.push_back(node);
            }

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
            if (this->f.is_open())
            {
                cout << "File is already open" << endl;
                return false;
            }

            if (this->input_filename.length() == 0)
            {
                cout << "No input filename" << endl;
                return false;
            }

            this->f.open(this->input_filename);
            return true;
        }

        // close the input file
        bool close()
        {
            if (!this->f.is_open())
            {
                cout << "File is already close" << endl;
                return false;
            }

            this->f.close();
            return true;
        }

        bool compress()
        {
            if (!f.is_open())
            {
                cout << "File is not open" << endl;
                return false;
            }

            vhf char_chart = this->get_char_chart();
            hf *head = reduce_to_head(char_chart);

            mcs coded_values;
            huffman_coded_values(head, coded_values);

            return false;
        }
    };
}
#endif