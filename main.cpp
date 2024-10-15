#include "huffman.h"
#include <iostream>
#include <stdio.h>
#include <string>


int main() {

    
    // std::string name = "AABBBCCABDA";
    // std:: string name = "BCCABBDDAECCBBAEDDCC";
    std::string input = "wefhjksdhjfksafhjklsadhfjadhjkfldhjfkadfjkhdfhdjkf";

    huffmanCode(input);

    // std::unordered_map<char, int> freqTable = getFrequency(name);
    // node* root = constructTree(freqTable);

    // std::unordered_map<char, std::string> huffmanTable;

    // // const std::string code = "adfasd";
    // createCodes(root, "", huffmanTable);

    // for (auto &c : freqTable) {
    //     std::cout << c.first << "freq: " << c.second << std::endl; 
    // }

    // for (auto x : huffmanTable) {
    //     std::cout << x.first << "code: " << x.second << std::endl; 
    // }

    // std::string encodedString = encode(name, huffmanTable);
    // std::cout << "Encoded Text: " << encodedString << "\n";

    // std::string decodedString = decode(root, encodedString);
    // std::cout << "Decoded Text / Original : " << decodedString << "\n";

    // node *root = new node('a', 5); 

    return 0;


}

