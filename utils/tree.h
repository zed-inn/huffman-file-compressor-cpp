#include <vector>

using namespace std;

typedef pair<char, int> pci;
typedef vector<pci> vpci;

class Binary_Tree
{
public:
    pci value;
    Binary_Tree *left = nullptr;
    Binary_Tree *right = nullptr;

    Binary_Tree() {}
    Binary_Tree(pci val) : value(val) {}
    Binary_Tree(pci val, Binary_Tree *left, Binary_Tree *right) : value(val), left(left), right(right) {}
};