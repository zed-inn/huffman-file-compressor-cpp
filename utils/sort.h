#include <vector>
#include "tree.h"

using namespace std;

typedef pair<char, int> pci;
typedef vector<pci> vpci;

void quicksort(vpci &char_chart)
{
    if (char_chart.size() <= 1)
        return;

    pci pivot = char_chart[0];

    vpci less, greater;
    int equals = 0;

    for (auto &x : char_chart)
    {
        if (x.second > pivot.second)
            greater.push_back(x);
        else if (x.second < pivot.second)
            less.push_back(x);
        else
            equals++;
    }

    quicksort(less);
    quicksort(greater);

    int k = 0;
    for (auto &x : less)
        char_chart[k++] = x;
    for (int i = 0; i < equals; i++)
        char_chart[k++] = pivot;
    for (auto &x : greater)
        char_chart[k++] = x;
}

Binary_Tree generate_huffman_tree(vpci &char_chart)
{
    // TODO
}