#include "huffman.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <sstream>

bool isLeaf(node* huffmanRoot) {
    // If the node has no children, it is a leaf node
    if (huffmanRoot->left == NULL && huffmanRoot->right == NULL) {
        return true;
    }
    return false;
}

std::unordered_map<char, int> getFrequency(std::string& input) {
    // Count the frequency of each character in the input and store in the frequency table
    std::unordered_map<char, int> freqTable; 
    for(int i = 0; i < input.size(); i++) {
        freqTable[input[i]]++;
    }
    return freqTable;
}

node* constructTree(std::unordered_map<char, int>& freqTable) {
    // Create a priority queue to store the nodes
    // Greedy approach to select the two nodes with the lowest frequency
    std::priority_queue<node*, std::vector<node*>, MinComparator> minPQ;
    

    for (auto &c : freqTable) {
        node* newNode = new node(c.first, c.second);
        minPQ.push(newNode);

    }

    while(minPQ.size() > 1) {
        node* first = minPQ.top();
        minPQ.pop();

        node* second = minPQ.top();
        minPQ.pop();

        // Create 
        int newNodeValue = first->count + second->count;
        node* newNode = new node(newNodeValue, first, second);

        minPQ.push(newNode);
    }
    return minPQ.top();
}

void createCodes(node* huffmanRoot, const std::string &code, std::unordered_map<char, std::string>& huffmanTable) {

    // traverse the tree recursively creating the unique code for each character
    if (huffmanRoot == NULL) {
        return;
    }
    // once a leaf node is reached, add the character and its code to the huffman table S
    if (isLeaf(huffmanRoot)) {
        huffmanTable[huffmanRoot->data] = code;
    }
    // Traverse left and right and add 0 and 1 to the code respectively
    createCodes(huffmanRoot->left, code + "0", huffmanTable);
    createCodes(huffmanRoot->right, code + "1", huffmanTable);

}

std::string encode(std::string inputString, std::unordered_map<char, std::string>& huffmanTable) {

    // For each character in the input string, replace it with the corresponding huffman code
    std::string encodedString = "";
    for (char c : inputString) {
        encodedString += huffmanTable[c];
    }
    return encodedString;
}

std::string decode(node* huffmanRoot, std::string encodedText) {

    std::string decodedText = "";
    node* current = huffmanRoot;
    // If the tree is a single node
    if (isLeaf(current)) {
        for(int i = 0; i < encodedText.length(); i++) {
            decodedText += current->data;
        }
        return decodedText;
    }

    // If the tree has more than one node 
    for (char bit : encodedText) {
        // if the bit is 0, traverse left
        if (bit == '0') {
            current = current->left;
        }
        // if the bit is 1, traverse right
        if (bit == '1') {
            current = current->right;
        }
        // if the current node is a leaf, add the character to the decoded text 
        if (isLeaf(current)) {
            decodedText += current->data;
            current = huffmanRoot;
        }
    }
    return decodedText;
}

// return the bit size of the input text (8 bits per character ASCII) 
double originalBitSize(std::string input) {
    return input.size() * 8;
}

// return the bit size of the compressed text
double compressedbitSize(std::unordered_map<char, int> freqTable, std::unordered_map<char, std::string> huffmanTable) {
    
    // size is the sum of the message size and the table size
    int messageSize = 0;
    int tableSize = 0;

    // for each character in the frequency table, calculate the size of the message and table
    for (auto &leafNode : freqTable) {
        char character = leafNode.first;
        int frequency = leafNode.second;

        int bitLength = huffmanTable[character].length();
        messageSize += frequency * bitLength; // message size is the frequency of the character multiplied by the bit length of the character
        tableSize += 8 + bitLength; // table size is the size of the character (8 bits - ASCII) and the bit length of the character
    }
    // return the total size of the message and table
    return messageSize + tableSize;
}


std::string huffmanCode(std::string &input) {

    // return empty string if input is empty
    if (input.size() == 0) {
        return "";
    }
    
    // get the frequency of each character in the input 
    std::unordered_map<char, int> freqTable = getFrequency(input);
    // construct the huffman tree
    node* root = constructTree(freqTable);
    

    // create the huffman table and codes
    std::unordered_map<char, std::string> huffmanTable;
    if (freqTable.size() == 1) { // if there is only one character in the input
        huffmanTable[input[0]] = "0";
    } else { // more than one character in the input
        createCodes(root, "", huffmanTable);
    }

    // encode the input text
    std::string encodedString = encode(input, huffmanTable);
    // decode the encoded text
    std::string decodedString = decode(root, encodedString);

    // Storage calculations, effectivness and output
    double ogBitSize = originalBitSize(input);
    double compBitSize = compressedbitSize(freqTable, huffmanTable);
    double effectivness = ((ogBitSize - compBitSize) / ogBitSize) * 100;

    std::cout << "Original Text Size: " << "\033[34m" << ogBitSize << " bits" << "\033[0m" << "\n";
    std::cout << "Compressed Text Size: " << "\033[34m" << compBitSize << " bits" << "\033[0m" << "\n"; 
    std::cout << "Effectivness: " << "\033[31m" << int(effectivness) << "%" << "\033[0m" << "\n";

    return decodedString;

}


    // for (auto &c : freqTable) {
    //     std::cout << c.first << "freq: " << c.second << std::endl; 
    // }

    // for (auto x : huffmanTable) {
    //     std::cout << x.first << "code: " << x.second << std::endl; 
    // }

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