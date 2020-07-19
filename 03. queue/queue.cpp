//queue 구현
#include <iostream>
using namespace std;

class node {
public:
	int data;
	node* next;
	node* prev;
};

class DLinkedList { //doubly linked list
public:
	//멤버변수
	node* head;
	node* tail;
	int num;
	//멤버함수
	DLinkedList() {
		head = new node;
		head->next = NULL;
		tail = new node;
		tail->prev = NULL;
		num = 0;
	};

	~DLinkedList() {
		while (!empty()) {
			remove();
		}
		delete head;
		delete tail;
	};

	int empty() {
		if (num == 0)
			return 1;
		else
			return 0;
	};

	int size() {
		if (num <= 0) return 0;
		else return num;
	}
	void add(int x) {	//enqueue
		node* newNode = new node;
		newNode->data = x;
		if (empty()) {
			newNode->prev = head;
			newNode->next = tail;
			head->next = newNode;
			tail->prev = newNode;
			num++;
		}
		else {
			node* v = head->next;
			newNode->next = v;
			newNode->prev = head;
			v->prev = newNode;
			head->next = newNode;
			num++;
		}

	};

	int remove() {	//dequeue
		node* v = tail->prev;
		if (empty())return -1;
		else {
			node* w = v->prev;
			w->next = tail;
			tail->prev = w;
			int data = v->data;
			delete v;
			num--;
			if (empty())
				num = 0;
			return data;
		}
	}

	int front() {
		if (empty())
			return -1;
		else
			return tail->prev->data;
	}

	int rear() {
		if (empty())
			return-1;
		else
			return head->next->data;
	}
};

class Queue {
public:
	//멤버변수
	DLinkedList* dll;
	int num;
	int cap;
	Queue(int n) {
		dll = new DLinkedList;
		num = 0;
		cap = n;
	}
	~Queue() {
		while (!isEmpty())
			dequeue();
		delete dll;
	}

	int isEmpty() {
		if (num == 0)
			return 1;
		else
			return 0;
	}

	void enqueue(int x) {
		if (num >= cap)
			cout << "Full" << endl;
		else {
			dll->add(x);
			num++;
		}
	}

	int dequeue() {
		if (num == 0)
			return -1;
		else {
			num--;
			if (num <= 0) {
				num = 0;
			}
			return dll->remove();
		}
	}

	int size() {
		if (num <= 0)
			return 0;
		else
			return num;
	}

	void front() {
		if (isEmpty()) {
			cout << "Empty" << endl;
		}
		else {
			cout << dll->front() << endl;
		}
	}

	void rear() {
		if (isEmpty()) {
			cout << "Empty" << endl;
		}
		else {
			cout << dll->rear() << endl;
		}
	}
};

int main() {
	int testcase = 0;

	while (1) {
		cin >> testcase;
		if (testcase >= 1 && testcase <= 100000)
			break;
	}

	for (int j = 0; j < testcase; j++) {
		int deck = 0; //카드개수
		while (1) {
			cin >> deck;
			if (deck >= 1 && deck <= 20)
				break;
		}

		Queue* q1 = new Queue(deck);
		Queue* q2 = new Queue(deck);

		for (int i = 0; i < deck; i++) {
			int input = 0;
			while (1) {
				cin >> input;
				if (input >= 1)
					break;
			}
			q1->enqueue(input);
		}
		for (int i = 0; i < deck; i++) {
			int input = 0;
			while (1) {
				cin >> input;
				if (input >= 1)
					break;
			}
			q2->enqueue(input);
		}

		int q1win = 0;
		int q2win = 0;
		int q1life = 0;
		int q2life = 0;

		for (int i = 0; i < deck; i++) {
			int q1char = q1->dequeue() + q1life;
			int q2char = q2->dequeue() + q2life;

			if (q1char > q2char) {
				q1win++;
				q1life = q1char - q2char - 1;
				q2life = 0;
			}
			else if (q2char > q1char) {
				q2win++;
				q2life = q2char - q1char - 1;
				q1life = 0;
			}
			else {//비김
				q2life = 0;
				q1life = 0;
			}
		}
		if (q1win > q2win)
			cout << 1 << endl;
		else if (q2win > q1win)
			cout << 2 << endl;
		else
			cout << 0 << endl;
		delete q1;
		delete q2;
	}

	return 0;
} 