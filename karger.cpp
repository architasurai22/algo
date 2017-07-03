#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
// a structure to represent a unweighted edge in graph
struct Edge
{
    int src, dest;
};
 
// a structure to represent a connected, undirected
// and unweighted graph as a collection of edges.
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge* edge;
};
 
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
      subsets[i].parent =
             find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}
// A very basic implementation of Karger's randomized
// algorithm for finding the minimum cut. Please note
// that Karger's algorithm is a Monte Carlo Randomized algo
// and the cut returned by the algorithm may not be
// minimum always
int kargerMinCut(struct Graph* graph)
{
    // Get data of given graph
    int V = graph->V, E = graph->E;
    Edge *edge = graph->edge;
 
    // Allocate memory for creating V subsets.
    struct subset *subsets = new subset[V];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Initially there are V vertices in
    // contracted graph
    int vertices = V;
 
    // Keep contracting vertices until there are
    // 2 vertices.
    while (vertices > 2)
    {
       // Pick a random edge
       int i = rand() % E;
 
       // Find vertices (or sets) of two corners
       // of current edge
       int subset1 = find(subsets, edge[i].src);
       int subset2 = find(subsets, edge[i].dest);
 
       // If two corners belong to same subset,
       // then no point considering this edge
       if (subset1 == subset2)
         continue;
 
       // Else contract the edge (or combine the
       // corners of edge into one vertex)
       else
       {
          //printf("Contracting edge %d-%d\n",edge[i].src, edge[i].dest);
          vertices--;
          Union(subsets, subset1, subset2);
       }
    }
 
    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);
        if (subset1 != subset2)
          cutedges++;
    }
 
    return cutedges;
}
int main()
{
	ifstream ifile;
	int i =0,j,v,u,k,edges=0,vertices=0;;
	int arr[201][201];
	memset(arr,0,sizeof(arr));
	ifile.open("min_cut.txt");
    if (!ifile)
    {	
    	cout<<"error\n";
        return 1;
    }
    for (string line, word; getline(ifile, line); )
	{
	    istringstream iss(line);
	    iss>>word;
	    u = atoi(word.c_str());
	    vertices++;
	    while (iss >> word)
	    {
	        v = atoi(word.c_str());
	        arr[u][v]=1;
	        edges++;
	    }
	}
	//cout<<vertices<<" "<<edges;
	struct Graph* graph = createGraph(vertices, edges);
	k=0;
	//while(k<edges)
	{
		for(i=1;i<=200;i++)
			for(j=1;j<=200;j++)
				if(arr[i][j]==1)
				{
					graph->edge[k].src = i;
    				graph->edge[k].dest = j;
    				k++;
				}
	}
  int min_cut=9999;
	for(i=0;i<9999;i++)
  {
      srand(time(NULL));
      int cut = kargerMinCut(graph);
      if(cut<min_cut)
      min_cut=cut;
  }
  cout<<min_cut<<endl;
  return 0;
}
//17
    
