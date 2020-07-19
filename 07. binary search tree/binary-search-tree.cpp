#include <iostream>
#include <vector>
using namespace std;

// Data structure to store a Binary Search Tree node
class Node {
public:
	int data;
	Node* left, * right;
};
class bst {
public:
	Node* root;
	vector<Node*> elem;

	bst() {
		root = NULL;
	}
	~bst() {
		treeDestructor(root);
	}
	void treeDestructor(Node* r) {
		if (r == NULL)
			return;
		if (r->left != NULL)
			treeDestructor(r->left);
		if (r->right != NULL)
			treeDestructor(r->right);
		//cout << "delete" << endl;
		delete r;
	}

	// Function to create a new binary tree node having given key
	Node* newNode(int key)
	{
		Node* node = new Node;
		node->data = key;
		node->left = node->right = nullptr;

		return node;
	}

	// Function to perform inorder traversal of the BST
	void inorder(Node* root)
	{
		if (root == nullptr)
			return;

		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}

	void preorder(Node* root) {
		if (root == nullptr)
			return;
		cout << root->data << " ";
		preorder(root->left);
		preorder(root->right);

	}

	// Helper function to find maximum value node in subtree rooted at ptr
	Node* minkey(Node* ptr)
	{
		Node* tmp = ptr;
		while (tmp->left != nullptr) {
			tmp = tmp->left;
		}
		return tmp;
	}

	// Recursive function to insert an key into BST
	Node* insert(Node* root, int key)
	{
		// if the root is null, create a new node an return it
		if (root == nullptr) {
			Node* w = newNode(key);
			elem.push_back(w);
			return w;
		}


		// if given key is less than the root node, recur for left subtree
		if (key < root->data)
			root->left = insert(root->left, key);

		// if given key is more than the root node, recur for right subtree
		else
			root->right = insert(root->right, key);

		return root;
	}

	// Function to delete node from a BST. Note that root is passed by
	// reference to the function
	void deleteNode(Node*& root, int key)
	{
		// base case: key not found in tree
		if (root == nullptr)
			return;

		// if given key is less than the root node, recur for left subtree
		if (key < root->data)
			deleteNode(root->left, key);

		// if given key is more than the root node, recur for right subtree
		else if (key > root->data)
			deleteNode(root->right, key);

		// key found
		else
		{
			// Case 1: node to be deleted has no children (it is a leaf node)
			if (root->left == nullptr && root->right == nullptr)
			{
				// deallocate the memory and update root to null
				delete root;
				root = nullptr;
			}

			// Case 2: node to be deleted has two children
			else if (root->left && root->right)
			{
				// find its in-order predecessor node
				Node* predecessor = minkey(root->right);

				// Copy the value of predecessor to current node
				root->data = predecessor->data;

				// recursively delete the predecessor. Note that the
				// predecessor will have at-most one child (left child)
				deleteNode(root->right, predecessor->data);
			}

			// Case 3: node to be deleted has only one child
			else
			{
				// find child node
				Node* child = (root->left) ? root->left : root->right;
				Node* curr = root;

				root = child;

				// deallocate the memory
				delete curr;
			}
		}
	}

	int depth( int key) {
		int d = 0;
		Node* cur = root;
		while (cur != NULL && cur->data != key) {
			if (key < cur->data) 
				cur = cur->left;
			else
				cur = cur->right;
			d++;
		}

		if (cur == NULL) //Á¸Àçx
			return -1;
		return d;
	}

	int childNum(int key) {
		int num = 0;
		Node* cur = root;
		while (cur != NULL && cur->data != key) {
			if (key < cur->data)
				cur = cur->left;
			else
				cur = cur->right;
		}
		if (cur == NULL) //Á¸Àçx
			return -1;
		if (cur->left != NULL)
			num++;
		if (cur->right != NULL)
			num++;
		return num;
	}

	int height() {
		int maxH = depth(elem.at(0)->data);
		int h = 0;
		for (int i = 1; i < elem.size(); i++) {
			h = depth(elem.at(i)->data);
			if (maxH < h)
				maxH = h;
		}
		return maxH;
	}
};

// main function
int main()
{
	int numOfIns = 0;
	cout << "¸í·É¾î °¹¼ö : ";
	cin >> numOfIns;

	bst bst1;

	for (int a = 0; a < numOfIns; a++) {
		string instruction;
		cout << "instruction : ";
		cin >> instruction;

		if (instruction == "insert") {
			int key = 0;
			cin >> key;
			bst1.root = bst1.insert(bst1.root, key);
		}
		else if (instruction == "delete") {
			int key = 0;
			cin >> key;
			bst1.deleteNode(bst3.root, key);
		}
		else if (instruction == "depth") {
			int key = 0;
			cin >> key;
			int d = bst1.depth(key);
			if (d != -1)
				cout << ' ' << d;
		}
		else if (instruction == "children") {
			int key = 0;
			cin >> key;
			int cn = bst1.childNum(key);
				if( cn != -1)
					cout << cn;
				if (cn == -1)
					cout << 0;
		}
		else if (instruction == "height") {
			cout << bst1.height() << endl;
		}
		else if (instruction == "inorder") {
			bst1.preorder(bst1.root);
		}
		else if (instruction == "preorder") {
			bst1.preorder(bst1.root);
		}
		else {
			a--;
			continue;
		}
	}

	return 0;
} 