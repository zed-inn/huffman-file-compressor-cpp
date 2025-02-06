#include "../headers/common.h"
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
                return false;

            if (input_filename.length() == 0)
                return false;

            f.open(input_filename);
            return true;
        }

        // close the input file
        bool close()
        {
            if (!f.is_open())
                return false;

            f.close();
            return true;
        }
    };
}
#endif