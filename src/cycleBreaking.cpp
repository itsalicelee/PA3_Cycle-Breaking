#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<stdlib.h>
#include"cycleBreaking.h"
using namespace std;

void Graph::initialize()  // initialize d, f, pi, color, array
{
    for(int i = 0; i < nodeNum; i++)
    {
        d[i] = 0;
        f[i] = 0;
        pi[i] = -1;
        color[i] = 'w';
        key[i] = MAX_WEIGHT;
    }
}



Graph::Graph(int edgeNum, int nodeNum, char graphType)  // constructor
{
    // allocate memory
    head = new Node*[nodeNum];
    this->nodeNum = nodeNum;
    this->graphType = graphType;
    

    // initialize head pointer for all vertices
    for (int i = 0; i < nodeNum; ++i){
        this->head[i] = nullptr;
        pi.push_back(0);
		d.push_back(0);
		f.push_back(0);
        pi.push_back(0);
		color.push_back('w');
        key.push_back(0);
    }
    
}


void Graph::printGraph()
{
    // print adjacency list representation of graph
    for (int i = 0; i < nodeNum; ++i)
    {  
        cout << "head" << i << ":" << endl;
        Node* a = head[i];
        while(a != nullptr)
        {
            cout << "("<<a->nodeKey << "," << a->cost  << ")"<< endl;
            a = a ->next;
        }
        cout << endl;
    }
}




// Destructor
Graph::~Graph() {
    for (int i = 0; i < nodeNum; i++)
        delete[] head[i];
    delete[] head;
}

// print all neighboring vertices of given vertex
void Graph::printList(int i)
{
    //given i and G.head[i]
    Node* ptr = this->head[i];

	while (ptr != nullptr)
	{   
		cout << "(" << i << ", " << ptr->nodeKey
			<< ", " << ptr->cost << ") ";

		ptr = ptr->next;
	}
	cout << endl;
}




void Graph::DFS(){
    
    this->initialize();

    int time = 0;

    for(int i = 0; i < nodeNum; ++i)
    {
        //cout << "i: " << i  << head[i]->val << " "<< head[i]->color << endl;   // 這裡應該是要判斷頭有沒有走過（但頭是ptr怎麼辦）
        if (color[i] == 'w'){
            DFS_visit(i, time);
        }
    }
}



void Graph::DFS_visit(int u, int& time)
{
    
    time++;
    this->d[u] = time;
    this->color[u] = 'g';

    Node* v = head[u];
    while(v != nullptr)
    {
        if(color[v->nodeKey] == 'w')
        {
            pi[v->nodeKey]= u;
            DFS_visit(v->nodeKey, time);
        }
        v = v->next;
    }
    this->color[u] = 'b';
    time++;
    this->f[u] = time; 

}

void Graph::printDFS()
{
	for (int i = 0; i < nodeNum; ++i){
		cout << i << ": " <<  "discover time: " << d[i] << ", finish time: " << f[i] << " " << endl;
	}
}

void Graph::PrimMST(int start)
{
    this->initialize();
    this->key[start] = 0;

    // create queue
    PriorityQueue Q;
    for(int i = 0; i < nodeNum; i++)
        Q.push(i);

    // Test queue
    // Q.printQueue();
    // Q.pop();
    // Q.printQueue();
    // Q.pop();
    // Q.printQueue();
    // bool b = Q.inQueue(3);

    cout << "size" << Q.size() << endl;
    while(Q.size() != 0)
    {
        int u = Q.top();  // Q is the lightest key! not the nodeKey
        Q.pop();
        Node* v = head[u];
        
        cout << "u" << u << endl;
        
        //TODO
        while(v != nullptr)
        {
            if(Q.inQueue(v->nodeKey) && v->cost < key[v->nodeKey]) // how to  find w(u,v) 
            {   
                cout << "choose " << v->nodeKey << endl;
                cout << "w(u,v): "<< v->cost << endl;
                pi[v->nodeKey] = u;
                key[v->nodeKey] = v->cost;
            }
            v = v ->next;
            this->printPrim();
        }
        
    }
}

void PriorityQueue::heapify_down(int i)
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

void PriorityQueue::heapify_up(int i)
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

void PriorityQueue::push(int key)
{
        // insert the new element to the end of the vector
        A.push_back(key);
 
        // get element index and call heapify-up procedure
        int index = size() - 1;
        heapify_up(index);
}

void PriorityQueue::pop()
    {
        try {
            // if heap has no elements, throw an exception
            if (size() == 0)
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
 
            // replace the root of the heap with the last element
            // of the vector
            A[0] = A.back();
            A.pop_back();
 
            // call heapify-down on root node
            heapify_down(0);
        }
        // catch and print the exception
        catch (const out_of_range& oor) {
            cout << "\n" << oor.what();
        }
}

int PriorityQueue::top()
{
    try {
        // if heap has no elements, throw an exception
        if (size() == 0)
            throw out_of_range("Vector<X>::at() : "
                    "index is out of range(Heap underflow)");

        // else return the top (first) element
        return A.at(0);    // or return A[0];
    }
    // catch and print the exception
    catch (const out_of_range& oor) {
        cout << "\n" << oor.what();
    }
}
bool PriorityQueue::inQueue(int n)
{   
    // better way??
    for(int i =0; i < A.size(); i++)
    {
        if (n == A[i])
            return true;
    }
    return false;
}

void PriorityQueue::printQueue()
{
    for(int i = 0; i < A.size(); i++)
        cout << A[i] << " ";
    cout << endl;
}

void Graph::printPrim()
{
	for (int i = 0; i < nodeNum; ++i){
		cout << i << ": " <<  "pi: " << pi[i] << ",   key: " << key[i] << " " << endl;
	}
}