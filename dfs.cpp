#include "std_lib_facilities.h"
#include <queue>
#include <stack>

class Node{
	char name;
	list<Node*> ls;
	bool visited;
public:
	Node(char c) :name(c), visited(false) {}
	char get_name() { return name; }
	bool is_visited() { return visited; }
	void mark() { visited = true; }
	list<Node*> get_list() { return ls; }
};

class Graph{
	vector <Node*> vn;
public:
	//helper func.
	Node* nodeFinder(char c){
		for(int i=0; i<vn.size(); i++)
			if(vn[i]->get_name() == c)
				return vn[i];
	}

	vector<Node*>* get_v() { return &vn; }

	void addNode(char c){
		vn.push_back(new Node(c));
	}

	void addEdge(char c1, char c2){
		nodeFinder(c1) -> get_list().push_back(nodeFinder(c2));
		nodeFinder(c2) -> get_list().push_back(nodeFinder(c1));
	}
};

void dfs(Node v);
int main()
{
	//building the graph
	Graph g;
	g.addNode('a');
	g.addNode('b');
	g.addNode('c');
	g.addNode('d');
	g.addNode('e');
	g.addNode('f');
	g.addNode('g');

	g.addEdge('a', 'b');
	g.addEdge('a', 'c');
	g.addEdge('a', 'e');
	g.addEdge('b', 'd');
	g.addEdge('b', 'f');
	g.addEdge('c', 'g');
	g.addEdge('e', 'f');

	//algorithm flow
	for(int i=0; i<g.get_v()->size(); i++)
		if((*(g.get_v()))[i]->is_visited() == false)
			dfs(*(*g.get_v())[i]);
}

void dfs(Node v){
	v.mark();
	cout << v.get_name() << '\t';
	typedef list<Node*>::iterator iter;
	iter p = v.get_list().begin();
	while (p != v.get_list().end()){
		if ((*p)->is_visited() == false)
			dfs(**p);
		p++;
	}
}