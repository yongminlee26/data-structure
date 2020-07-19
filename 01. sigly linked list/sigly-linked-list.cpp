//sigly linked list 구현
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
		while (!empty())
			removeFront();
		delete head;
	}

	int empty() {
		if (num == 0)	//비어있음
			return 1; 
		else            //안 빔
			return 0;
	}

	int front() {
		if (empty())
			return -1;
		else
			return head->next->data;
	}

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

	void showList() {
		if (empty())
			cout << -1;
		else {
			node* cur = head->next;	
			for (int j = 0; j < num; j++) {
				cout << cur->data << ' ';
				cur = cur->next;

			}
		}
		cout << endl;
	}

	void addBack(int x) {
		node* lastNode = head;
		for (int j = 0; j < num; j++) {
			lastNode = lastNode->next;
		}
		node* newNode = new node;
		newNode->data = x;
		newNode->next = NULL;
		lastNode->next = newNode;
		num++;
	}

};
int main() {
	int casenum = 0;
	string instruc;
	SLinkedList sll;
	cin >> casenum;
	for (int j = 0; j < casenum; j++) {
		cin >> instruc;
		if (instruc == "addFront") {
			int input = 0;
			cin >> input;
			sll.addFront(input);
		}
		else if (instruc == "removeFront") {
			cout << sll.removeFront() << endl;
		}
		else if (instruc == "front") {
			cout << sll.front() << endl;
		}
		else if (instruc == "empty") {
			cout << sll.empty() << endl;
		}
		else if (instruc == "showList") {
			sll.showList();
		}
		else {	//addBack
			int input = 0;
			cin >> input;
			sll.addBack(input);
		}
	}

	return 0;
} 