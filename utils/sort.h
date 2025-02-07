#include "../headers/common.h"
#include "../headers/types.h"
#include "../headers/namespace.h"

#ifndef SORT_H
#define SORT_H

void quicksort(vpci &p)
{
    if (p.size() <= 1)
        return;

    vpci lesser, greater, equal;
    pci pivot = p[0];

    bool lesser_sorted = true, greater_sorted = true;

    for (auto &x : p)
    {
        if (x.second == pivot.second)
            equal.push_back(x);
        else if (x.second < pivot.second)
        {
            if (lesser_sorted && lesser.size() > 0 && lesser[lesser.size() - 1].second > x.second)
                lesser_sorted = false;
            lesser.push_back(x);
        }
        else
        {
            if (greater_sorted && greater.size() > 0 && greater[greater.size() - 1].second > x.second)
                greater_sorted = false;
            greater.push_back(x);
        }
    }

    if (!lesser_sorted)
        quicksort(lesser);
    if (!greater_sorted)
        quicksort(greater);

    int k = 0;
    for (auto x : lesser)
        p[k++] = x;
    for (auto x : equal)
        p[k++] = x;
    for (auto x : greater)
        p[k++] = x;
};

#endif