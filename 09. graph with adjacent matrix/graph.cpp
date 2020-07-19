// graph
#include<iostream>
#include<vector>
using namespace std;
class edge;

class vertex {

public:
	int val;
	int idx;

	vertex(int v, int i) {
		val = v;
		idx = i;
	}

};

class edge {
public:

	vertex* vtx1;
	vertex* vtx2;
	string str;

	edge(vertex* v1, vertex* v2, string s = "null") {
		vtx1 = v1;
		vtx2 = v2;
		str = s;
	}

	vertex* opposite(vertex* pV) {
		if (pV == vtx1)
			return vtx2;
		else if (pV == vtx2)
			return vtx1;
		else
			return NULL;
	}
};



class matrixGraph {

public:

	vector<vertex*> vtxList;
	vector<edge*> edgeList;
	vector<vector<edge*>> matrix;
	int numVtx;
	int numEdge;

	matrixGraph() {
		numVtx = 0;
		numEdge = 0;
	}

	vertex* findVtx(int v) {
		vertex* ret = NULL;

		for (int i = 0; i < vtxList.size(); i++) {
			if (v == vtxList[i]->val) {
				ret = vtxList[i];
				break;
			}
		}
		return ret;
	}

	edge* findEdge(int v1, int v2) {
		edge* ret = NULL;

		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i]->vtx1->val == v1 && edgeList[i]->vtx2->val == v2) {
				ret = edgeList[i];
				break;
			}
			else if (edgeList[i]->vtx2->val == v1 && edgeList[i]->vtx1->val == v2) {
				ret = edgeList[i];
				break;
			}
		}

		return ret;
	}

	void insertVtx(int v) {

		int matrixIdx = matrix.size();
		vertex* nV = new vertex(v, matrixIdx);
		vtxList.push_back(nV);


		matrixIdx++;
		matrix.resize(matrixIdx);
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].resize(matrixIdx);
		numVtx++;
	}
	void insertEdge(int v1, int v2) {

		vertex* vtx1 = findVtx(v1);
		vertex* vtx2 = findVtx(v2);

		if (vtx1 == NULL || vtx2 == NULL) {
			cout << -1 << endl; //정점 정보 존재 x
			return;
		}

		//간선이미 존재
		if (matrix[vtx1->idx][vtx2->idx] != NULL || matrix[vtx2->idx][vtx1->idx] != NULL) {
			cout << -1 << endl;
			return;
		}

		edge* nE = new edge(vtx1, vtx2);
		matrix[vtx1->idx][vtx2->idx] = nE;
		matrix[vtx2->idx][vtx1->idx] = nE;
		edgeList.push_back(nE);
		numEdge++;
	}
	void insertEdge(int v1, int v2, string s) {

		vertex* vtx1 = findVtx(v1);
		vertex* vtx2 = findVtx(v2);

		if (vtx1 == NULL || vtx2 == NULL) {
			cout << -1 << endl; //정점 정보 존재 x
			return;
		}

		//간선이미 존재
		if (matrix[vtx1->idx][vtx2->idx] != NULL || matrix[vtx2->idx][vtx1->idx] != NULL) {
			cout << -1 << endl;
			return;
		}

		edge* nE = new edge(vtx1, vtx2, s);
		matrix[vtx1->idx][vtx2->idx] = nE;
		matrix[vtx2->idx][vtx1->idx] = nE;
		edgeList.push_back(nE);
		numEdge++;
	}

	void info(int v1, int v2) {

		vertex* vtx1 = findVtx(v1);
		vertex* vtx2 = findVtx(v2);

		if (vtx1 == NULL || vtx2 == NULL) {
			cout << -1 << endl; //정점 정보 존재 x
			return;
		}

		//연결되어 있음
		if (matrix[vtx1->idx][vtx2->idx] != NULL && matrix[vtx2->idx][vtx1->idx] != NULL) { //인접
			cout << 1 << endl;
			return;
		}

		//연결안되있음
		if (matrix[vtx1->idx][vtx2->idx] == NULL && matrix[vtx2->idx][vtx1->idx] == NULL) { //인접 x
			cout << 0 << endl;
			return;
		}
	}

	void removeVtx(int v) {

		vertex* delvtx = findVtx(v);
		//삭제하려는 정점이 그래프에 없다면 -1을 출력한다.
		if (delvtx == NULL) {
			cout << -1 << endl;
			return;
		}

		//delvtx의 incidentEdges
		vector<edge*> deledge; 
		for (int i = 0; i < matrix[delvtx->idx].size(); i++) {
			if (matrix[delvtx->idx][i] != NULL)
				deledge.push_back(matrix[delvtx->idx][i]);
		}

		//vtxList에서 vtx제거 
		for (int i = 0; i < vtxList.size(); i++) {
			if (vtxList[i]->val == v) {
				vtxList.erase(vtxList.begin() + i);
			}
		}
		//vtxList[v] = nullptr;

		///matrix에서 vtx제거 => edge제거
		for (int i = 0; i < matrix.size(); i++) {
			matrix[i].erase(matrix[i].begin() + delvtx->idx);
		}
		if (matrix.size() != 0) //★
			matrix.erase(matrix.begin() + delvtx->idx);

		numVtx--;

		//idx 갱신
		for (int i = 0; i < vtxList.size(); i++) {
			if (vtxList[i]->idx > delvtx->idx) //★
				vtxList[i]->idx--;
		}

		delete delvtx;

		//edgeList에서 edge제거
		for (int i = 0; i < edgeList.size(); i++) {
			for (int j = 0; j < deledge.size(); j++) {
				if (deledge[j] == edgeList[i]) {
					edgeList[i] = nullptr; //★ edgeList.erase하면 전체 크기 바뀌어서 에러뜸
					numEdge--;
					break;
				}
			}
		}

		// 정점을 삭제할 때마다, 해당그래프에 남아있는 간선의 개수를 출력
		cout << numEdge << " ";

		// 간선이 생성된 순서에 따라서 간선에 저장되어 있는 정보들을 출력 (edgeList 필요한 이유)
		for (int i = 0; i < edgeList.size(); i++) {
			if (edgeList[i] != NULL) //★
				cout << edgeList[i]->str << ' ';
		}
		cout << endl;
	}
};

int main() {

	int nVtx = 0;
	int nEdge = 0;
	int nDel = 0;
	cin >> nVtx >> nEdge >> nDel;
	matrixGraph mg2;

	for (int i = 0; i < nVtx; i++) {
		int v = 0;
		cin >> v;
		mg2.insertVtx(v);
	}

	for (int i = 0; i < nEdge; i++) {
		int v1 = 0;
		int v2 = 0;
		string s;
		cin >> v1 >> v2 >> s;
		mg2.insertEdge(v1, v2, s);
	}
	cout << mg2.numVtx << ' ' << mg2.numEdge <<endl;

	for (int i = 0; i < nDel; i++) {
		int v = 0;
		cin >> v;
		mg2.removeVtx(v);
	}

	return 0;
}