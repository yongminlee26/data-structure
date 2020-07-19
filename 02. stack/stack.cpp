// stack 구현
#include <iostream>
using namespace std;

class node {
public:
	int data;
	node* next;
};

class SLinkedList {
public:
	//멤버변수
	node* head;
	int num;
	//멤버함수
	SLinkedList() {
		head = new node; //더미노드
		head->next = NULL;
		head->data = 0;
		num = 0;
	}

	~SLinkedList() {
		while (!empty()) {
			removeFront();
		}
		delete head;
	}

	int empty() {
		if (num == 0)
			return 1;
		else
			return 0;
	};

	int front() {
		if (empty())
			return -1;
		else
			return head->next->data;
	};

	void addFront(int x) {
		node* newnode = new node;
		node* frontNode = head->next;
		newnode->next = frontNode;
		head->next = newnode;
		newnode->data = x;
		num++;
	}

	int removeFront() {
		if (empty())
			return -1;
		else {
			int frontData = head->next->data;
			node* delNode = head->next;
			head->next = delNode->next;
			delete delNode;
			num--;
			return frontData;
		}
	}
};

class Stack{
public:
	//멤버변수
	SLinkedList* sll;
	int number;
	//멤버함수
	SllStack() {
		sll = new SLinkedList;
		number = 0;
	}

	~SllStack() {
		while (!empty()) {
			pop();
		}
		delete sll;
	}

	int empty() {
		return sll->empty();
	}

	int size() {
		return number;
	}

	int top() {
		return sll->front();
	}

	void push(int n) {
		number++;
		sll->addFront(n);
	}

	int pop() {
		if(!empty())
			number--;
		return sll->removeFront();
	}

};

int main() {
	int casenum = 0;
	string instruc;
	Stack stack;
	cin >> casenum;
	for (int j = 0; j < casenum; j++) {
		cin >> instruc;
		if (instruc == "empty") {
			cout << stack.empty() << endl;
		}
		else if (instruc == "top") {
			cout << stack.top() << endl;
		}
		else if (instruc == "push") {
			int input = 0;
			cin >> input;
			stack.push(input);
		}
		else if (instruc == "pop") {
			cout << stack.pop() << endl;
		}
		else if (instruc == "size") {
			cout << stack.size() << endl;
		}
		else {
			j--;
			continue;
		}
	}

	return 0;
} 