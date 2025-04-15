#include "../headers/common.h"
#include "../headers/types.h"
#include "../headers/dsa.h"
#include "../headers/utils.h"
#include "../headers/namespace.h"

#ifndef FILE_H
#define FILE_H

namespace Huffman_Compression
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
            this->f_out.open(this->output_filename, ios::app | ios::binary);
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

        void out_write(string line)
        {
            for (auto x : line)
                this->f_out.write(&x, 1);
        }

        void out_write(char ch)
        {
            this->f_out.write(&ch, 1);
        }

        void write_header(mcs &codes)
        {
            int total_length = 0;
            int padding = 0;
            for (auto x : codes)
                total_length += 8 + 16 + x.second.length();
            padding = (8 - total_length % 8) % 8;
            total_length = (total_length + padding) / 8;

            string code = "";
            for (int i = 0; i < padding; i++)
                code += "0";

            this->out_write(to_string(total_length) + " " + to_string(padding) + " ");

            for (auto x : codes)
            {
                code += convert_char_2bits(x.first) + convert_int_2bits(x.second.length()) + x.second;
                while (code.length() >= 8)
                    this->out_write(convert_firs8_2bit(code));
            }
        }

        string write_content_padding(int &padding)
        {
            this->out_write(to_string(padding) + "\n");

            string padded_string = "";
            for (int i = 0; i < padding; i++)
                padded_string += "0";
            return padded_string;
        }

        void write_content(mcs &codes, int padding)
        {
            this->f.clear();
            this->f.seekg(0);

            char ch;
            string coded_content = this->write_content_padding(padding);
            while (this->f.get(ch))
            {
                coded_content += codes[ch];
                while (coded_content.length() >= 8)
                {
                    char ch_coded = convert_firs8_2bit(coded_content);
                    this->out_write(ch_coded);
                }
            }
        }

        void compress()
        {
            if (!this->f.is_open())
            {
                cout << "File is not open" << endl;
                return;
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
        }
    };
};

namespace Huffman_Decompression
{
    class File
    {
    private:
        ifstream f;
        ofstream f_out;
        hf *hf_tree = nullptr;

        mcs get_header()
        {
            char ch;
            int total_length = 0, padding = 0;
            while (this->f.get(ch) && ch != ' ')
                total_length = total_length * 10 + (ch - '0');
            this->f.get(ch);
            padding = ch - '0';
            this->f.get(ch);

            mcs codes;
            string header = "";

            for (int i = 0; i < total_length && f.get(ch); i++)
            {
                string char_decoded = convert_char_2bits(ch);
                if (i == 0)
                    header += char_decoded.substr(padding);
                else
                    header += char_decoded;
            }

            while (header.length() > 0)
            {
                char value = convert_firs8_2bit(header);
                int len = convert_16bits_2int(header);
                string code = header.substr(0, len);
                header.erase(header.begin(), header.begin() + len);
                codes[value] = code;
            }

            return codes;
        }

    public:
        string input_filename;
        string output_filename;

        File(string filename) : input_filename(filename)
        {
            auto it = filename.rfind(".");
            if (it != string::npos)
                filename = filename.substr(0, it);

            output_filename = filename + "." + DECOMPRESSED_FILE_EXTENSION;
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

            this->f.open(this->input_filename, ios::binary);
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

        void out_write(string line)
        {
            for (auto x : line)
                this->f_out.write(&x, 1);
        }

        void out_write(char ch)
        {
            this->f_out.write(&ch, 1);
        }

        void write_content()
        {
            char ch;
            this->f.get(ch);
            int padding = ch - '0';
            this->f.get(ch);

            hf *arrow = this->hf_tree;

            while (this->f.get(ch))
            {
                string code = convert_char_2bits(ch);
                for (int i = padding; i < code.length(); i++)
                {
                    if (code[i] == LEFT)
                        arrow = arrow->get_left();
                    else
                        arrow = arrow->get_right();

                    if (arrow->is_leaf_node())
                    {
                        this->out_write(arrow->value);
                        arrow = this->hf_tree;
                    }
                }
                padding = 0;
            }
            if (arrow->is_leaf_node())
                this->out_write(arrow->value);
        }

        void decompress()
        {
            if (!this->f.is_open())
            {
                cout << "File is not open" << endl;
                return;
            }

            mcs codes = this->get_header();
            this->hf_tree = reduce_to_head(codes);

            this->open_out();

            this->write_content();

            this->close_out();
        }
    };
};

#endif