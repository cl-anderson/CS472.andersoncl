// assn06.cpp : This file contains the 'main' function. Program execution begins and ends there.
// sources: MAIN SOURCE was CS472 sample code as shown in lecture.
//			https://www.studysmarter.co.uk/explanations/computer-science/data-representation-in-computer-science/huffman-coding/
//			https://www.geeksforgeeks.org/how-to-read-file-character-by-character-in-cpp/
//			https://www.geeksforgeeks.org/print-characters-frequencies-order-occurrence/
//			https://www.geeksforgeeks.org/traversing-a-map-or-unordered_map-in-cpp-stl/
//          https://www.tutorialspoint.com/Read-whole-ASCII-file-into-Cplusplus-std-string

//
// File:   huggman.cpp
// Author: Your Glorious Instructior
// Purpose:
// Demonstrate Huffman encoding.
//
// Based on program found at: https://github.com/PetarV-/Algorithms/blob/master/Compression%20Algorithms/Huffman%20Coding.cpp
//
// The Huffman coding scheme assigns a variable-length prefix code to each
// character in a given set of characters, constructing an optimal lossless
// coding scheme with respect to the character distribution's entropy.

// The version implemented here analyses a given ASCII character string in
// order to obtain optimal codes based on character frequencies in the
// string. A more general version would receive a probability distribution
// instead.
//
// Complexity: O(n) time to construct O(H) time (on average) to encode/decode,
//             where H is the entropy
//

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

// The string to analyse
string str;

// Maps the encountered characters to their relative frequencies
map<char, double> P;

// The Huffman Tree
struct HuffTreeNode {
    double p;
    bool leaf;
    char letter;
    HuffTreeNode *parent;
    HuffTreeNode *l;
    HuffTreeNode *r;
    // nonleaf node
    HuffTreeNode(double p, HuffTreeNode *l, HuffTreeNode *r) {
        this -> p = p;
        this -> leaf = false;
        this -> letter = '\0';
        this -> parent = NULL;
        this -> l = l;
        this -> r = r;
        l -> parent = this;
        r -> parent = this;
    }
    // leaf node
    HuffTreeNode(double p, char c) {
        this -> p = p;
        this -> leaf = true;
        this -> letter = c;
        this -> parent = this -> l = this -> r = NULL;
    }
};

// Comparator of two node pointers
struct CmpNodePtrs {
    // As priority_queue is a max heap rather than min-heap,
    // invert the meaning of the < operator,
    // in order to get lower probabilities at the top
    bool operator()(const HuffTreeNode* lhs, const HuffTreeNode* rhs) const
    {
        return (lhs -> p) > (rhs -> p);
    }
};

// the root of the tree
HuffTreeNode *root;

// mapping each character to its leaf node (for quick encoding)
map<char, HuffTreeNode*> leaf;

// Produces the probability distribution (may be omitted if known in advance)
inline void analyse() {
    for (int i=0;i<str.length();i++) {
        P[str[i]]++;
    }
    for (auto it = P.begin();it!=P.end();it++) {
        P[it -> first] = it -> second / str.length();
    }
}

// Construct the Huffman Tree using the probability distribution
inline void build_tree() {
    priority_queue<HuffTreeNode*, vector<HuffTreeNode*>, CmpNodePtrs> pq;
    // First construct the leaves, and fill the priority queue
    for (auto it = P.begin();it!=P.end();it++) {
        leaf[it -> first] = new HuffTreeNode(it -> second, it -> first);
        pq.push(leaf[it -> first]);
    }
    while (pq.size() > 1) {
        HuffTreeNode* L = pq.top(); pq.pop();
        HuffTreeNode* R = pq.top(); pq.pop();
        // Spawn a new node generating the children
        HuffTreeNode* par = new HuffTreeNode((L -> p) + (R -> p), L, R);
        pq.push(par);
    }
    root = pq.top(); pq.pop();
}

// Huffman-encode a given character
inline string encode(char c) {
    string ret = "";
    HuffTreeNode* curr = leaf[c];
    while (curr -> parent != NULL) {
        if (curr == curr -> parent -> l) ret += "0";
        else if (curr == curr -> parent -> r) ret += "1";
        curr = curr -> parent;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

// Huffman-encode the given string
inline string encode(string s) {
    string ret = "";
    for (int i=0;i<s.length();i++) {
        ret += encode(s[i]);
    }
    return ret;
}

inline std::ofstream encodeof(string s) {
    std::ofstream ret;
    for (int i = 0; i < s.length(); i++) {
        ret << encode(s[i]);
    }
    return ret;
}

// Huffman-decode the given string
inline string decode(string s) {
    string ret = "";
    int i = 0;
    HuffTreeNode* curr;
    while (i < s.length()) {
        curr = root;
        while (!(curr -> leaf)) {
            if (s[i++] == '0') curr = curr -> l;
            else curr = curr -> r;
        }
        ret += curr -> letter;
    }
    return ret;
}

void encodeFile(string filename)
{
    ifstream file(filename);
    if (!file) {
        cerr << "can't open output file" << endl;
    }
    int size = 0;
    int count = 0;
    char c = 'x';
    string str;
    
    if (file)
    {
        while (file.get(c))
        {
            str.push_back(c);
        }
        std::cout << "String read in : " << str << std::endl;
        file.close();
    }
    else cerr << "File didn't open!\n";
    std::string encodedstr = encode(str);
    ofstream fileOut(filename);
    fileOut << encodedstr;
    fileOut.close();
}
int main() {
    str = "this is an example of a huffman tree";
    analyse();
    build_tree();
    string test = "aefhimnstloprux";

    for (int i=0; i<test.length(); i++) 
    {
        std::cout << "Encode(" << test[i] << ") = " << encode(test[i]) << std::endl;
    }

    std::cout << "Encoding of 'this is real':";
    std::cout << encode("this is real") << endl;

    std::ofstream outFile("huffmantest3.txt");
   
    outFile << "Test text to encode";
    outFile.close();
    std::cout << "Encoding file...\n";
    encodeFile("huffmantest3.txt");

    return 0;
    }