#include<iostream>
#include<string>
#include<vector>
using namespace std;

class DoublyEdgeLinkedList;

class vertex {									//vertex class에 대하여	
public:
	DoublyEdgeLinkedList* incidentEdgeList;     //임의의 모든 vertex A는 A와 incident 한 모든 edge들을 이중링크드리스트로 가지고 있다.
	int degree = 0;		//vertex A의 차수
	int data;			//vertex A의 고유번호
	bool visited;       //vertex A가 방문 되었는지 여부
	vertex* prev;       //vertex 한개를 이중연결리스트(vertexLinkedList)를 구성하는 하나의 노드로 볼수 있기 때문
	vertex* next;		//위와 동일한 이유
	vertex(int data);
	void increase_degree() {	//vertex A의 차수를 1증가
		this->degree++;
	}
	void decrease_degree() {	//vertex A의 차수를 1감소
		this->degree--;
	}
};

class edge {
public:
	edge* prev;			//edge 한개를 이중연결리스트(edgeLinkedList)를 구성하는 하나의 노드로 볼수 있기 때문
	edge* next;			//위와 동일한 이유
	edge* myself_InFisrt_incidentEdge;	//임의의 vertex A와 incident한 edge E가 있다고 하자. 이때 E는 A.incidentEdgeList에도 존재(E1)하고, 그래프 전체에서 관리하는 TotalEdgeLinkedList(E2)에도 존재한다. 
	edge* myself_InSecond_incidentEdge;	//이 때, E1과 E2가 바로 O(1)시간에 서로 참조할수있게 포인터를 유지한다. 13주차실습 강의노트 21페이지에서 회색원이 보라색으로 표현된 엣지들로 가는 주황색 화살표 : myself_InTotal_EdgeList, 
	edge* myself_InTotal_EdgeList;		//보라색으로 표현된 엣지에서 회색원으로 나가는  두개의 주황색 화살표 : myself_InFisrt_incidentEdge, myself_InSecond_incidentEdge
	vertex* source;						//엣지를 정의하는 source, destination 두개의 vertex
	vertex* destination;
	string str;
	bool discovery;	//엣지가 discovery edge인지
	bool back;		//해당 엣지가 back edge인지
	bool cross;		//해당 엣지가 cross edge인지
	edge(vertex* a, vertex* b, string s = "null") {
		this->source = a;
		this->destination = b;
		this->myself_InFisrt_incidentEdge = NULL;
		this->myself_InSecond_incidentEdge = NULL;
		this->myself_InTotal_EdgeList = NULL;
		this->discovery = false;
		this->back = false;
		this->cross = false;
		this->str = s;
	}
	vertex* opposite(vertex* v) { //해당 vertex의 반대편 vertex
		if (v == source)
			return destination;
		else if (v == destination)
			return source;
		else return NULL;
	}
};

