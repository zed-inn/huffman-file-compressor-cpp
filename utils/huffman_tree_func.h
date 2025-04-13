#include "./headers/common.h"
#include "./headers/dsa.h"
#include "./headers/types.h"
#include "./headers/namespace.h"

hf *reduce_last_two(vhf &char_chart)
{
    hf *left = char_chart[char_chart.size() - 1];
    hf *right = char_chart[char_chart.size() - 2];
    hf *new_head = new hf(left, right);

    new_head->set_weight(left->get_weight() + right->get_weight());

    char_chart.erase(char_chart.end() - 2, char_chart.end());
    char_chart.push_back(new_head);
    return new_head;
}

hf *reduce_to_head(vhf &char_chart)
{
    sort(char_chart.begin(), char_chart.end(), [](hf &a, hf &b)
         { return a.get_weight() > b.get_weight(); });

    if (char_chart.size() > 2)
    {
        reduce_last_two(char_chart);
        return reduce_to_head(char_chart);
    }

    switch (char_chart.size())
    {
    case 2:
        return reduce_last_two(char_chart);
        break;

    case 1:
        return char_chart[0];
        break;

    default:
        return nullptr;
        break;
    }
}
