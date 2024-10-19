#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <sstream>

struct node {
    char data;
    int count;
    node *left, *right;

    // Leaf Node constructor has no children
    node(char data, int count) : data(data), count(count), left(NULL), right(NULL) {}
    // Internal Node constructor has no character data but has left and right child node
    // 0 creates empty character same as "\0"
    node(int count, node *left, node* right) : data(0), count(count), left(left), right(right) {}
};

// Required to create own comparator for priority queue as Greater<int> doesn't work with node pointers
struct MinComparator 
{
    bool operator()(node* left, node* right) {
        return left->count > right->count;
    }

};


bool isLeaf(node* huffmanRoot);

// Function to get a frequency of character in input text
std::unordered_map<char, int> getFrequency(std::string& input);

// Create the binary tree
node* constructTree(std::unordered_map<char, int> &freqTable);

// Generate codes and create huffman table 
void createCodes(node* huffmanRoot, const std::string &code, std::unordered_map<char, std::string>& huffmanTable);

// generate the encoded text using huffman table
std::string encode(std::string inputString, std::unordered_map<char, std::string>& huffmanTable);
// Decode the encoded text using huffman tree and encoded text
std::string decode(node* huffmanRoot, std::string encodedText);

std::string huffmanCode (std::string &input);





#endif // HUFFMAN