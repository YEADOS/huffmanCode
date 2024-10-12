#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

// A Huffman tree node
struct Node {
    char ch;           // The character
    int freq;          // Frequency of the character
    Node *left, *right; // Left and right child

    // Constructor for leaf node
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // Constructor for internal node
    Node(int f, Node* l, Node* r) : ch('\0'), freq(f), left(l), right(r) {}
};

// Comparison object to be used to order the heap (priority queue)
struct Compare {
    bool operator()(Node* l, Node* r) {
        // The highest priority item has the lowest frequency
        return l->freq > r->freq;
    }
};

// Utility function to check if the node is a leaf
bool isLeaf(Node* root) {
    return !root->left && !root->right;
}

// Traverse the Huffman Tree and store Huffman Codes in a map.
void generateCodes(Node* root, const std::string& str,
                   std::unordered_map<char, std::string>& huffmanCode)
{
    if (root == nullptr)
        return;

    // Found a leaf node
    if (isLeaf(root)) {
        // Handle the case when the input text contains only one unique character
        huffmanCode[root->ch] = str != "" ? str : "1";
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

// Builds Huffman Tree and generates Huffman codes
Node* buildHuffmanTree(const std::string& text)
{
    // Count frequency of appearance of each character
    std::unordered_map<char, int> freq_map;
    for (char ch : text) {
        freq_map[ch]++;
    }

    // Create a priority queue to store live nodes of Huffman tree
    auto cmp = [](Node* l, Node* r) { return l->freq > r->freq; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> minHeap(cmp);

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair : freq_map) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Special case: For texts with only one unique character
    if (minHeap.size() == 1) {
        minHeap.push(new Node('\0', 0)); // Add an extra node
    }

    // Iterate until the size of heap becomes one
    while (minHeap.size() != 1)
    {
        // Remove the two nodes of highest priority (lowest frequency)
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();

        // Create a new internal node with these two nodes as children
        int sum = left->freq + right->freq;
        minHeap.push(new Node(sum, left, right));
    }

    // The remaining node is the root node and the tree is complete
    return minHeap.top();
}

// Utility function to free the allocated memory for the tree
void freeTree(Node* root) {
    if (root == nullptr)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Function to decode the encoded text using the Huffman tree
std::string decode(Node* root, const std::string& encodedText) {
    std::string decodedText;
    Node* current = root;
    for (char bit : encodedText) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        // Reached a leaf node
        if (isLeaf(current)) {
            decodedText += current->ch;
            current = root;
        }
    }
    return decodedText;
}

int main()
{
    std::string text;
    std::cout << "Enter text to encode: ";
    std::getline(std::cin, text);

    if (text.empty()) {
        std::cout << "Empty string provided.\n";
        return 0;
    }

    // Build Huffman Tree
    Node* root = buildHuffmanTree(text);

    // Generate Huffman Codes
    std::unordered_map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Print the Huffman Codes
    std::cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    // Encode the text
    std::string encodedText;
    for (char ch : text) {
        encodedText += huffmanCode[ch];
    }

    std::cout << "\nEncoded Text:\n" << encodedText << "\n";

    // Decode the encoded text using the decode function
    std::string decodedText = decode(root, encodedText);

    std::cout << "\nDecoded Text:\n" << decodedText << "\n";

    // Free the allocated memory
    freeTree(root);

    return 0;
}
