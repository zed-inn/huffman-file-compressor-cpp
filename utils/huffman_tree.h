class HuffmanTree
{
private:
    HuffmanTree *left, *right;
    int weight;

public:
    char value;

    HuffmanTree(HuffmanTree *left) : left(left) {}
    HuffmanTree(HuffmanTree *left, HuffmanTree *right) : left(left), right(right) {}
    HuffmanTree(char value, int weight) : value(value), weight(weight) {}
    HuffmanTree() : value('\0'), left(nullptr), right(nullptr) {}

    void set_weight(int weight)
    {
        this->weight = weight;
    }

    void set_left(HuffmanTree *left)
    {
        this->left = left;
    }

    void set_right(HuffmanTree *right)
    {
        this->right = right;
    }

    int get_weight()
    {
        return this->weight;
    }

    char get_char()
    {
        return this->value;
    }

    bool is_leaf_node()
    {
        return this->left == nullptr && this->right == nullptr;
    }
};