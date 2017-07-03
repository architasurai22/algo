// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
  
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
  
// Number of vertices in the graph
#define V 201
  
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}
  
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   //for (int i = 0; i < V; i++)
      //printf("%d \t\t %d\n", i, dist[i]);
    cout<<dist[7]<<endl;
    cout<<dist[37]<<endl;
    cout<<dist[59]<<endl;
    cout<<dist[82]<<endl;
    cout<<dist[99]<<endl;
    cout<<dist[115]<<endl;
    cout<<dist[133]<<endl;
    cout<<dist[165]<<endl;
    cout<<dist[188]<<endl;
    cout<<dist[197]<<endl;
}
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
  
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
  
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
  
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
  
       // Mark the picked vertex as processed
       sptSet[u] = true;
  
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
  
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
  
     // print the constructed distance array
     printSolution(dist, V);
}
  
// driver program to test above function
int main()
{
   ifstream ifile;
  int i =0,j,v,u,k,d;
  int graph[V][V];
  char temp[10];
  memset(graph,0,sizeof(graph));
  ifile.open("assignment_5.txt");
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
      //cout<<u<<" ";
      while (iss >> word)
      {
          j=0;
          for(k=0;word.at(k)!=','&&k<word.length();k++)
            temp[j++]=word.at(k);
          temp[j]='\0';
          v = atoi(temp);
          j=0;k++;
          while(k<word.length())
            temp[j++]=word.at(k++);
          d = atoi(temp);
          //cout<<temp<<" ";
          //cout<<d<<" ";
          graph[u-1][v-1]=d;
          graph[v-1][u-1]=d;
      }
  }
  /*for(i=0;i<V;i++)
  {
    for(j=0;j<V;j++)
      cout<<graph[i][j]<<" ";
    cout<<endl;
  }*/
  dijkstra(graph, 0);
    return 0;
}
//2599,2610,2947,2052,2367,2399,2029,2442,2505,3068