#include<bits/stdc++.h>

class Binary_Tree
{
public:
    int value;
    Binary_Tree *left = nullptr;
    Binary_Tree *right = nullptr;

    Binary_Tree() {}
    Binary_Tree(int val) : value(val) {}
    Binary_Tree(int val, Binary_Tree *left, Binary_Tree *right) : value(val), left(left), right(right) {}
};