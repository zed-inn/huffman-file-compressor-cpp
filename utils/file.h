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
        int total_chars = 0;

        vpci get_char_count()
        {
            mci char_chart_dict;

            char x;
            while (this->f.get(x))
            {
                char_chart_dict[x] += 1;
                ++this->total_chars;
            }

            vpci char_chart;
            for (auto &x : char_chart_dict)
                char_chart.push_back(x);

            return char_chart;
        }

        vhf get_char_chart(vpci &char_count)
        {
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

        // cleans the output file
        void clear_out_file()
        {
            this->f_out.open(this->output_filename, ios::trunc);
            this->f_out.close();
        }

        // opens the output file
        bool open_out()
        {
            if (this->f_out.is_open())
            {
                cout << "Output File is already open" << endl;
                return false;
            }

            if (this->output_filename.length() == 0)
            {
                cout << "No output filename" << endl;
                return false;
            }

            this->clear_out_file();
            this->f_out.open(this->output_filename, ios::app);
            return true;
        }

        // close the output file
        bool close_out()
        {
            if (!this->f_out.is_open())
            {
                cout << "Output File is already close" << endl;
                return false;
            }

            this->f_out.close();
            return true;
        }

        void reset()
        {
            this->close();
            this->open();
        }

        string write_content_padding(int &padding)
        {
            this->f_out << padding << "\n";

            string padded_string = "";
            for (int i = 0; i < padding; i++)
                padded_string += "0";
            return padded_string;
        }

        void write_content(mcs &codes, int padding)
        {
            this->reset();

            char ch;
            string coded_content = this->write_content_padding(padding);
            while (this->f.get(ch))
            {
                coded_content += codes[ch];
                while (coded_content.length() >= 8)
                    this->f_out << convert_firs8_2bit(coded_content);
            }
        }

        void write_header(mcs &codes)
        {
            int padding = 0, total_length = 0;
            for (auto x : codes)
                total_length += x.second.length() + 16;
            padding = (8 - total_length % 8) % 8;
            total_length = (total_length + padding) / 8;

            this->f_out << total_length << " " << padding << " ";

            string coded = "";
            for (int i = 0; i < padding; i++)
                coded += "0";

            for (auto x : codes)
                coded += convert_char_2bits(x.first) + convert_char_2bits((char)x.second.length()) + x.second;

            while (coded.length() >= 8)
                this->f_out << convert_firs8_2bit(coded);
        }

        bool compress()
        {
            if (!f.is_open())
            {
                cout << "File is not open" << endl;
                return false;
            }

            vpci char_count = this->get_char_count();
            vhf char_chart = this->get_char_chart(char_count);
            hf *head = reduce_to_head(char_chart);

            mcs coded_values;
            huffman_coded_values(head, coded_values);

            this->open_out();

            this->write_header(coded_values);
            int padding = 0;
            {
                for (auto x : char_count)
                    padding += (x.second * coded_values[x.first].length()) % 8;
                padding %= 8;
                padding = (8 - padding) % 8;
            }
            this->write_content(coded_values, padding);

            this->close_out();
            return false;
        }
    };
}
#endif