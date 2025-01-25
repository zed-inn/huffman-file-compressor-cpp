#include "tree.h"

typedef vector<Binary_Tree> vbt;

void quicksort(vpci &char_chart)
{
    if (char_chart.size() <= 1)
        return;

    pci pivot = char_chart[0];

    vpci less, greater, equals;

    bool greater_sorted = true, less_sorted = true;

    for (auto &x : char_chart)
    {
        if (x.second > pivot.second)
        {
            // also check if the greater or less are sorted already
            if (greater_sorted && (greater.size() > 0) && (x.second < greater[greater.size() - 1].second))
                greater_sorted = false;
            greater.push_back(x);
        }
        else if (x.second < pivot.second)
        {
            if (less_sorted && (less.size() > 0) && (x.second < less[less.size() - 1].second))
                less_sorted = false;
            less.push_back(x);
        }
        else
            equals.push_back(x);
    }

    // so we don't have to sort those that are already sorted
    if (!less_sorted)
        quicksort(less);
    if (!greater_sorted)
        quicksort(greater);

    int k = 0;
    for (auto &x : less)
        char_chart[k++] = x;
    for (auto &x : equals)
        char_chart[k++] = x;
    for (auto &x : greater)
        char_chart[k++] = x;
}

void quicksort(vbt &tree)
{
    if (tree.size() <= 1)
        return;

    pci pivot = tree[0].value;

    vbt less, greater, equals;

    bool greater_sorted = true, less_sorted = true;

    for (auto &x : tree)
    {
        if (x.value.second > pivot.second)
        {
            // also check if the greater or less are sorted already
            if (greater_sorted && (greater.size() > 0) && (x.value.second < greater[greater.size() - 1].value.second))
                greater_sorted = false;
            greater.push_back(x);
        }
        else if (x.value.second < pivot.second)
        {
            if (less_sorted && (less.size() > 0) && (x.value.second < less[less.size() - 1].value.second))
                less_sorted = false;
            less.push_back(x);
        }
        else
            equals.push_back(x);
    }

    // so we don't have to sort those that are already sorted
    if (!less_sorted)
        quicksort(less);
    if (!greater_sorted)
        quicksort(greater);

    int k = 0;
    for (auto &x : less)
        tree[k++] = x;
    for (auto &x : equals)
        tree[k++] = x;
    for (auto &x : greater)
        tree[k++] = x;
}

vbt convert_to_binary_tree(vpci &char_chart)
{
    vbt values;
    for (auto &x : char_chart)
    {
        Binary_Tree *t = new Binary_Tree(x);
        values.push_back(x);
    }
    return values;
}

Binary_Tree * generate_huffman_tree(vbt tree){
    
}