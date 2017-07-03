// C++ Implementation of Kosaraju's algorithm to print all SCCs
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
# define MAX 10
int arr[MAX],z=0;

class Graph
{
	int V; // No. of vertices
	list<int> *adj; // An array of adjacency lists

	// Fills Stack with vertices (in increasing order of finishing
	// times). The top element of stack has the maximum finishing 
	// time
	void fillOrder(int v, bool visited[], stack<int> &Stack);

	// A recursive function to print DFS starting from v
	int DFSUtil(int v, bool visited[]);
public:
	Graph(int V);
	void addEdge(int v, int w);

	// The main function that finds and prints strongly connected
	// components
	void printSCCs();

	// Function that returns reverse (or transpose) of this graph
	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

// A recursive function to print DFS starting from v
int Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;
	int count = 1;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			count+= DFSUtil(*i, visited);
	return count;
}

Graph Graph::getTranspose()
{
	Graph g(V);
	for (int v = 0; v < V; v++)
	{
		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			g.adj[*i].push_back(v);
		}
	}
	return g;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
	// Mark the current node as visited and print it
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
			fillOrder(*i, visited, Stack);

	// All vertices reachable from v are processed by now, push v 
	Stack.push(v);
}

// The main function that finds and prints all strongly connected 
// components
void Graph::printSCCs()
{
	stack<int> Stack;

	// Mark all the vertices as not visited (For first DFS)
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	// Fill vertices in stack according to their finishing times
	for(int i = 0; i < V; i++)
		if(visited[i] == false)
			fillOrder(i, visited, Stack);

	// Create a reversed graph
	Graph gr = getTranspose();

	// Mark all the vertices as not visited (For second DFS)
	for(int i = 0; i < V; i++)
		visited[i] = false;

	// Now process all vertices in order defined by Stack
	while (Stack.empty() == false)
	{
		// Pop a vertex from stack
		int v = Stack.top();
		Stack.pop();

		// Print Strongly connected component of the popped vertex
		if (visited[v] == false)
		{
			int count = gr.DFSUtil(v, visited);
			arr[z++]=count;
		}
	}
}

// Driver program to test above functions
int main()
{
	ifstream ifile;
	int i =0,j,v,u,k;
	map< int,vector<int> > m;
	Graph g(5);
	ifile.open("scc.txt");
    if (!ifile)
    {	
    	cout<<"error\n";
        return 1;
    }
    for (string line, word; getline(ifile, line); )
	{
	    istringstream iss(line);
	    iss >> word;
	    u = atoi(word.c_str());
	    iss >> word;
	    v = atoi(word.c_str());
	    //cout<<v<<" ";
	    m[u].push_back(v);
	}
	map< int,vector<int> >::iterator it;
	for(it=m.begin();it!=m.end();it++)
	{
		for(int i = 0;i<it->second.size();i++)
			g.addEdge(it->first,it->second[i]);
	}
	memset(arr,0,sizeof(arr));
	g.printSCCs();
	/*int f1,f2,f3,f4,f5;
	f1 = 0;
	for(i=0;i<500;i++)
		if(f1<arr[i])
			f1=arr[i];
	f2 = 0;
	for(i=0;i<500;i++)
		if(f2<arr[i]&&f2!=f1)
			f2=arr[i];
	f3 = 0;
	for(i=0;i<500;i++)
		if(f3<arr[i]&&f3!=f2&&f3!=f1)
			f3=arr[i];
	f4 = 0;
	for(i=0;i<500;i++)
		if(f4<arr[i]&&f4<f3)
			f4=arr[i];
	f5 = 0;
	for(i=0;i<500;i++)
		if(f5<arr[i]&&f5<f4)
			f5=arr[i];
	cout<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<" "<<f5<<endl;*/
	sort(arr,arr+MAX);
	cout<<arr[MAX-1]<<" "<<arr[MAX-2]<<" "<<arr[MAX-3]<<" "<<arr[MAX-4]<<" "<<arr[MAX-5]<<endl;
	return 0;
}
// 434821,968,459,313,211