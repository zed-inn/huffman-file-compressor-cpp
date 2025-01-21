#include <bits/stdc++.h>
#include "tree.h"

using namespace std;

typedef pair<char, int> pci;
typedef vector<pci> vpci;

void quicksort(vpci &char_chart)
{
    if (char_chart.size() <= 1)
        return;

    pci pivot = char_chart[0];

    vpci less, greater, equal;

    for (auto &x : char_chart)
    {
        if (x.second > pivot.second)
            greater.push_back(x);
        else if (x.second < pivot.second)
            less.push_back(x);
        else
            equal.push_back(x);
    }

    quicksort(less);
    quicksort(greater);

    int k = 0;
    for (auto &x : less)
        char_chart[k++] = x;
    for (auto &x : equal)
        char_chart[k++] = x;
    for (auto &x : greater)
        char_chart[k++] = x;
}

Binary_Tree generate_huffman_tree(vpci &char_chart){
    // TODO: create a huffman tree/table
}