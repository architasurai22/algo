#include <bits/stdc++.h>
#define INFINITY 99999
#define MIN(a,b) a<b?a:b
using namespace std;

struct node
{
       int nodenum,cost;
       node *next;
}**g;

void getInt(char *a, int nos, int *val1, int *val2, int *val3=NULL)
{
     int i,j;
     char ab[10];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *val1=atoi(ab);
     for(j=0, i++; (a[i]!='\n' && a[i]!=' '); i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val2=atoi(ab);
     if(nos==3)
     {
               for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
               ab[j]='\0';
               *val3=atoi(ab);
     }
}

int cost(int i, int j)
{
    node *temp=g[i];
    while(temp!=NULL)
    {
         if(temp->nodenum==j) return temp->cost;
         temp=temp->next;
    }
    return INFINITY;
}

void getSSP(char *s)
{
    char line[20];
    int num_nodes,num_edges,***a;
    FILE *f=fopen(s,"r");
    fgets(line,20,f);
    getInt(line,2,&num_nodes,&num_edges);
    g=new node*[num_nodes+1];
    for(int i=1; i<=num_nodes; i++)
    {
            g[i]=new node;
            g[i]->next=NULL;
            g[i]->nodenum=i;
            g[i]->cost=0;
    }
    for(int i=0; i<num_edges; i++)
    {
            int node1,node2,cost;
            fgets(line,20,f);
            getInt(line,3,&node1,&node2,&cost);
            node *newnode=new node;
            newnode->nodenum=node2;
            newnode->cost=cost;
            newnode->next=NULL;
            node *temp=g[node1];
            while(temp->next!=NULL) temp=temp->next;
            temp->next=newnode;
    }
    fclose(f);
    a=new int**[num_nodes+1];
    for(int i=1; i<=num_nodes; i++)
    {
            a[i]=new int*[num_nodes+1];
            for(int j=1; j<=num_nodes; j++)
                    {
                         a[i][j]=new int[2];
                         if(i==j) a[i][j][0]=0;
                         else a[i][j][0]=cost(i,j);
                    }
            delete g[i];
    }
    for(int k=1; k<=num_nodes; k++)
    {
            for(int i=1; i<=num_nodes; i++)
                for(int j=1; j<=num_nodes; j++)
                    a[i][j][1]=MIN(a[i][j][0],(a[i][k][0]+a[k][j][0]));
            for(int i=1; i<=num_nodes; i++)
                for(int j=1; j<=num_nodes; j++)
                    a[i][j][0]=a[i][j][1];
    }
    
    bool flag=true;
    for(int i=1; i<=num_nodes; i++) if(a[i][i][1]<0)
    {
            flag=false;
            cout<<"Negative cost cycle found.\n";
            break;
    }
    if(flag)
    {
            int max=INFINITY;
            for(int i=1; i<=num_nodes; i++)
                    for(int j=1; j<=num_nodes; j++)
                            if(a[i][j][1]<=max)
                               max=a[i][j][1];
            cout<<"Shortest Shortest Path: "<<max<<endl;
    }
    delete g;
    delete a;
}

int main(int argc, char *argv[])
{
    getSSP("g1.txt");
    getSSP("g2.txt");
    getSSP("g3.txt");
    return 0;
}
// -19
