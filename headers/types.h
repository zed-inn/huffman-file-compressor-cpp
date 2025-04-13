#include "./common.h"
#include "./dsa.h"
#include "./namespace.h"

#ifndef TYPES_H
#define TYPES_H

typedef pair<char, int> pci;
typedef unordered_set<char> usc;
typedef unordered_map<char, int> mci;
typedef unordered_map<char, string> mcs;
typedef vector<pair<char, int>> vpci;
typedef HuffmanTree hf;
typedef vector<hf *> vhf;

#endif