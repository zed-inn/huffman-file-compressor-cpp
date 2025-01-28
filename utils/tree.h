#include <vector>
#include <map>
#include <string>
#include "../constants/constants.h"

using namespace std;

typedef pair<char, int> pci;
typedef vector<pci> vpci;
typedef map<char, string> mcs;
typedef map<char, int> mci;

class Binary_Tree
{
public:
    pci value{'\0', 0};
    Binary_Tree *left = nullptr;
    Binary_Tree *right = nullptr;

    Binary_Tree() {}
    Binary_Tree(pci val) : value(val) {}
    Binary_Tree(pci val, Binary_Tree *left, Binary_Tree *right) : value(val), left(left), right(right) {}
};

void put_values(Binary_Tree *t, mcs &m, string binary)
{
    if (t->value.first != '\0')
    {
        m[t->value.first] = binary;
        return;
    }

    if (t->left != nullptr)
        put_values(t->left, m, binary + LEFT);
    if (t->right != nullptr)
        put_values(t->right, m, binary + RIGHT);
}