#include "std_lib_facilities.h"
#include <queue>
#include <limits>

using namespace std;

class Node{
	char name;
	list<Node*> ls;
	bool visited;
	int dist;
	//Node previous;
public:
	Node(char c) :name(c), visited(false), dist(numeric_limits<int>::infinity()) {}
	char get_name() { return name; }
	int get_dist() { return dist; }
	void set_dist(int d) { dist = d; }
	bool is_visited() { return visited; }
	void mark() { visited = true; }
	list<Node*>* get_list() { return &ls; }
};

class CompareNode {
public:
	bool operator()(Node* n1, Node* n2) // Returns true if n1 has a lower 'dist' than n2
    {
       if (n1->get_dist() < n2->get_dist()) return true;
       return false;
    }
};

class Edge {
	Node* u;
	Node* v;
	int cost;
public:
	Edge(Node* a, Node* b, int c) :u(a), v(b), cost(c) {}
	int get_cost() { return cost; }
	Node* get_u() { return u; }
	Node* get_v() { return v; }
};

class Graph{
	vector <Node*> vn;
	vector<Edge> ve;
public:
	//helper func.
	Node* nodeFinder(char c){
		for(int i=0; i<vn.size(); i++)
			if(vn[i]->get_name() == c)
				return vn[i];
	}

	Edge edgeFinder(Node* a, Node* b) {
		for (int i = 0; i < ve.size(); i++)
			if (ve[i].get_u() == a && ve[i].get_v() == b)
				return ve[i];
	}

	vector<Node*> get_v() { return vn; }
	vector<Edge> get_e() { return ve; }

	void addNode(char c){
		vn.push_back(new Node(c));
	}

	void addEdge(char c1, char c2, int c){
		nodeFinder(c1) -> get_list()->push_back(nodeFinder(c2));
		nodeFinder(c2) -> get_list()->push_back(nodeFinder(c1));
		ve.push_back(Edge(nodeFinder(c1), nodeFinder(c2), c));
	}
};

int main()
{
	priority_queue<Node*, vector<Node*>, CompareNode> pq;

	//building the graph
	Graph g;
	g.addNode('s');
	g.addNode('t');
	g.addNode('y');
	g.addNode('x');
	g.addNode('z');

	g.addEdge('s', 't', 10);
	g.addEdge('s', 'y', 5);
	g.addEdge('t', 'y', 2);
	g.addEdge('t', 'x', 1);
	g.addEdge('y', 'x', 9);
	g.addEdge('y', 'z', 2);
	g.addEdge('z', 'x', 6);
	g.addEdge('z', 's', 7);

	// Algorithm flow
	g.nodeFinder('s')->set_dist(0);
	for (int i = 0; i < g.get_v().size(); i++)
		pq.push(g.get_v()[i]);
	while (!pq.empty())
	{
		Node* t = pq.top();
		if (t->get_dist() == numeric_limits<int>::infinity()) break;
		pq.pop();
		typedef list<Node*>::iterator iter;
		iter p = t->get_list()->begin();
		while (p != t->get_list()->end())
		{
			int alt = (*p)->get_dist() + g.edgeFinder(*p, t).get_cost();
			if (alt < (*p)->get_dist())
				(*p)->set_dist(alt);
		}
	}

	for (int i = 0; i < g.get_v().size(); i++)
		cout << g.get_v()[i]->get_name() << '\t' << g.get_v()[i]->get_dist() << '\n';
}