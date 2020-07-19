// unordered map implementation

#include <iostream>
#include <vector>

using namespace std;
#define AVAILABLE 0
#define OCCUPIED 1
class Node {
public:
	int key;
	//int value;
	bool state;
	Node(int k) {
		key = k;
		state = OCCUPIED;
	}
};

class hashmap {
public:
	int cap;
	vector<Node*> bucketArr;
	//vector<bool> flag;

	hashmap() {
		cap = 353333;
		bucketArr.resize(cap, NULL);

		// bad initialization : timelimit 
		/*for (int j = 0; j < cap; j++) {
			bucketArr.push_back(NULL);
		}*/

	}


	int hashCode(int k) { // key ->integer
		return k;
	}

	int compFunc(int in) { //integer -> hashvalue
		int ret = in % cap;
		return ret;
	}

	int hashFunc(int k) { //key -> hash value
		return compFunc(hashCode(k));
	}

	int doubleHashFunc(int k) {
		return (17 - (hashCode(k) % 17));
	}

	int linearPut(int k) {
		int idx = hashFunc(k);
		while (1) {
			if (bucketArr[idx] == NULL) {
				bucketArr[idx] = new Node(k);
				break;
			}
			idx = (1 + idx) % cap;
		}
		return idx;
	}

	int put(int k) { //key, value 저장하고 저장한 위치 반환


		int idx = hashFunc(k);
		int dHashVal = doubleHashFunc(k);

		while (1) {
			if (bucketArr[idx] == NULL) {
				bucketArr[idx] = new Node(k);
				break;
			}
			idx = (idx + dHashVal) % cap;
		}

		return idx;
	}

	int linearProbe(int k) { //open addressing's linear probe : 해당 키값의 위치 반환
		int idx = hashFunc(k);
		int probnum = 1;



		for (int i = 0; i < cap; i++) {

			if (bucketArr[idx] == NULL) {
				idx = -1;
				break;
			}
			else if (bucketArr[idx]->state == AVAILABLE) {
				idx = (idx + 1) % cap;
				probnum++;
			}
			else if (bucketArr[idx]->key == k) {
				break;
			}
			else {
				idx = (idx + 1) % cap;
				probnum++;
			}
		}
		if (idx <= -1)
			cout << 0 << ' ' << probnum << endl;
		else
			cout << 1 << ' ' << probnum << endl;

		return idx;
	}

	int probe(int k) { //double hashing's probe : 해당 키값의 위치 반환
		int idx = hashFunc(k);
		int probnum = 1;
		int dhashVal = doubleHashFunc(k);


		for (int i = 0; i < cap; i++) {

			if (bucketArr[idx] == NULL) {
				idx = -1;
				break;
			}
			else if (bucketArr[idx]->state == AVAILABLE) {
				idx = (idx + dhashVal) % cap;
				probnum++;
			}
			else if (bucketArr[idx]->key == k) {
				break;
			}
			else {
				idx = (idx + dhashVal) % cap;
				probnum++;
			}
		}
		if (idx <= -1)
			cout << 0 << ' ' << probnum << endl;
		else
			cout << 1 << ' ' << probnum << endl;

		return idx;
	}
	void linearErase(int k) {
		int idx = linearProbe(k);
		if (idx == -1)
			return;
		else
			bucketArr[idx]->state = AVAILABLE;
	}
	void erase(int k) {
		int idx = probe(k);
		if (idx == -1)
			return;
		else 
			bucketArr[idx]->state = AVAILABLE;
		return;
	}
};


int main() {

	int testcase = 0;
	cin >> testcase;

	for (int i = 0; i < testcase; i++) {
		hashmap map;
		int size = 0;
		cin >> size;
		for (int a = 0; a < size; a++) {
			int e = 0;
			cin >> e;
			map.put(e);
		}

		int num = 0;
		cin >> num;

		for (int b = 0; b < num; b++) {
			int search = 0;
			cin >> search;
			map.probe(search);
		}
	}

	return 0;

} 