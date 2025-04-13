#include "../headers/common.h"
#include "../headers/dsa.h"
#include "../headers/types.h"
#include "../headers/namespace.h"

hf *reduce_first_two(vhf &char_chart)
{
    hf *left = char_chart[0];
    hf *right = char_chart[1];
    hf *new_head = new hf(left, right);

    new_head->set_weight(left->get_weight() + right->get_weight());

    char_chart.erase(char_chart.begin());
    char_chart.erase(char_chart.begin());

    char_chart.push_back(new_head);
    return new_head;
}

hf *reduce_to_head(vhf &char_chart)
{
    sort(char_chart.begin(), char_chart.end(), [](hf *a, hf *b)
         { return a->get_weight() < b->get_weight(); });

    if (char_chart.size() > 2)
    {
        reduce_first_two(char_chart);
        return reduce_to_head(char_chart);
    }

    switch (char_chart.size())
    {
    case 2:
        return reduce_first_two(char_chart);
        break;

    case 1:
        return char_chart[0];
        break;

    default:
        return nullptr;
        break;
    }
}

void print_tree(hf *root)
{
    if (!root)
    {
        cout << "Empty tree\n";
        return;
    }

    queue<hf *> q;
    q.push(root);

    while (!q.empty())
    {
        int levelSize = q.size();
        while (levelSize--)
        {
            hf *curr = q.front();
            q.pop();

            if (curr != nullptr)
            {
                if (curr->is_leaf_node())
                    cout << curr->value << " ";
                else
                    cout << "-" << " ";
                q.push(curr->get_left());
                q.push(curr->get_right());
            }
            else
            {
                cout << "null ";
            }
        }
        cout << "\n";
    }
}

void huffman_coded_values(hf *head, mcs &coded_values, string code_value = "")
{
    if (head->is_leaf_node())
        coded_values[head->value] = code_value;

    else
    {
        huffman_coded_values(head->get_left(), coded_values, code_value + LEFT);
        huffman_coded_values(head->get_right(), coded_values, code_value + RIGHT);
    }
}