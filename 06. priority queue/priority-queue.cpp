//min heap
#include <iostream>
#include <vector>
using namespace std;

//vector base minHeap
class minHeap
{
public:
	// vector to store heap elements
	vector<int> A;
	int num;

	minHeap() {
		A.push_back(-1);
		num = 0;
	}
	// return parent of A[i]
	// don't call this function if i is already a root node
	int PARENT(int i)
	{
		return i / 2;
	}

	// return left child of A[i]	
	int LEFT(int i)
	{
		return (2 * i);
	}

	// return right child of A[i]	
	int RIGHT(int i)
	{
		return (2 * i + 1);
	}

	// Recursive Heapify-down algorithm
	void heapify_down(int i)
	{
		// get left and right child of node at index i
		int left = LEFT(i);
		int right = RIGHT(i);

		int smallest = i;

		// compare A[i] with its left and right child
		// and find smallest value
		if (left < size() && A[left] < A[i])
			smallest = left;

		if (right < size() && A[right] < A[smallest])
			smallest = right;

		// swap with child having lesser value and 
		// call heapify-down on the child
		if (smallest != i) {
			swap(A[i], A[smallest]);
			heapify_down(smallest);
		}
	}

	// Recursive Heapify-up algorithm
	void heapify_up(int i)
	{
		// check if node at index i and its parent violates 
		// the heap property
		if (i && A[PARENT(i)] > A[i])
		{
			// swap the two if heap property is violated
			swap(A[i], A[PARENT(i)]);

			// call Heapify-up on the parent
			heapify_up(PARENT(i));
		}
	}

	// return size of the heap
	unsigned int size()
	{
		return num;
	}

	// function to check if heap is empty or not
	bool empty()
	{
		return num == 0;
	}

	// insert key into the heap
	void insert(int key)
	{
		// insert the new element to the end of the vector
		A.push_back(key);

		// get element index and call heapify-up procedure
		int index = num + 1;
		heapify_up(index);

		num++;
	}

	// function to remove element with lowest priority (present at root)
	int pop()
	{

		// if heap has no elements, throw an exception
		if (num == 0) {
			return -1;
		}

		// replace the root of the heap with the last element
		// of the vector
		int data = A[1];
		A[1] = A.back();
		A.pop_back();

		// call heapify-down on root node
		heapify_down(1);
		num--;
		return  data;

	}

	// function to return element with lowest priority (present at root)
	int top()
	{

		// if heap has no elements, throw an exception
		if (num == 0) {
			return -1;
		}

		// else return the top (first) element
		return A.at(1);	// or return A[0];

	}
	void print() {
		if (empty()) {
			cout << -1;
		}
		else {
			for (int i = 1; i <= num; i++) {
				cout << A.at(i) << ' ';
			}
		}
		cout << endl;
	}
};

// Min Heap C++ Implementation
int main()
{

	minHeap pq;
	string str;
	int testcase = 0;
	while (1) {
		cin >> testcase;
		if (testcase >= 1 && testcase <= 200000)
			break;
	}

	for (int j = 0; j < testcase; j++) {
		cin >> str;

		if (str == "isEmpty") {
			cout << pq.empty() << endl;
		}
		if (str == "insert") {
			int input = 0;
			cin >> input;
			while (1) {
				if (input >= 1 && input <= 20)
					break;
			}
			pq.insert(input);
		}
		if (str == "print") {
			pq.print();
		}
		if (str == "size") {
			cout << pq.size() << endl;
		}
		if (str == "top") {
			cout << pq.top() << endl;
		}
		if (str == "pop") {
			cout << pq.pop() << endl;
		}
	}

	return 0;
} 