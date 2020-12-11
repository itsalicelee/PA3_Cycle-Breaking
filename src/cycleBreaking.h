
// Data structure to store Adjacency list nodes
struct Node {
	int val, cost;
	Node* next;
	char color = 'w';
	Node* pi = nullptr;
	int d = 0;
	int f = 0;
};

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
};

class Graph
{
private:
	Node* getAdjListNode(int value, int weight, Node* head);  // Function to allocate new node of Adjacency List
	int nodeNum;	// number of nodes in the graph
	char graphType;
	void DFS_visit(Node* vertex, int time);
	//void DFS_visit(Node* u, int& time);


public:
	Node **head;  // An array of pointers to Node to represent adjacency list
	Graph(int edgeNum, int nodeNum, char graphType);  // Constructor
	~Graph();  // Destructor
    void printList(Node* ptr, int i);
	void addEdge(Edge anEdge);
	void DFS();



};