class DoublyEdgeLinkedList {		//엣지들로 이루어진 이중연결리스트
public:
	edge* head;
	edge* tail;
	int size;
	DoublyEdgeLinkedList() {
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
	void insert(edge* insertEdge) {
		if (this->head == NULL) {
			head = insertEdge;
			tail = insertEdge;
		}
		else {
			tail->next = insertEdge;
			insertEdge->prev = tail;
			tail = insertEdge;
		}
		this->size++;
	}
	void remove(edge* delEdge) {

		if (delEdge == head || delEdge == tail) {
			if (delEdge == head && delEdge != tail) {
				edge* temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;

			}
			else if (delEdge == tail && delEdge != head) {
				edge* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;

			}
			else { head = tail = NULL; }
		}
		else {
			delEdge->prev->next = delEdge->next;
			delEdge->next->prev = delEdge->prev;
			delete delEdge;
		}
		this->size--;
	}
};

vertex::vertex(int data) {
	this->degree = 0;
	this->data = data;
	this->visited = false;
	vertex* prev = NULL;
	vertex* next = NULL;
	this->incidentEdgeList = new DoublyEdgeLinkedList();
}

class DoublyVertexLinkedList {		//vertex들로 이루어진 이중연결리스트
public:
	vertex* head;
	vertex* tail;
	int size;
	DoublyVertexLinkedList() {
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
	void insert(vertex* insertVertex) {
		if (this->head == NULL) {
			head = insertVertex;
			tail = insertVertex;
		}
		else {
			tail->next = insertVertex;
			insertVertex->prev = tail;
			tail = insertVertex;
		}
		this->size++;
	}
	void remove(vertex* delVertex) {
		if (delVertex == head || delVertex == tail) {
			if (delVertex == head && delVertex != tail) {
				vertex* temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;
			}
			else if (delVertex == tail && delVertex != head) {
				vertex* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			else { head = tail = NULL; }
		}
		else {
			delVertex->prev->next = delVertex->next;
			delVertex->next->prev = delVertex->prev;
			delete delVertex;
		}
		this->size--;
	}
};

class graph {
public:
	DoublyVertexLinkedList* TotalvertexList;			//그래프에 존재하는 모든 vertex를 관리하는 이중연결리스트
	DoublyEdgeLinkedList* TotaledgeList;				//그래프에 존재하는 모든 edge를 관리하는 이중연결리스트
	int vertexSize;		//현재 vertex 의 개수
	graph() {
		this->vertexSize = 0;
		this->TotalvertexList = new DoublyVertexLinkedList();
		this->TotaledgeList = new DoublyEdgeLinkedList();
	}
	bool isFindVertex(int data) {		//고유번호가 data인 vertex가 VertexLinkedList에 존재하는지 유무 반환
		vertex* tempVertex;
		bool flag = false;
		tempVertex = TotalvertexList->head;
		while (tempVertex != NULL) {
			if (tempVertex->data == data)
			{
				flag = true; break;
			}
			tempVertex = tempVertex->next;
		}
		return flag;
	}
	vertex* findVertex(int data) {			//고유번호가 data인 vertex가 VertexLinkedList에 존재하면 해당 vertex의 주소값 반환
		vertex* tempVertex;
		tempVertex = TotalvertexList->head;
		while (tempVertex != NULL) {
			if (tempVertex->data == data)
			{
				break;
			}
			tempVertex = tempVertex->next;
		}
		return tempVertex;
	}
	bool isFindEdge(int source, int destination) {	//고유번호가 source와 destination인 vertex로 만들어진 edge가 edgeLinkedList에 존재하는지 유무 반환
		edge* tempEdge;
		bool flag = false;
		tempEdge = TotaledgeList->head;
		while (tempEdge != NULL) {
			if (tempEdge->source->data == source && tempEdge->destination->data == destination ||
				tempEdge->source->data == destination && tempEdge->destination->data == source)
			{
				flag = true; break;
			}
			tempEdge = tempEdge->next;
		}
		return flag;
	}

	edge* findEdge(int source, int destination) {	//고유번호가 source와 destination인 vertex로 만들어진 edge가 edgeLinkedList에 존재한다면 해당 edge주소 반환
		edge* tempEdge;
		tempEdge = TotaledgeList->head;
		while (tempEdge != NULL) {
			if (tempEdge->source->data == source && tempEdge->destination->data == destination ||
				tempEdge->source->data == destination && tempEdge->destination->data == source)
			{
				break;
			}
			tempEdge = tempEdge->next;
		}
		return tempEdge;
	}

	void insert_vertex(int n) {						//고유번호가 n인 vertex를 그래프에 삽입
		if (vertexSize != 0) {
			if (isFindVertex(n) == true)return;
			else {
				vertex* newVertex = new vertex(n);
				TotalvertexList->insert(newVertex);
				this->vertexSize++;
			}
		}
		else {
			vertex* newVertex = new vertex(n);
			TotalvertexList->insert(newVertex);
			this->vertexSize++;
		}
	}

	void insert_edge(int source, int destination, string s) {
		if (isFindVertex(source) == true && isFindVertex(destination) == true) {
			vertex* srcVertex = findVertex(source);
			vertex* dstVertex = findVertex(destination);
			edge* newEdge = new edge(srcVertex, dstVertex, s);		//totaledgelist에 추가될 새로운 edge (E1)

			TotaledgeList->insert(newEdge);

			edge* tempEdge1 = new edge(srcVertex, dstVertex, s);		//src.incidentedges 에 추가될 새로운 edge (E2) 
			edge* tempEdge2 = new edge(srcVertex, dstVertex, s);		//destination.incidentedges에 추가될 새로운 edge(E3)
			tempEdge1->myself_InTotal_EdgeList = newEdge;			//E1,E2와 E3는 주소값자체는 다르지만 각자 가지고 있는 모든 field값은 같다. 
			tempEdge2->myself_InTotal_EdgeList = newEdge;			//실습강의노트 21페이지에서 어던 주황색 화살표들이 E1,E2,E3에 해당되는지 이해하시면 됩니다.

			srcVertex->incidentEdgeList->insert(tempEdge1);
			dstVertex->incidentEdgeList->insert(tempEdge2);
			newEdge->myself_InFisrt_incidentEdge = tempEdge1;
			newEdge->myself_InSecond_incidentEdge = tempEdge2;

			srcVertex->increase_degree();
			dstVertex->increase_degree();
		}
		else {
			return;
		}
	}
	void erase_edge(int source, int destination) {
		if (isFindEdge(source, destination) == false)return;
		else {
			edge* delEdge = findEdge(source, destination);
			vertex* srcVertex = findVertex(source);
			vertex* dstVertex = findVertex(destination);

			srcVertex->incidentEdgeList->remove(delEdge->myself_InFisrt_incidentEdge);
			dstVertex->incidentEdgeList->remove(delEdge->myself_InSecond_incidentEdge);

			srcVertex->decrease_degree();
			dstVertex->decrease_degree();

			TotaledgeList->remove(delEdge);
		}
	}

	bool isAdj(int temp1, int temp2) {			//고유번호 temp1, temp2를 가진 vertex가 서로 인접한지 유무 check!!

		bool flag = false;
		vertex* start = findVertex(temp1);
		edge* temp = start->incidentEdgeList->head;
		for (int i = 0; i < start->incidentEdgeList->size; i++, temp = temp->next) {
			if (temp->destination->data == temp2 || temp->source->data == temp2) { flag = true; break; }
		}
		return flag;
	}

	void DFS(int v) {
		vertex* curVtx = findVertex(v);
		curVtx->visited = true;
		cout << curVtx->data << ' ';
		edge* curEdge = curVtx->incidentEdgeList->head;

		for (int i = 0; i < curVtx->degree; i++) {

			if (curEdge->discovery == false && curEdge->back == false) {
				vertex* oppV = curEdge->opposite(curVtx);
				if (oppV->visited == false) {
					curEdge->discovery = true;
					curEdge->myself_InTotal_EdgeList->discovery = true;
					curEdge->myself_InTotal_EdgeList->myself_InFisrt_incidentEdge->discovery = true;
					curEdge->myself_InTotal_EdgeList->myself_InSecond_incidentEdge->discovery = true;
					DFS(oppV->data);
				}
				else {
					curEdge->back = true;
					curEdge->myself_InTotal_EdgeList->back = true;
					curEdge->myself_InTotal_EdgeList->myself_InFisrt_incidentEdge->back = true;
					curEdge->myself_InTotal_EdgeList->myself_InSecond_incidentEdge->back = true;
				}
			}
			curEdge = curEdge->next;
		}
	};

	vector<vector<vertex*>> lvQueue;
	void BFS(int v) {

		int lv = 0;
		vertex* startV = findVertex(v);
		lvQueue.resize(1);
		lvQueue[lv].push_back(startV);
		startV->visited = true;

		while (!(lvQueue[lv].empty())) {

			//new lvQueue[lv+1]
			lvQueue.resize(lvQueue.size() + 1);

			//for all v in Q[lv]
			for (int i = 0; i < lvQueue[lv].size(); i++) {
				vertex* curVtx = lvQueue[lv][i];
				edge* curEdge = curVtx->incidentEdgeList->head;

				//for all e in v.incidentEdges
				for (int j = 0; j < curVtx->degree; j++) {

					if (curEdge->discovery == false && curEdge->cross == false) {
						vertex* oppV = curEdge->opposite(curVtx);

						if (oppV->visited == false) {
							curEdge->myself_InTotal_EdgeList->discovery = true;
							curEdge->myself_InTotal_EdgeList->myself_InFisrt_incidentEdge->discovery = true;
							curEdge->myself_InTotal_EdgeList->myself_InSecond_incidentEdge->discovery = true;
							oppV->visited = true;
							lvQueue[lv + 1].push_back(oppV);

						}
						else {
							curEdge->myself_InTotal_EdgeList->cross = true;
							curEdge->myself_InTotal_EdgeList->myself_InFisrt_incidentEdge->cross = true;
							curEdge->myself_InTotal_EdgeList->myself_InSecond_incidentEdge->cross = true;
						}
					}
					curEdge = curEdge->next;
				}
			}
			lv++;
		}
	}
};

int main() {

	int N, M, K;
	int temp1, temp2;
	cin >> N >> M >> K;

	graph* gD = new graph();
	graph* gB = new graph();

	//vertex 삽입
	for (int i = 0; i < N; i++) {
		cin >> temp1;
		gD->insert_vertex(temp1);
		gB->insert_vertex(temp1);

	}

	//edge 삽입
	for (int i = 0; i < M; i++) {
		string s = "";
		cin >> temp1 >> temp2;
		//if (g->isFindEdge(temp1, temp2) == true)cout << -1 << endl;
		if (gD->isAdj(temp1, temp2) == true)
			cout << -1 << endl;  
		else 
			gD->insert_edge(temp1, temp2, s);

		if (gB->isAdj(temp1, temp2) == true){ }
		else 
			gB->insert_edge(temp1, temp2, s);
	}

	cout << "DFS" << endl;
	gD->DFS(K);
	cout << endl;

	cout << "BFS" << endl;
	gB->BFS(K);
	for (int i = 0; i < gB->lvQueue.size(); i++) {
		for (int j = 0; j < gB->lvQueue[i].size(); j++) {
			cout << gB->lvQueue[i][j]->data << " ";
		}
	}
	cout << endl;
} 