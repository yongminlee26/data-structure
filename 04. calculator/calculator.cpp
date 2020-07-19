//calcuate using 2 stackes
//중위표기법 입력을 2stacks로 활용하여 연산
//operator stacks : 중위표기법 -> 후위표기법
//operand stacks : 후위표기법 연산
#include <iostream>
using namespace std;

// stack 구현
//week4 p1
#include <iostream>
using namespace std;

template<typename DATA>
class node {
public:
	DATA data;
	node* next;
};

template<typename DATA>
class SLinkedList {
public:
	//멤버변수
	node<DATA>* head;
	int num;
	//멤버함수
	SLinkedList() {
		head = new node<DATA>; //더미노드
		head->next = NULL;
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

	DATA front() {
		if (empty())
			return 0;
		else
			return head->next->data;
	};

	void addFront(DATA x) {
		node<DATA>* newnode = new node<DATA>;
		node<DATA>* frontNode = head->next;
		newnode->next = frontNode;
		head->next = newnode;
		newnode->data = x;
		num++;
	}

	DATA removeFront() {
		if (empty())
			return 0;
		else {
			DATA frontData = head->next->data;
			node<DATA>* delNode = head->next;
			head->next = delNode->next;
			delete delNode;
			num--;
			return frontData;
		}
	}
};

template<typename DATA>
class SllStack {
public:
	//멤버변수
	SLinkedList<DATA>* sll;
	int number;
	//멤버함수
	SllStack() {
		sll = new SLinkedList<DATA>;
		number = 0;
	}

	~SllStack() {
		while (!empty()) {
			pop();
		}
		delete sll;
	}

	int empty() {
		if (number == 0)
			return 1;
		else return 0;
	}

	int size() {
		return number;
	}

	DATA top() {
		return sll->front();
	}

	void push(int n) {
		number++;
		sll->addFront(n);
	}

	DATA pop() {
		if (!empty())
			number--;
		return sll->removeFront();
	}

};

int main() {

	std::cout << "************************************" << endl;
	std::cout << "             calculator             " << endl;
	std::cout << "************************************" << endl << endl;
	SllStack<char>* operatorStack;
	SllStack<int>* operandStack;

	int testcase = 0;
	std::cout << "testcase : ";
	std::cin >> testcase;

	string infix;	//중위표기법
	char* postfix;	//중위->후위




	for (int a = 0; a < testcase; a++) {
		cout << endl;
		std::cout << "expression #" << a + 1 << " : ";
		std::cin >> infix;				// ex : (2+3)^(8-1)*(4+5*6)-7
		postfix = new char[infix.length() + 1];
		int infixLen = infix.length();

		postfix[infixLen] = '\0';

		operatorStack = new SllStack<char>;

		int postfixIndex = 0;

		//1. 중위표기법을 후위표기법으로 변화 : operatorStack(char를 담는 스택) 사용

		for (int i = 0; i < infix.length(); i++) {
			//step1.1
			if (infix[i] - '0' >= 1 && infix[i] - '0' <= 9) { //operand
				postfix[postfixIndex] = infix[i];
				postfixIndex++;
			}
			//step1.2
			else if (infix[i] == '(') {
				char input = infix[i];
				operatorStack->push(input);
				infixLen -= 1;
				postfix[infixLen] = '\0';

			}
			//step1.3
			else if (infix[i] == ')') {
				infixLen -= 1;
				postfix[infixLen] = '\0';

				char top = operatorStack->top();
				while (top != '(') {
					postfix[postfixIndex] = operatorStack->pop();
					postfixIndex++;
					top = operatorStack->top();
				}
				operatorStack->pop(); // 스택 맨위 의 '(' 제거
			}
			//step1.4
			else { //infix[i]==operator
				if (operatorStack->empty() || operatorStack->top() == '(') {
					operatorStack->push(infix[i]);
				}
				//연산자 우선순위
				else if (infix[i] == '^') {
					operatorStack->push(infix[i]);
				}
				else if (infix[i] == '*' || infix[i] == '/') {
					char top = operatorStack->top();
					if (top == '+' || top == '-') {
						operatorStack->push(infix[i]);
					}
					if (top == '^') {
						postfix[postfixIndex] = operatorStack->pop();
						postfixIndex++;
						operatorStack->push(infix[i]);
					}if (top == '/' || top == '*') {
						postfix[postfixIndex] = operatorStack->pop();
						postfixIndex++;
						operatorStack->push(infix[i]);
					}
				}
				else if (infix[i] == '+' || infix[i] == '-') {
					char top = operatorStack->top();
					postfix[postfixIndex] = operatorStack->pop();
					postfixIndex++;
					operatorStack->push(infix[i]);
				}
			}
		}
		//step1.5

		while (!operatorStack->empty()) {
			postfix[postfixIndex] = operatorStack->pop();
			postfixIndex++;
		}
		cout << "postfix : " << postfix << endl;
		delete operatorStack;
		//elete[] postfix;

		//2. 후위표기법(postprefix) 연산 : int 를 담는 스택 (operandStack) 사용
		//피연산자 : push
		//연산자 : pop, pop, 결과갑 push

		operandStack = new  SllStack<int>;
		//char* postflix 길이 : postfixIndex + 1
		int postfixLen = postfixIndex + 1;
		for (int i = 0; i < postfixLen; i++) {
			char input = postfix[i];
			if ((input - '0') >= 0 && (input - '0') <= 9) { //input is operand
				int inputNum = input - '0';
				operandStack->push(inputNum);
			}
			else if (input == '+') {
				int result = 0;
				result += operandStack->pop();
				result += operandStack->pop();
				operandStack->push(result);
			}
			else if (input == '*') {
				int result = 0;
				result += operandStack->pop();
				result *= operandStack->pop();
				operandStack->push(result);
			}
			else if (input == '/') {
				int result = 0;
				int left = 0;
				int right = 0;
				right = operandStack->pop();
				left = operandStack->pop();
				result = left / right;
				operandStack->push(result);
			}
			else if (input == '-') {
				int left = 0;
				int right = 0;
				int result = 0;
				right = operandStack->pop();
				left = operandStack->pop();
				result = left - right;
				operandStack->push(result);
			}
			else if (input == '^') {
				int left = 0;
				int right = 0;
				int result = 1;
				right = operandStack->pop();
				left = operandStack->pop();
				for (int j = 0; j < right; j++) {
					result *= left;
				}
				operandStack->push(result);
			}
		}
		cout << "결과값 : ";
		cout << operandStack->pop() << endl;

		delete operandStack;
		delete[] postfix;
	}
	return 0;

}