#include "huffman.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

bool isLeaf(node* huffmanRoot) {
    if (huffmanRoot->left == NULL && huffmanRoot->right == NULL) {
        return true;
    }
    return false;
}

std::unordered_map<char, int> getFrequency(std::string& input) {

    std::unordered_map<char, int> freqTable; 
    
    for(int i = 0; i < input.size(); i++) {
        freqTable[input[i]]++;
    }

    return freqTable;

}

node* constructTree(std::unordered_map<char, int>& freqTable) {

    std::priority_queue<node*, std::vector<node*>, MinComparator> minPQ;
    

    for (auto &c : freqTable) {
        node* newNode = new node(c.first, c.second);
        minPQ.push(newNode);

    }

    while(minPQ.size() > 1) {

        // The remaining node is the root node of the tree. 
        // if (minPQ.size() == 1) {
        //     return minPQ.top();
        // }

        node* first = minPQ.top();
        std::cout << "first: " << first->count;
        minPQ.pop();
        node* second = minPQ.top();
        std::cout << " --- second: " << second->count << "\n";
        minPQ.pop();

        // Create 
        int newNodeValue = first->count + second->count;
        node* newNode = new node(newNodeValue, first, second);

        minPQ.push(newNode);
    }

    return minPQ.top();
}

void createCodes(node* huffmanRoot, const std::string &code, std::unordered_map<char, std::string>& huffmanTable) {

    //
    if (huffmanRoot == NULL) {
        return;
    }

    if (isLeaf(huffmanRoot)) {
        huffmanTable[huffmanRoot->data] = code;
    }

    createCodes(huffmanRoot->left, code + "0", huffmanTable);
    createCodes(huffmanRoot->right, code + "1", huffmanTable);

}

std::string encode(std::string inputString, std::unordered_map<char, std::string>& huffmanTable) {

    std::string encodedString = "";

    for (char c : inputString) {
        encodedString += huffmanTable[c];
    }

    return encodedString;
}

std::string decode(node* huffmanRoot, std::string encodedText) {

    std::string decodedText = "";
    node* current = huffmanRoot;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        }
        if (bit == '1') {
            current = current->right;
        }

        if (isLeaf(current)) {
            decodedText += current->data;
            current = huffmanRoot;
        }

    }
    

    return decodedText;
    
}

void huffmanCode (std::string &input) {

    std::unordered_map<char, int> freqTable = getFrequency(input);

    node* root = constructTree(freqTable);
    
    std::unordered_map<char, std::string> huffmanTable;
    createCodes(root, "", huffmanTable);


    std::string encodedString = encode(input, huffmanTable);
    std::cout << "Encoded Text: " << encodedString << "\n";

    std::string decodedString = decode(root, encodedString);
    std::cout << "Decoded Text / Original : " << decodedString << "\n";

}

// int main() {


//     // std::string name = "AABBBCCABDA";
//     // std:: string name = "BCCABBDDAECCBBAEDDCC";
//     std::string name = "Advanced Algorithms is good";
//     std::unordered_map<char, int> freqTable = getFrequency(name);
//     node* root = constructTree(freqTable);

//     std::unordered_map<char, std::string> huffmanTable;

//     createCodes(root, "", huffmanTable);

//     for (auto &c : freqTable) {
//         std::cout << c.first << "freq: " << c.second << std::endl; 
//     }

//     for (auto x : huffmanTable) {
//         std::cout << x.first << "code: " << x.second << std::endl; 
//     }

//     std::string encodedString = encode(name, huffmanTable);
//     std::cout << "Encoded Text: " << encodedString << "\n";

//     std::string decodedString = decode(root, encodedString);
//     std::cout << "Decoded Text / Original : " << decodedString << "\n";

//     // node *root = new node('a', 5); 


// }