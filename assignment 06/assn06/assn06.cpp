// assn06.cpp : This file contains the 'main' function. Program execution begins and ends there.
// sources: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
// C program for Huffman Coding 
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <unordered_map>

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 

// A Huffman tree node 
struct MinHeapNode {

	// One of the input characters 
	char data;

	// Frequency of the character 
	unsigned freq;

	// Left and right child of this node 
	struct MinHeapNode* left, * right;
};

// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap {

	// Current size of min heap 
	unsigned size;

	// capacity of min heap 
	unsigned capacity;

	// Array of minheap node pointers 
	struct MinHeapNode** array;
};

// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
		sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

// A utility function to create 
// a min heap of given capacity 
struct MinHeap* createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	// current size is 0 
	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (struct MinHeapNode**)malloc(
		minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a,
	struct MinHeapNode** b)

{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size
		&& minHeap->array[left]->freq
		< minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size
		&& minHeap->array[right]->freq
		< minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
			&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check 
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap,
	struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i
		&& minHeapNode->freq
		< minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print a VECTOR, as modified by cl-anderson
void printVec(std::vector<int> vec, int n)
{
	int i;
	for (i = 0; i < vec.size(); ++i)
		printf("%d", vec[i]);

	printf("\n");
}

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap* createAndBuildMinHeap(std::vector<char> data,
	std::vector<int> freq, int size)

{

	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

// The main function that builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(std::vector<char> data,
	std::vector<int> freq, int size)

{
	struct MinHeapNode* left, * right, * top;

	// Step 1: Create a min heap of capacity 
	// equal to size. Initially, there are 
	// modes equal to size. 
	struct MinHeap* minHeap
		= createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) {

		// Step 2: Extract the two minimum 
		// freq items from min heap 
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		// Step 3: Create a new internal 
		// node with frequency equal to the 
		// sum of the two nodes frequencies. 
		// Make the two extracted node as 
		// left and right children of this new node. 
		// Add this node to the min heap 
		// '$' is a special value for internal nodes, not 
		// used 
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	// Step 4: The remaining node is the 
	// root node and the tree is complete. 
	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree. 
// It uses vec instead of arr to store codes since i, cl-anderson, modified it.
void printCodes(struct MinHeapNode* root, std::vector<int> vec,
	int top)

{

	// Assign 0 to left edge and recur 
	if (root->left) {

		vec[top] = 0;
		printCodes(root->left, vec, top + 1);
	}

	// Assign 1 to right edge and recur 
	if (root->right) {

		vec[top] = 1;
		printCodes(root->right, vec, top + 1);
	}

	// If this is a leaf node, then 
	// it contains one of the input 
	// characters, print the character 
	// and its code from vec (instead of arr as previously mentioned 
	if (isLeaf(root)) {

		printf("%c: ", root->data);
		printVec(vec, top);
	}
}

// The main function that builds a 
// Huffman Tree and print codes by traversing 
// the built Huffman Tree 
void HuffmanCodes(std::vector<char> data, std::vector<int> freq, int size)

{
	// Construct Huffman Tree 
	struct MinHeapNode* root
		= buildHuffmanTree(data, freq, size);

	// Print Huffman codes using 
	// the Huffman tree built above 
	std::vector<int> vec;
	int top = 0;

	printCodes(root, vec, top);
}

std::vector<char> readFile(std::ifstream& file)
{
	int size = 0;
	int count = 0;
	char c;
	std::vector<char> cvec;
	while (file.get(c))
	{
		cvec.push_back(c);
	}
	return cvec;
}

std::vector<int> getFreq(std::vector<char> vec)
{
	std::vector<int> freqvec;
	std::unordered_map<char, int> d;

	for (char i : vec) {
		d[i]++;
	}
	for (auto i = d.begin(); i != d.end(); i++)
	{
		freqvec.push_back(i->second);
	}
	return freqvec;
}
// Driver code 
int main()
{
	std::string filename = "";
	std::cout << "Enter the name of the file to create: ";
	std::cin >> filename;
	std::fstream writeFile;
	writeFile.open(filename);
	writeFile << "Test text for encoding";
	std::ifstream readingFile;
	readingFile.open(filename);
	
	std::vector<char> vec;
	vec = readFile(readingFile);
	std::vector<int> freq;
	freq = getFreq(vec);
	int size = vec.size() / sizeof(vec[0]);

	HuffmanCodes(vec, freq, size);

	return 0;
}
