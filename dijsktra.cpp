#include <bits/stdc++.h>
#define SIZE 200

using namespace std;

struct edge
{
       int n2;
       int weight;
       edge *next;
};

void dijkstra(edge **g, long *dist, int s)
{
     bool visited[SIZE+1];
     for(int i=1; i<=SIZE; visited[i++]=false);
     visited[s]=true;
     dist[s]=0;
     for(int i=2; i<=SIZE; i++)
     {
             int n2, wt=1000000;
             for(int i=1; i<=SIZE; i++)
             {
                     if(visited[i])
                     {
                             edge *temp=g[i];
                             while(temp!=NULL)
                             {
                                     if(!visited[temp->n2] && (dist[i]+temp->weight)<wt)
                                     {
                                             n2=temp->n2;
                                             wt=(dist[i]+temp->weight);
                                     }
                                     temp=temp->next;
                             }
                     }
             }
             visited[n2]=true;
             dist[n2]=wt;
     }
}

int main(int argc, char *argv[])
{
    edge **g=new edge*[SIZE+1];
    long dist[SIZE+1];
    FILE *f=fopen("dijkstraData.txt","r");
    for(int i=1; i<=SIZE; i++)
    {
            g[i]=NULL;
            dist[i]=1000000;
    }
    char *a=new char[400];
    while(fgets(a,400,f))
    {
            int n1=atoi(a);
            while(a[0]!='\t') a++;
            a++;
            while(true)
            {
                    int n2=atoi(a);
                    while(a[0]!=',') a++;
                    a++;
                    int wt=atoi(a);
                    edge *newedge=new edge;
                    newedge->n2=n2;
                    newedge->weight=wt;
                    newedge->next=g[n1];
                    g[n1]=newedge;
                    while(a[0]!='\t' && strlen(a)>=3) a++;
                    if(strlen(a)<3) break;
                    a++;
            }
            a=new char[400];
    }
    fclose(f);
    dijkstra(g,dist,1);
    cout<<"Shortest Path Distances to the vertices 7,37,59,82,99,115,133,165,188,197:\n";
    cout<<dist[7]<<","<<dist[37]<<","<<dist[59]<<","<<dist[82]<<","<<dist[99]<<","<<dist[115]<<","<<dist[133]<<","<<dist[165]<<","<<dist[188]<<","<<dist[197]<<endl;
 
    return 0;
}
// 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
