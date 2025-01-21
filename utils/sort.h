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
            equals++;
    }

    // so we don't have to sort those that are already sorted
    if (!less_sorted)
        quicksort(less);
    if (!greater_sorted)
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
}