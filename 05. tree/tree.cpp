#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	int data;
	Node* parent;
	vector<Node*> children;

	Node() {
		data = 0;
		parent = NULL;
	}

	Node(int d) {
		data = d;
		parent = NULL;
	}

	~Node() {}

	void insertChild(Node* chi) {
		children.push_back(chi);
		return;
	}

	void delChild(Node* chi) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i] == chi) {
				children.erase(children.begin() + i);
				break;
			}
		}
		return;
	}

	bool isRoot() {
		if (parent == NULL)
			return true;
		else
			return false;
	}
};

class GeneralTree {
public:
	Node* root;
	vector<Node*> nodeList;
	//메서드
	GeneralTree() {
		root = new Node(1);
		nodeList.push_back(root);
	}
	GeneralTree(int data) {
		root = new Node(data);
	}
	~GeneralTree() {
	}
	void setRoot(int data) {
		root = new Node(data);
	}
	Node* getRoot() {
		return root;
	}
	void insertNode(int parent_data, int data) {
		Node* par = findNode(parent_data);
		if (par != NULL) {
			Node* newnode = new Node(data);
			par->insertChild(newnode);
			nodeList.push_back(newnode);
			newnode->parent = par;
		}
		else {
			cout << -1 << endl;
			return;
		}
	}
	void delNode(int data) {
	}

	Node* findNode(int data) {
		Node* find = NULL;;
		for (int j = 0; j < nodeList.size(); j++) {
			if (nodeList[j]->data == data)
				find = nodeList[j];
		}
		return find;
	}
	void printChild(int data) {
		Node* par = findNode(data);
		if (par != NULL) { //부모가 있음
			if (par->children.size() == 0) { // 부모있음 자식이 없음
				cout << 0;
			}
			else { //부모있음 자식있음
				for (int j = 0; j < par->children.size(); j++) {
					cout << par->children[j]->data << " ";
				}
			}
		}
		else { // 부모없음
			cout << -1;
			return;
		}
	}

	int printDepth(int data) {
		Node* node = findNode(data);
		if (node == NULL) { // 못찾음;
			return -1;
		}
		else {
			if (node->parent == NULL) { // root
				return 0;
			}
			else {
				return 1 + printDepth(node->parent->data);
			}
		}
	}

	void preorder(Node* node) {
		cout << node->data << " ";
		for (int i = 0; i < node->children.size(); i++) {
			preorder(node->children[i]);
		}
	}
	void postorder(Node* node) {
		for (int i = 0; i < node->children.size(); i++) {
			postorder(node->children[i]);
		}
		cout << node->data << " ";
	}

	void printHeight() {
		int nodedata = 0;
		int height = 0;
		for (int i = 0; i < nodeList.size(); i++) {
			nodedata = nodeList[i]->data;
			int depth = printDepth(nodedata);
			if (depth > height)
				height = depth;
		}
		cout << height << endl;
	}
};

int main()
{
	int testcase = 0;
	cin >> testcase;
	string input;
	GeneralTree gtree;

	for (int i = 0; i < testcase; i++) {

		cin >> input;
		if (input == "insert") {
			int par = 0;
			int chil = 0;
			cin >> par >> chil;
			gtree.insertNode(par, chil);
		}
		else if (input == "printChild") {
			int par = 0;

			cin >> par;
			gtree.printChild(par);
			cout << endl;
		}
		else if (input == "printDepth") {
			int node = 0;
			cin >> node;
			cout << gtree.printDepth(node) << endl;
		}
		else if (input == "printHeight") {
			gtree.printHeight();
		}
		else if (input == "printPreorder") {
			gtree.preorder(gtree.root);
			cout << endl;
		}
		else if (input == "printPostorder") {
			gtree.postorder(gtree.root);
			cout << endl;
		}
		else {
			i--;
			continue;
		}
	}

	return 0;
} 